#ifndef SHADERGRAPH_DETAILSCALAR_H
#define SHADERGRAPH_DETAILSCALAR_H

#include "../DetailLeaf.h"

#include <QDoubleSpinBox>

#include <core/Core.h>

#include "../DetailNode.h"

namespace ShaderGraph
{
    class DetailScalar : public DetailLeaf
    {
    public:
        /// Default Constructor.
        DetailScalar() = default;

        /// Constructor :
        /// Construct a Scalar Item.
        /// @node : the leaf parent.
        /// @tree : the root of this leaf.
        /// @parent : The node to detail.
        explicit DetailScalar(QDoubleSpinBox * spinBox,
                              QTreeWidgetItem * node,
                              QString name,
                              QtNodes::NodeDataModel * nodeDataModel = nullptr,
                              QColor textColor = QColor("white")) :
                DetailLeaf(node, name, nodeDataModel, textColor),
                m_spinBox(spinBox)
        {
            node->treeWidget()->setItemWidget(getItem(), 0, m_spinBox);
        }

        /// Destructor.
        ~DetailScalar() override = default;

    private:
        QDoubleSpinBox * m_spinBox;

    };
}

#endif //SHADERGRAPH_DETAILSCALAR_H
