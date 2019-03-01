#include "Window.h"

#include <vector>
#include <memory>
#include <string>

#include <QComboBox>
#include <QSurfaceFormat>

#include <core/Core.h>

#include "ui_Window.h"

#define FORMAT_VERSION 4, 1
#define FORMAT_DEPTH_BUFFER_SIZE 24
#define FPS 60

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

    // Step 2 : Setup the logger
    LOG_INIT("../data/ShaderGraph.log", ui->logPanel);

    connect(ui->logLevelSelector, SIGNAL(currentIndexChanged(int)),
            &ShaderGraph::LOGGER, SLOT(setLevel(int)));

    SET_LOG_LEVEL_TO_DEBUG();

    // Step 3 : Initialize the timer that will update the GLWidget every tick
    timer = new QTimer(ui->preview);
    connect(timer, SIGNAL(timeout()), ui->preview, SLOT(update()));
    timer->start(1000 / FPS);
}

Window::~Window()
{
    delete ui;
}