#ifndef SHADERGRAPH_DETAILTEXT_H
#define SHADERGRAPH_DETAILTEXT_H

#include "../DetailLeaf.h"

#include <QLineEdit>

#include <core/Core.h>

#include "../DetailNode.h"

namespace ShaderGraph
{
    class DetailText : public DetailLeaf
    {
    public:
        /// Default Constructor.
        DetailText() = default;

        /// Constructor :
        /// Construct a Scalar Item.
        /// @node : the leaf parent.
        /// @tree : the root of this leaf.
        /// @parent : The node to detail.
        explicit DetailText(QLineEdit * textField,
                            QTreeWidgetItem * node,
                            QString name,
                            QtNodes::NodeDataModel * nodeDataModel = nullptr,
                            QColor textColor = QColor("white")) :
                DetailLeaf(node, name, nodeDataModel, textColor),
                m_textField(textField)
        {
            node->treeWidget()->setItemWidget(getItem(), 0, m_textField);
        }

        /// Destructor.
        ~DetailText() override = default;

    private:
        QLineEdit * m_textField = nullptr;

    };
}

#endif //SHADERGRAPH_DETAILTEXT_H
