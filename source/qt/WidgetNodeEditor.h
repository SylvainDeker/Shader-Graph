#ifndef SHADERGRAPH_WIDGETNODEEDITOR_H
#define SHADERGRAPH_WIDGETNODEEDITOR_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/ConnectionStyle>
#include <nodes/TypeConverter>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>

#include "../core/Core.h"

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::ConnectionStyle;

class WidgetNodeEditor : public QWidget
{
    Q_OBJECT
public:
    WidgetNodeEditor(QWidget *parent = nullptr);
    ~WidgetNodeEditor() = default;

private:
    FlowScene   * m_scene;
    FlowView    * m_graphicsView;
    QVBoxLayout * m_layout;
};


#endif //SHADERGRAPH_WIDGETNODEEDITOR_H
