#ifndef SHADERGRAPH_DETAILVECTOR_H
#define SHADERGRAPH_DETAILVECTOR_H

#include <core/Core.h>

#include "../DetailNode.h"

#include "DetailScalar.h"

namespace ShaderGraph
{
    class DetailVector2 : public DetailNode
    {
    public:
        /// Default Constructor.
        DetailVector2() = default;

        /// Constructor :
        /// Construct a Vector2 Item.
        /// @node : the leaf parent.
        /// @tree : the root of this leaf.
        /// @parent : The node to detail.
        explicit DetailVector2(QDoubleSpinBox * spinBoxX,
                               QDoubleSpinBox * spinBoxY,
                               QTreeWidgetItem * node,
                               QString name,
                               QtNodes::NodeDataModel * nodeDataModel = nullptr,
                               QColor textColor = QColor("white")) :
                DetailNode(node, name, nodeDataModel, textColor)
        {
            m_x = DetailScalar(spinBoxX, QNode(), "X", nodeDataModel);
            m_y = DetailScalar(spinBoxY, QNode(), "Y", nodeDataModel);
        }

        /// Destructor.
        ~DetailVector2() override = default;

    private:
        DetailScalar m_x;
        DetailScalar m_y;
    };

    class DetailVector3 : public DetailNode
    {
    public:
        /// Default Constructor.
        DetailVector3() = default;

        /// Constructor :
        /// Construct a Vector3 Item.
        /// @node : the leaf parent.
        /// @tree : the root of this leaf.
        /// @parent : The node to detail.
        explicit DetailVector3(QDoubleSpinBox * spinBoxX,
                               QDoubleSpinBox * spinBoxY,
                               QDoubleSpinBox * spinBoxZ,
                               QTreeWidgetItem * node,
                               QString name,
                               QtNodes::NodeDataModel * nodeDataModel = nullptr,
                               QColor textColor = QColor("white")) :
                DetailNode(node, name, nodeDataModel, textColor)
        {
            m_x = DetailScalar(spinBoxX, QNode(), "X", nodeDataModel);
            m_y = DetailScalar(spinBoxY, QNode(), "Y", nodeDataModel);
            m_z = DetailScalar(spinBoxZ, QNode(), "Z", nodeDataModel);
        }

        /// Destructor.
        ~DetailVector3() override = default;

    private:
        DetailScalar m_x;
        DetailScalar m_y;
        DetailScalar m_z;
    };

    class DetailVector4 : public DetailNode
    {
    public:
        /// Default Constructor.
        DetailVector4() = default;

        /// Constructor :
        /// Construct a Vector4 Item.
        /// @node : the leaf parent.
        /// @tree : the root of this leaf.
        /// @parent : The node to detail.
        explicit DetailVector4(QDoubleSpinBox * spinBoxX,
                               QDoubleSpinBox * spinBoxY,
                               QDoubleSpinBox * spinBoxZ,
                               QDoubleSpinBox * spinBoxW,
                               QTreeWidgetItem * node,
                               QString name,
                               QtNodes::NodeDataModel * nodeDataModel = nullptr,
                               QColor textColor = QColor("white")) :
                DetailNode(node, name, nodeDataModel, textColor)
        {
            m_x = DetailScalar(spinBoxX, QNode(), "X", nodeDataModel);
            m_y = DetailScalar(spinBoxY, QNode(), "Y", nodeDataModel);
            m_z = DetailScalar(spinBoxZ, QNode(), "Z", nodeDataModel);
            m_w = DetailScalar(spinBoxW, QNode(), "W", nodeDataModel);
        }

        /// Destructor.
        ~DetailVector4() override = default;

    private:
        DetailScalar m_x;
        DetailScalar m_y;
        DetailScalar m_z;
        DetailScalar m_w;
    };

    class DetailColor : public DetailNode
    {
    public:
        /// Default Constructor.
        DetailColor() = default;

        /// Constructor :
        /// Construct a Color Item.
        /// @node : the leaf parent.
        /// @tree : the root of this leaf.
        /// @parent : The node to detail.
        explicit DetailColor(QDoubleSpinBox * spinBoxX,
                               QDoubleSpinBox * spinBoxY,
                               QDoubleSpinBox * spinBoxZ,
                               QDoubleSpinBox * spinBoxW,
                               QTreeWidgetItem * node,
                               QString name,
                               QtNodes::NodeDataModel * nodeDataModel = nullptr,
                               QColor textColor = QColor("white")) :
                DetailNode(node, name, nodeDataModel, textColor)
        {
            m_x = DetailScalar(spinBoxX, QNode(), "R", nodeDataModel);
            m_y = DetailScalar(spinBoxY, QNode(), "G", nodeDataModel);
            m_z = DetailScalar(spinBoxZ, QNode(), "B", nodeDataModel);
            m_w = DetailScalar(spinBoxW, QNode(), "A", nodeDataModel);
        }

        /// Destructor.
        ~DetailColor() override = default;

    private:
        DetailScalar m_x;
        DetailScalar m_y;
        DetailScalar m_z;
        DetailScalar m_w;
    };
}

#endif //SHADERGRAPH_DETAILUNIFORM_H
