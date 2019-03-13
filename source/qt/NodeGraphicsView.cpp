#include "NodeGraphicsView.h"

NodeGraphicsView::NodeGraphicsView(QWidget *parent) :
    FlowView(parent)
{

}

NodeGraphicsView::NodeGraphicsView(QtNodes::FlowScene *scene, QWidget *parent) :
    FlowView(scene,parent)
{

}


void NodeGraphicsView::mousePressEvent(QMouseEvent *event)
{
  FlowView::mousePressEvent(event);
}
