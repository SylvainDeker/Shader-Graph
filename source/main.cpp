#include <QApplication>
#include "qt/Window.h"

#include "core/Core.h"
//#include "model/NodeManager.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Window window;
    window.show();
    return app.exec();
}