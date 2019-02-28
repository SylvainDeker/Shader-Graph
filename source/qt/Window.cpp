#include "Window.h"

#include <vector>
#include <memory>
#include <string>

#include <QComboBox>
#include <QSurfaceFormat>

#include <core/Core.h>

#include "ui_Window.h"

Window::Window(QWidget * Parent) :
    QMainWindow(Parent),
    ui(new Ui::Window)
{
    // Step 1 : Setup the user interface
    ui->setupUi(this);
    setCentralWidget(ui->widget);

    // Step 2 : Setup the logger
    LOG_INIT("../data/ShaderGraph.log", ui->logPanel);

    connect(ui->logLevelSelector, SIGNAL(currentIndexChanged(int)),
            &ShaderGraph::LOGGER, SLOT(setLevel(int)));

    SET_LOG_LEVEL_TO_DEBUG();
}

Window::~Window()
{
    delete ui;
}