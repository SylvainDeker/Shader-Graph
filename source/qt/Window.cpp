#include "Window.h"

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>

#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QSurfaceFormat>
#include <QtWidgets/QGraphicsScene>

#include <nodes/Node>
#include <nodes/FlowView>
#include <nodes/FlowScene>

#include <core/Core.h>

#include "ui_Window.h"
#include "model/Compilation.h"

#define FORMAT_VERSION 4, 1
#define FORMAT_DEPTH_BUFFER_SIZE 24

Window::Window(QWidget * Parent) :
        QMainWindow(Parent),
        m_ui(new Ui::Window)
{
    // Step 0 : Initialise the default format
    QSurfaceFormat format;
    format.setVersion(FORMAT_VERSION);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(FORMAT_DEPTH_BUFFER_SIZE);
    QSurfaceFormat::setDefaultFormat(format);

    // Step 1 : Setup the user interface
    m_ui->setupUi(this);
    setCentralWidget(m_ui->widget);

    QObject::connect(m_ui->saveButton, &QPushButton::pressed,
                     m_ui->nodeEditor->getScene(), &QtNodes::FlowScene::save);

    QObject::connect(m_ui->loadButton, &QPushButton::pressed,
                     m_ui->nodeEditor->getScene(), &QtNodes::FlowScene::load);

    QObject::connect(m_ui->compileButton, &QPushButton::pressed,
                     this, &Window::compile);

    m_ui->detailsTree->header()->close();

    // Step 2 : Setup the logger
    LOG_INIT("../data/ShaderGraph.log", m_ui->logPanel);
    LOG_CONNECT(m_ui->logFilter);

    // Step 3 : Update the GL-Widget
    // FIXME : for some reason, a simple m_ui->preview->update doesn't "work".
    //         It needs a bit a delay to display the build scene.
    QTimer::singleShot(100, m_ui->preview, SLOT(update()));

    // Step 4 : Create the common tree view
    QtNodes::FlowScene * scene = m_ui->nodeEditor->getScene();

    m_ui->treeWidget->header()->close();
    m_ui->functionFilter->setPlaceholderText(QStringLiteral("Filter..."));

    // Push each category
    for (auto const &category : scene->registry().categories())
    {
        if(category !=QStringLiteral("Output"))
        {
            auto item = new QTreeWidgetItem(m_ui->treeWidget);
            item->setText(0, category);
            item->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            item->setTextColor(0, QColor("white"));
            m_internalFunctionTree[category] = item;
        }
    }

    // Push each common
    for (auto const &assoc : scene->registry().registeredModelsCategoryAssociation())
    {
        auto parent = m_internalFunctionTree[assoc.second];
        auto item   = new QTreeWidgetItem(parent);
        item->setText(0, assoc.first);
        item->setData(0, Qt::UserRole, assoc.first);
        item->setTextColor(0, QColor("gray"));
    }

    // Event: item clicked Function Panel
    connect(m_ui->treeWidget, &QTreeWidget::itemClicked, [this](QTreeWidgetItem *item, int)
    {
        QString modelName = item->data(0, Qt::UserRole).toString();

        if (modelName == QStringLiteral("skip me")) return;

        auto type = m_ui->nodeEditor->getScene()->registry().create(modelName);

        if (type)
        {
            // create the node
            auto& node = m_ui->nodeEditor->getScene()->createNode(std::move(type));

            // Set the node position to the center of the flow view
            const QtNodes::FlowView * flowView = m_ui->nodeEditor->getFlowView();
            auto viewportDimension = flowView->viewport()->rect();
            QPointF flowViewCenter = flowView->mapToScene(viewportDimension).boundingRect().center();
            node.nodeGraphicsObject().setPos(flowViewCenter);
        }
        else LOG_ERROR("QTreeWidget::itemClicked::functionTree :Model not found");
    });

    // Event : Filter Function Panel
    connect(m_ui->functionFilter, &QLineEdit::textChanged, [this](const QString &text)
    {
        for (auto& topLvlItem : m_internalFunctionTree)
        {
            // FIXME : A "Top Level Item" is nullptr...
            if (topLvlItem)
            {
                for (int i = 0; i < topLvlItem->childCount(); ++i)
                {
                    auto child = topLvlItem->child(i);
                    auto modelName = child->data(0, Qt::UserRole).toString();
                    const bool match = modelName.contains(text, Qt::CaseInsensitive);
                    child->setHidden(!match);
                }
            }
        }
    });

    // Step 5 : Setup Details Panel
    m_ui->nodeEditor->setDetailsTree(m_ui->detailsTree);
}

void Window::compile()
{
    bool success = false;
    std::string errmsg = "No error recorded";

    ShaderGraph::GLSLData glslData;

    ShaderGraph::FlowScene * sc = m_ui->nodeEditor->getScene();

    bool isMasterMaterialOutputNodeFound = false;
    ShaderGraph::Node * masterMaterialOutputNode = nullptr;

    // Looking for the output node
    for (auto& elt : sc->nodes())
    {
        assert(dynamic_cast<ShaderGraph::Node*>(elt.second->nodeDataModel()));
        auto node = dynamic_cast<ShaderGraph::Node*>(elt.second->nodeDataModel());

        if (node->name() == "MasterMaterialOutput")
        {
            isMasterMaterialOutputNodeFound = true;
            masterMaterialOutputNode = node;
        }
    }

    if (isMasterMaterialOutputNodeFound)
    {
        // Write the code in a file
        std::ofstream shaderFile("../data/ShaderGraph_Output.txt");

        if (shaderFile.is_open())
        {
            glslData = masterMaterialOutputNode->toGLSL();

            success = !glslData.hasFailed;

            if (success)
            {
                // Write and flush the generated code.
                shaderFile << glslData.generatedCode;
                shaderFile.flush();

                // Close the file.
                shaderFile.close();
            }
            else errmsg = glslData.errmsg;
        }
        else errmsg = "Could not open file";
    }
    else errmsg = "No output node";

    if (success)
    {
        m_ui->preview->onShaderCompiled(glslData.uniforms,
                                        glslData.generatedCode,
                                        glslData.texturePaths);
        LOG_INFO("Shader : Compiled");
    }
    else
    {
        LOG_ERROR("Compilation failed : {0}", errmsg);
    }
}

Window::~Window()
{
    LOG_DESTROY; // Destroy the log system.
    delete m_ui;
}
