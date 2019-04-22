#ifndef SHADERGRAPH_FLOWVIEW_H
#define SHADERGRAPH_FLOWVIEW_H

#include <list>

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <nodes/Node>
#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/ConnectionStyle>
#include <nodes/TypeConverter>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>

#include <core/Core.h>

#include "model/Node.h"
#include "FlowScene.h"

namespace ShaderGraph
{
    class FlowView : public QtNodes::FlowView
    {
    Q_OBJECT

    public:
        explicit FlowView(QWidget *parent = Q_NULLPTR);

        explicit FlowView(QtNodes::FlowScene *scene, QWidget *parent = Q_NULLPTR);

        inline void setDetailsTree(QTreeWidget * tree) { m_detailsTree = tree; }

    public Q_SLOTS:

        void onNodeDeleted(QtNodes::Node &n);

    protected:

        void mousePressEvent(QMouseEvent *event) override;

    private:
        QTreeWidget * m_detailsTree;
        ShaderGraph::Node * m_detailedNode = nullptr;

    };
}

#endif // SHADERGRAPH_FLOWVIEW_H
