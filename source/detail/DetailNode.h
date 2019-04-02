#ifndef SHADERGRAPH_DETAILNODE_H
#define SHADERGRAPH_DETAILNODE_H

#include <QColor>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <nodes/NodeDataModel>

#include <core/Core.h>

#include "../pin/IPin.h"

namespace ShaderGraph
{
    class DetailNode
    {
    public:
        /// Default Constructor.
        DetailNode() = default;

        /// Constructor :
        /// Construct a node of a sub-tree.
        /// @tree : the root of this node.
        /// @name : the name of this node.
        /// @parent : The node to detail.
        explicit DetailNode(QTreeWidgetItem * root,
                            QString name,
                            QtNodes::NodeDataModel * nodeDataModel = nullptr,
                            QColor textColor = QColor("white")) :
            m_name(name),
            m_isRoot(false),
            m_nodeDataModel(nodeDataModel)
        {
            m_node = new QTreeWidgetItem(root);
            m_node->setText(0, name);
            m_node->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_node->setTextColor(0, textColor);
            m_node->setExpanded(true);
        }

        /// Constructor :
        /// Construct a sub-tree.
        /// @tree : The root of this subtree.
        /// @name : The name of this subtree.
        /// @parent : The node to detail.
        explicit DetailNode(QTreeWidget * root,
                            QString name,
                            QtNodes::NodeDataModel * nodeDataModel = nullptr,
                            QColor textColor = QColor("white")) :
                m_name(name),
                m_isRoot(true),
                m_nodeDataModel(nodeDataModel)
        {
            m_node = new QTreeWidgetItem(root);
            m_node->setText(0, name);
            m_node->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_node->setTextColor(0, textColor);
            m_node->setExpanded(true);
        }

        /// Destructor.
        virtual ~DetailNode() = default;

        /// Display this hidden pin in the TreeWidget.
        inline void show() { m_node->setHidden(false); }

        /// Hide this hidden pin from the TreeWidget.
        void hide() { m_node->setHidden(true); }


        /// Getter : The root of this subtree.
        inline QTreeWidgetItem * QNode() { return m_node; }

        /// Gettet : The name of this node.
        inline const QString& getName() const { return m_name; }

        /// Getter : The parent.
        inline QtNodes::NodeDataModel * getNodeDataModel() { return m_nodeDataModel; }

        inline bool isRoot() const { return m_isRoot; }

    private:
        /// The name of this node.
        QString m_name;

        /// The parent of this node.
        QTreeWidgetItem * m_node;

        /// Is this sub-tree a the root ?
        bool m_isRoot;

        /// The node to detail.
        QtNodes::NodeDataModel * m_nodeDataModel;
    };
}

#endif //SHADERGRAPH_DETAILNODE_H
