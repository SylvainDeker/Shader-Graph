#ifndef SHADERGRAPH_DETAILLEAF_H
#define SHADERGRAPH_DETAILLEAF_H

#include <QColor>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <nodes/NodeDataModel>

#include <core/Core.h>

#include "../pin/IPin.h"

namespace ShaderGraph
{
    class DetailLeaf
    {
    public:
        /// Default Constructor.
        DetailLeaf() = default;

        /// Constructor :
        /// Construct a node of a sub-tree.
        /// @tree : the root of this leaf.
        /// @name : the name of this leaf.
        /// @parent : The node to detail.
        explicit DetailLeaf(QTreeWidgetItem * root,
                            QString name,
                            QtNodes::NodeDataModel * nodeDataModel = nullptr,
                            QColor textColor = QColor("white")) :
                m_name(name),
                m_nodeDataModel(nodeDataModel)
        {
            m_node = new QTreeWidgetItem(root);
            m_node->setText(0, name);
            m_node->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_node->setTextColor(0, textColor);
            m_node->setExpanded(true);

            m_item = new QTreeWidgetItem(m_node);
        }

        /// Destructor.
        virtual ~DetailLeaf() = default;

        /// Display this hidden pin in the TreeWidget.
        inline void show() { m_item->setHidden(false); }

        /// Hide this hidden pin from the TreeWidget.
        void hide() { m_item->setHidden(true); }

        /// Getter : The item.
        inline QTreeWidgetItem * getItem() { return m_item; }

        /// Getter : The parent.
        inline QtNodes::NodeDataModel * getNodeDataModel() { return m_nodeDataModel; }

        /// Getter : The name.
        inline const QString& getName() const { return m_name; }

    private:
        /// The name of this leaf.
        QString m_name;

        /// The node to detail.
        QtNodes::NodeDataModel * m_nodeDataModel;

        /// The root of this subtree.
        QTreeWidgetItem * m_node;

        /// The item.
        QTreeWidgetItem * m_item;
    };
}

#endif //SHADERGRAPH_DETAILLEAF_H
