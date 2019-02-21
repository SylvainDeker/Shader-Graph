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

//QApplication app(argc, argv);
//
//ShaderGraph::NodeManager nodeManager;
//
//nodeManager.registry()->registerModel<ShaderGraph::BooleanNode>();
//
//nodeManager.loadNodeStyle("../data/nodestyle.txt");
//
//QtNodes::FlowScene scene(nodeManager.registry());
//QtNodes::FlowView view(&scene);
//
//view.setWindowTitle("ShaderGraph");
//view.resize(800, 600);
//view.show();
//
//return app.exec();