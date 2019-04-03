#include "WidgetNodeEditor.h"

#include <QVBoxLayout>

#include "pin/PinDecl.h"
#include "model/NodeDecl.h"
#include "nodeeditor/NodeManager.h"

#include "nodeeditor/NodeGraphicsView.h"

WidgetNodeEditor::WidgetNodeEditor(QWidget *parent):
    QWidget(parent)
{
    ShaderGraph::NodeManager nodeManager;
    nodeManager.loadNodeStyle("../data/nodestyle.txt");

    nodeManager.registry()->registerModel<ShaderGraph::MasterMaterialOutput>("Output");

    nodeManager.registry()->registerModel<ShaderGraph::ColorNode>("Input");
    nodeManager.registry()->registerModel<ShaderGraph::TextureNode>("Input");
    nodeManager.registry()->registerModel<ShaderGraph::ScalarNode>("Input");
    nodeManager.registry()->registerModel<ShaderGraph::Vec2Node>("Input");
    nodeManager.registry()->registerModel<ShaderGraph::Vec3Node>("Input");
    nodeManager.registry()->registerModel<ShaderGraph::Vec4Node>("Input");

    nodeManager.registry()->registerModel<ShaderGraph::MakeVec2Node>("Vector");
    nodeManager.registry()->registerModel<ShaderGraph::BreakVec2Node>("Vector");

    nodeManager.registry()->registerModel<ShaderGraph::MakeVec3Node>("Vector");
    nodeManager.registry()->registerModel<ShaderGraph::BreakVec3Node>("Vector");

    nodeManager.registry()->registerModel<ShaderGraph::MakeVec4Node>("Vector");
    nodeManager.registry()->registerModel<ShaderGraph::BreakVec4Node>("Vector");

    nodeManager.registry()->registerModel<ShaderGraph::FxVecN>("DebugOnly");
    nodeManager.registry()->registerModel<ShaderGraph::GxOnlyVec2>("DebugOnly");

    nodeManager.registry()->registerModel<ShaderGraph::AndOperatorNode>("LogicalOperator");
    nodeManager.registry()->registerModel<ShaderGraph::OrOperatorNode>("LogicalOperator");

    nodeManager.registry()->registerModel<ShaderGraph::EqualNode>("LogicalOperator");
    nodeManager.registry()->registerModel<ShaderGraph::NotEqualNode>("LogicalOperator");
    nodeManager.registry()->registerModel<ShaderGraph::GreaterNode>("LogicalOperator");
    nodeManager.registry()->registerModel<ShaderGraph::LowerNode>("LogicalOperator");
    nodeManager.registry()->registerModel<ShaderGraph::GreaterEqualNode>("LogicalOperator");
    nodeManager.registry()->registerModel<ShaderGraph::LowerEqualNode>("LogicalOperator");

    nodeManager.registry()->registerModel<ShaderGraph::AddNode>("Operator");
    nodeManager.registry()->registerModel<ShaderGraph::SubtractNode>("Operator");
    nodeManager.registry()->registerModel<ShaderGraph::MultiplyNode>("Operator");
    nodeManager.registry()->registerModel<ShaderGraph::DivideNode>("Operator");


    ShaderGraph::registerToTemplateConverters(nodeManager.registry());

    m_layout        = new QVBoxLayout(this);
    m_scene         = new FlowScene(nodeManager.registry(),this);
    m_graphicsView  = new NodeGraphicsView(m_scene);

    m_layout->addWidget(m_graphicsView);
}

