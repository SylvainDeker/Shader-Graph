#ifndef SHADERGRAPH_WIDGETNODEEDITOR_H
#define SHADERGRAPH_WIDGETNODEEDITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/ConnectionStyle>
#include <nodes/TypeConverter>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>
#include <core/Core.h>
#include "NodeGraphicsView.h"
#include "../model/output/MasterMaterialOutput.h"


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

    inline FlowScene * getScene()   { return m_scene; }
    inline FlowView * getFlowView() { return m_graphicsView; }
    inline ShaderGraph::MasterMaterialOutput * getMasterMaterialOutput()
                { return m_masterMaterialOutput; }

    void setAssociatedDetailsLayout(QVBoxLayout * layout);


private:
    FlowScene   * m_scene;
    NodeGraphicsView    * m_graphicsView;
    QVBoxLayout * m_layout;
    ShaderGraph::MasterMaterialOutput * m_masterMaterialOutput;
};


#endif //SHADERGRAPH_WIDGETNODEEDITOR_H
