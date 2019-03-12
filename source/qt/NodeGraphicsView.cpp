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
    FlowView(scene,parent),
    m_detailslayout(nullptr)
{

}


void NodeGraphicsView::mousePressEvent(QMouseEvent *event)
{
  std::vector<QtNodes::Node*> nodes =  scene()->selectedNodes();

  if(nodes.size()>0){

      // QLayoutItem *item;
      // while ((item = m_detailslayout->takeAt(0))) delete item;

      ShaderGraph::Node * md;
      for (size_t i = 0; i < nodes.size(); i++) {
        md =  static_cast<ShaderGraph::Node *>(nodes[i]->nodeDataModel());
        md->showDetails(m_detailslayout);
      }

  }


  FlowView::mousePressEvent(event);
}
