#ifndef SHADERGRAPH_WIDGETNODEEDITOR_H
#define SHADERGRAPH_WIDGETNODEEDITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTreeWidget>
#include <QTreeWidget>

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/ConnectionStyle>
#include <nodes/TypeConverter>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>

#include <core/Core.h>

#include "nodeeditor/FlowScene.h"
#include "nodeeditor/FlowView.h"

#include "../model/output/MasterMaterialOutput.h"

class WidgetNodeEditor : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetNodeEditor(QWidget * parent = nullptr);

    ~WidgetNodeEditor() override = default;

    inline ShaderGraph::FlowScene * getScene()   { return m_scene; }
    inline ShaderGraph::FlowView * getFlowView() { return m_flowView; }
    inline ShaderGraph::MasterMaterialOutput * getMasterMaterialOutput() { return m_masterMaterialOutput; }

    inline void setDetailsTree(QTreeWidget * tree) { m_flowView->setDetailsTree(tree); }

private:
    ShaderGraph::FlowScene              * m_scene;
    ShaderGraph::FlowView               * m_flowView;
    QVBoxLayout                         * m_layout;
    ShaderGraph::MasterMaterialOutput   * m_masterMaterialOutput;
};


#endif //SHADERGRAPH_WIDGETNODEEDITOR_H
