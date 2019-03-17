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
#include <QTreeWidgetItem>
#include <QApplication>
#include <QCursor>
#include <QLineEdit>

#include <nodes/Node>

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

    QMap<QString, QTreeWidgetItem*> topLevelItems;

    // Push each category
    for (auto const &category : scene->registry().categories())
    {
        auto item = new QTreeWidgetItem(ui->treeWidget);
        item->setText(0, category);
        item->setData(0, Qt::UserRole, QStringLiteral("skip me"));
        item->setTextColor(0, QColor("white"));
        topLevelItems[category] = item;
    }

    // Push each function
    for (auto const &assoc : scene->registry().registeredModelsCategoryAssociation())
    {
        auto parent = topLevelItems[assoc.second];
        auto item   = new QTreeWidgetItem(parent);
        item->setText(0, assoc.first);
        item->setData(0, Qt::UserRole, assoc.first);
        item->setTextColor(0, QColor("gray"));
    }

    // Item clicked event
    connect(ui->treeWidget, &QTreeWidget::itemClicked, [&](QTreeWidgetItem *item, int)
    {
        QString modelName = item->data(0, Qt::UserRole).toString();

        if (modelName == QStringLiteral("skip me")) return;

        LOG_INFO("Creating a new node : {0} (WIP)", modelName.toStdString());
    });

    // Setup filtering
    connect(ui->functionFilter, &QLineEdit::textChanged, [&](const QString &text)
    {
        (void) text;
        LOG_INFO("Filtering : function tree (WIP)");
    });
}

Window::~Window()
{
    LOG_DESTROY; // Destroy the log system.
    delete ui;
}