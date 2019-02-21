#include "Window.h"

#include <QSurfaceFormat>

#include "ui_Window.h"

Window::Window(QWidget * Parent) : 
    QMainWindow(Parent), 
    ui(new Ui::Window)
{
    /* Setup the UI */
    ui->setupUi(this);
    ui->nodeEditor->setFocus();
    this->setCentralWidget(ui->widget);

    ui->logPanel->append("<Log Init>");
    ui->logPanel->append("<Log> ...");
}

Window::~Window() 
{
    delete ui;
}