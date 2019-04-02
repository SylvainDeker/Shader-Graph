#ifndef SHADERGRAPH_DETAILBOOL_H
#define SHADERGRAPH_DETAILBOOL_H

#include "../DetailLeaf.h"

#include <QCheckBox>

#include <core/Core.h>

#include "../DetailNode.h"

namespace ShaderGraph
{
    class DetailBool : public DetailLeaf
    {
    public:
        /// Default Constructor.
        DetailBool() = default;

        /// Constructor :
        /// Construct a Scalar Item.
        /// @node : the leaf parent.
        /// @tree : the root of this leaf.
        /// @parent : The node to detail.
        explicit DetailBool(QCheckBox * checkBox,
                            QTreeWidgetItem * node,
                            QString name,
                            QtNodes::NodeDataModel * nodeDataModel = nullptr,
                            QColor textColor = QColor("white")) :
                DetailLeaf(node, name, nodeDataModel, textColor),
                m_checkBox(checkBox)
        {
            node->treeWidget()->setItemWidget(getItem(), 0, m_checkBox);
        }

        /// Destructor.
        ~DetailBool() override = default;

    private:
        QCheckBox * m_checkBox = nullptr;

    };
}

#endif //SHADERGRAPH_DETAILBOOL_H
