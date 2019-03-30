#include <QPushButton>
#include "NodeGraphicsView.h"
#include "../model/Node.h"

NodeGraphicsView::
NodeGraphicsView(QWidget *parent):
    FlowView(parent),
    m_detailslayout(nullptr)
{

}

NodeGraphicsView::
NodeGraphicsView(QtNodes::FlowScene *scene, QWidget *parent):
    FlowView(scene, parent),
    m_detailslayout(nullptr)
{

}


void NodeGraphicsView::mousePressEvent(QMouseEvent *event)
{
    std::vector<QtNodes::Node*> nodes = scene()->selectedNodes();

//  if (!nodes.empty()) {
//
//      ShaderGraph::Node * md;
//
//      for (size_t i = 0; i < nodes.size(); i++) {
//        md = dynamic_cast<ShaderGraph::Node *>(nodes[i]->nodeDataModel());
//        md->showDetails(m_detailslayout);
//      }
//
//  }

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

                sgNode->showDetails(m_detailslayout);
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
