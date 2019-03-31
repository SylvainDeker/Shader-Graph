#include <QPushButton>
#include "NodeGraphicsView.h"
#include "../model/Node.h"

#include "../model/output/MasterMaterialOutput.h"

NodeGraphicsView::NodeGraphicsView(QWidget *parent):
    FlowView(parent)
{

}

NodeGraphicsView::NodeGraphicsView(QtNodes::FlowScene *scene, QWidget *parent):
    FlowView(scene, parent)
{

}


void NodeGraphicsView::mousePressEvent(QMouseEvent *event)
{
    std::vector<QtNodes::Node*> nodes = scene()->selectedNodes();

    if (nodes.empty())
    {
        if (m_detailedNode) m_detailedNode->hideDetails(m_detailsTree);
        m_detailedNode = nullptr;
    }
    else
    {
        bool hasPromotedNode = false;

        for (QtNodes::Node * node : nodes)
        {
            auto sgNode = dynamic_cast<ShaderGraph::Node *>(node->nodeDataModel());

            if (sgNode == nullptr) // cast failed
            {
                LOG_ERROR("NodeGraphicsView::mousePressEvent : Invalid node : Ignored");
            }
            else
            {
                if (m_detailedNode) m_detailedNode->hideDetails(m_detailsTree);
                m_detailedNode = sgNode;

                sgNode->showDetails(m_detailsTree);

                hasPromotedNode = true;
            }
        }

        if (!hasPromotedNode)
        {
            LOG_ERROR("NodeGraphicsView::mousePressEvent : Any selected nodes has been promoted");
            m_detailedNode = nullptr;
        }
    }
    FlowView::mousePressEvent(event);
}

void NodeGraphicsView::deleteSelectedNodes(){
  ShaderGraph::Node * node;
  for (QGraphicsItem * item : scene()->selectedItems())
  {
    if (auto n = qgraphicsitem_cast<QtNodes::NodeGraphicsObject*>(item)){
      node = static_cast<ShaderGraph::Node*>(n->node().nodeDataModel());
      if(node->name()==QStringLiteral("MasterMaterialOutput")) return;
    }
  }
  FlowView::deleteSelectedNodes();
}
