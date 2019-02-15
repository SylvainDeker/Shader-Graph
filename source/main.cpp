#include <QtWidgets/QApplication>

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>

#include "core/Core.h"
#include "model/NodeManager.h"

#include "model/input/BooleanNode.h"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  ShaderGraph::NodeManager nodeManager;

  nodeManager.registry()->registerModel<ShaderGraph::BooleanNode>();

  nodeManager.loadNodeStyle("../data/nodestyle.txt");

  QtNodes::FlowScene scene(nodeManager.registry());
  QtNodes::FlowView view(&scene);

  view.setWindowTitle("ShaderGraph");
  view.resize(800, 600);
  view.show();

  return app.exec();
}
