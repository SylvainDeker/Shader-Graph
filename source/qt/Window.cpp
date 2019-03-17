#include "Window.h"

#include <vector>
#include <memory>
#include <string>

#include <QComboBox>
#include <QPushButton>
#include <QSurfaceFormat>

#include <nodes/FlowScene>


#include <core/Core.h>

#include "ui_Window.h"

/* WIP : not sure to add them all */

#include <QtWidgets/QGraphicsScene>
#include <QApplication>
#include <QCursor>
#include <QLineEdit>

#include <QDrag>
#include <QMimeData>
#include <QLabel>

#include <nodes/Node>
#include <nodes/FlowScene>
#include <nodes/FlowView>

#define FORMAT_VERSION 4, 1
#define FORMAT_DEPTH_BUFFER_SIZE 24

Window::Window(QWidget * Parent) :
    QMainWindow(Parent),
    ui(new Ui::Window)
{
    // Step 0 : Initialise the default format
    QSurfaceFormat format;
    format.setVersion(FORMAT_VERSION);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(FORMAT_DEPTH_BUFFER_SIZE);
    QSurfaceFormat::setDefaultFormat(format);

    // Step 1 : Setup the user interface
    ui->setupUi(this);
    setCentralWidget(ui->widget);

    QObject::connect(ui->saveButton, &QPushButton::pressed,
                     ui->nodeEditor->getScene(), &QtNodes::FlowScene::save);

    QObject::connect(ui->loadButton, &QPushButton::pressed,
                     ui->nodeEditor->getScene(), &QtNodes::FlowScene::load);

    // Step 2 : Setup the logger
    LOG_INIT("../data/ShaderGraph.log", ui->logPanel);
    LOG_CONNECT(ui->logLevelSelector);

    // Step 3 : Update the GL-Widget
    // FIXME : for some reason, a simple ui->preview->update doesn't "work".
    //         It needs a bit a delay to display the build scene.
    QTimer::singleShot(100, ui->preview, SLOT(update()));

    // Step 4 : Create the function tree view
    ui->functionFilter->setPlaceholderText(QStringLiteral("Filter..."));

    ui->treeWidget->header()->close();

    QtNodes::FlowScene * scene = ui->nodeEditor->getScene();

    // Push each category
    for (auto const &category : scene->registry().categories())
    {
        auto item = new QTreeWidgetItem(ui->treeWidget);
        item->setText(0, category);
        item->setData(0, Qt::UserRole, QStringLiteral("skip me"));
        item->setTextColor(0, QColor("white"));
        m_internalFunctionTree[category] = item;
    }

    // Push each function
    for (auto const &assoc : scene->registry().registeredModelsCategoryAssociation())
    {
        auto parent = m_internalFunctionTree[assoc.second];
        auto item   = new QTreeWidgetItem(parent);
        item->setText(0, assoc.first);
        item->setData(0, Qt::UserRole, assoc.first);
        item->setTextColor(0, QColor("gray"));
    }

    // Item clicked event
    connect(ui->treeWidget, &QTreeWidget::itemClicked, [this](QTreeWidgetItem *item, int)
    {
        QString modelName = item->data(0, Qt::UserRole).toString();

        if (modelName == QStringLiteral("skip me")) return;

        auto type = ui->nodeEditor->getScene()->registry().create(modelName);

        if (type)
        {
            // create the node
            auto& node = ui->nodeEditor->getScene()->createNode(std::move(type));

            // Set the node position to the center of the flow view
            const QtNodes::FlowView * flowView = ui->nodeEditor->getFlowView();
            auto viewportDimension = flowView->viewport()->rect();
            QPointF flowViewCenter = flowView->mapToScene(viewportDimension).boundingRect().center();
            node.nodeGraphicsObject().setPos(flowViewCenter);

            LOG_INFO("Creating : {0} node", modelName.toStdString());
        }
        else LOG_ERROR("QTreeWidget::itemClicked::functionTree :Model not found");
    });

    // Setup filtering
    connect(ui->functionFilter, &QLineEdit::textChanged, [this](const QString &text)
    {
        for (auto& topLvlItem : m_internalFunctionTree)
        {
            for (int i = 0; i < topLvlItem->childCount(); ++i)
            {
                auto child = topLvlItem->child(i);
                auto modelName = child->data(0, Qt::UserRole).toString();
                const bool match = (modelName.contains(text, Qt::CaseInsensitive));
                child->setHidden(!match);
            }
        }
    });
    
    ui->nodeEditor->setAssociatedDetailsLayout(ui->layoutdetails);
}

Window::~Window()
{
    LOG_DESTROY; // Destroy the log system.
    delete ui;
}
