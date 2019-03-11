#include "NodeGraphicsView.h"

NodeGraphicsView::
NodeGraphicsView(QWidget *parent):
    FlowView(parent)
{

}

NodeGraphicsView::
NodeGraphicsView(QtNodes::FlowScene *scene, QWidget *parent):
    FlowView(scene,parent)
{

}


void
NodeGraphicsView::
mousePressEvent(QMouseEvent *event)
{
  std::vector<QtNodes::Node*> nodes =  scene()->selectedNodes();

  if(nodes.size()>0){
      QtNodes::Node * n;
      QtNodes::NodeDataModel * md;
      // TODO
      std::string cat;
      cat +=  "Node selected: ";
      for (size_t i = 0; i < nodes.size(); i++) {
        n = nodes[i];
        cat += std::to_string((unsigned long long int) (n)); // just to show ptr
        // FIXME (sylvain) following line doesn't compile and I dunno why.  I suspect the 'const' in the getter but not sure at all.
        // md =  n->nodeDataModel();
      }
      cat += '\n';
      LOG_INFO(cat);
  }


  FlowView::mousePressEvent(event);













}
