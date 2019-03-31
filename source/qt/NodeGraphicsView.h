#ifndef SHADERGRAPH_NODEGRAPHICSVIEW_H
#define SHADERGRAPH_NODEGRAPHICSVIEW_H

#include <list>

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>

#include <nodes/Node>
#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/ConnectionStyle>
#include <nodes/TypeConverter>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>

// WIP

#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <core/Core.h>

#include "../model/Node.h"

class NodeGraphicsView : public QtNodes::FlowView {

  Q_OBJECT

public:
  NodeGraphicsView(QWidget *parent = Q_NULLPTR);

  NodeGraphicsView(QtNodes::FlowScene *scene, QWidget *parent = Q_NULLPTR);

  inline void setDetailsTree(QTreeWidget * tree) { m_detailsTree = tree; }

protected:
  void mousePressEvent(QMouseEvent *event) override;

private:
    QTreeWidget * m_detailsTree;
    ShaderGraph::Node * m_detailedNode = nullptr;

};


#endif // SHADERGRAPH_NODEGRAPHICSVIEW_H
