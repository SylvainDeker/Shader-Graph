#include <QPushButton>

#include "model/Node.h"
#include "FlowView.h"
#include "../model/output/MasterMaterialOutput.h"

namespace ShaderGraph
{
    FlowView::FlowView(QWidget *parent) : QtNodes::FlowView(parent)
    {
        connect(this->scene(), &QtNodes::FlowScene::nodeDeleted,
                this, &::ShaderGraph::FlowView::onNodeDeleted);
    }

    FlowView::FlowView(QtNodes::FlowScene *scene, QWidget *parent) : QtNodes::FlowView(scene, parent)
    {
        connect(this->scene(), &QtNodes::FlowScene::nodeDeleted,
                this, &::ShaderGraph::FlowView::onNodeDeleted);
    }

    void FlowView::onNodeDeleted(QtNodes::Node& n)
    {
        Q_UNUSED(n);

        ShaderGraph::Node * node;

        bool isDeletingTheDetailedNode = false;

        // Check if the MasterMaterialOutputNode is in the selectedItems.
        // If it is, then "cancel" this event, else continue.
        for (QGraphicsItem * item : scene()->selectedItems())
        {
            auto nodeGraphicsObject = qgraphicsitem_cast<QtNodes::NodeGraphicsObject*>(item);

            if (nodeGraphicsObject)
            {
              node = dynamic_cast<ShaderGraph::Node*>(nodeGraphicsObject->node().nodeDataModel());

              assert(node);

              if (node->name() == QStringLiteral("MasterMaterialOutput"))
              {
                  LOG_WARN("Cannot delete the MasterMaterialOutput");
                  return;
              }

                isDeletingTheDetailedNode |= node->isDetailedNode();
            }
        }

        if (isDeletingTheDetailedNode) m_detailedNode = nullptr;
    }

    void FlowView::mousePressEvent(QMouseEvent * event)
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
        QtNodes::FlowView::mousePressEvent(event);
    }
}