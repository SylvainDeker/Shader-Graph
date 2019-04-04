#ifndef SHADERGRAPH_WIDGETNODEEDITOR_H
#define SHADERGRAPH_WIDGETNODEEDITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTreeWidget>

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/ConnectionStyle>
#include <nodes/TypeConverter>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>

#include <core/Core.h>

#include "nodeeditor/NodeGraphicsView.h"
#include "../model/output/MasterMaterialOutput.h"

// TODO : Do not do that
using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::ConnectionStyle;

class WidgetNodeEditor : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetNodeEditor(QWidget *parent = nullptr);

    ~WidgetNodeEditor() override = default;

    inline FlowScene * getScene()   { return m_scene; }
    inline FlowView * getFlowView() { return m_graphicsView; }
    inline ShaderGraph::MasterMaterialOutput * getMasterMaterialOutput()
                { return m_masterMaterialOutput; }

    inline void setDetailsTree(QTreeWidget * tree) { m_graphicsView->setDetailsTree(tree); }

private:
    FlowScene           * m_scene;
    NodeGraphicsView    * m_graphicsView;

    QVBoxLayout * m_layout;
    ShaderGraph::MasterMaterialOutput * m_masterMaterialOutput;

};


#endif //SHADERGRAPH_WIDGETNODEEDITOR_H
