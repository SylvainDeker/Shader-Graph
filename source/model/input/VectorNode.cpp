#include "VectorNode.h"

namespace ShaderGraph
{
    //====================================================================================================
    // Scalar Node
    //====================================================================================================

    ScalarNode::ScalarNode() :
            Node("Scalar", "Scalar"),
            m_value(0.f),
            m_embeddedWidget(new QWidget()),
            m_layout(new QBoxLayout(QBoxLayout::TopToBottom, m_embeddedWidget)),

            m_spinBoxX(new QDoubleSpinBox()),
            m_detailsPanelSpinBoxX(new QDoubleSpinBox())
    {

        outputs() = std::vector<PIN>{
                std::make_shared<Float>("Result", this)
        };

        m_layout->addWidget(m_spinBoxX);

        m_spinBoxX->setSingleStep(SPINBOX_STEP);
        m_spinBoxX->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxX->setFixedWidth(WIDGET_NODE_SIZE);

        m_detailsPanelSpinBoxX->setSingleStep(SPINBOX_STEP);
        m_detailsPanelSpinBoxX->setRange(-FLT_MAX, FLT_MAX);
        m_detailsPanelSpinBoxX->setFixedWidth(WIDGET_NODE_SIZE);

        connect(m_spinBoxX, SPINBOX_VALUE_CHANGED_SLOT, this, &ScalarNode::onValueChanged);
        connect(m_detailsPanelSpinBoxX, SPINBOX_VALUE_CHANGED_SLOT, this, &ScalarNode::onDetailValueChanged);
    }

    void ScalarNode::showDetails(QTreeWidget * tree)
    {
        if (m_axisSection == nullptr)
        {
            // Axis section
            m_axisSection = new QTreeWidgetItem(tree);
            m_axisSection->setText(0, "Axis");
            m_axisSection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_axisSection->setTextColor(0, QColor("white"));
            m_axisSection->setExpanded(true);

            // X axis
            m_xSection = new QTreeWidgetItem(m_axisSection);
            m_xSection->setText(0, "X-Axis");
            m_xSection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_xSection->setTextColor(0, QColor("white"));
            m_xSection->setExpanded(true);
            // X axis item
            m_xItem = new QTreeWidgetItem(m_xSection);
            tree->setItemWidget(m_xItem, 0, m_detailsPanelSpinBoxX);
        }
        else
        {
            m_axisSection->setHidden(false);
        }

        Node::showDetails(tree);
    }

    void ScalarNode::hideDetails(QTreeWidget * tree)
    {
        m_axisSection->setHidden(true);

        Node::hideDetails(tree);
    }

    //====================================================================================================
    // Vector2 Node
    //====================================================================================================

    Vec2Node::Vec2Node() :
            Node("Vector2", "Vector2"),
            m_value(glm::vec2(0.f)),
            m_embeddedWidget(new QWidget()),
            m_layout(new QBoxLayout(QBoxLayout::TopToBottom, m_embeddedWidget)),

            m_spinBoxX(new QDoubleSpinBox()),
            m_spinBoxY(new QDoubleSpinBox()),

            m_detailsPanelSpinBoxX(new QDoubleSpinBox()),
            m_detailsPanelSpinBoxY(new QDoubleSpinBox())
    {

        outputs() = std::vector<PIN>{
                std::make_shared<Vector3>("Result", this)
        };

        m_layout->addWidget(m_spinBoxX);
        m_layout->addWidget(m_spinBoxY);

        m_spinBoxX->setSingleStep(SPINBOX_STEP);
        m_spinBoxX->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxX->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxY->setSingleStep(SPINBOX_STEP);
        m_spinBoxY->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxY->setFixedWidth(WIDGET_NODE_SIZE);

        connect(m_spinBoxX, SPINBOX_VALUE_CHANGED_SLOT, this, &Vec2Node::onValueChanged);
        connect(m_spinBoxY, SPINBOX_VALUE_CHANGED_SLOT, this, &Vec2Node::onValueChanged);

        m_detailsPanelSpinBoxX->setSingleStep(SPINBOX_STEP);
        m_detailsPanelSpinBoxX->setRange(-FLT_MAX, FLT_MAX);
        m_detailsPanelSpinBoxX->setFixedWidth(WIDGET_NODE_SIZE);

        m_detailsPanelSpinBoxY->setSingleStep(SPINBOX_STEP);
        m_detailsPanelSpinBoxY->setRange(-FLT_MAX, FLT_MAX);
        m_detailsPanelSpinBoxY->setFixedWidth(WIDGET_NODE_SIZE);

        connect(m_detailsPanelSpinBoxX, SPINBOX_VALUE_CHANGED_SLOT, this, &Vec2Node::onDetailValueChanged);
        connect(m_detailsPanelSpinBoxY, SPINBOX_VALUE_CHANGED_SLOT, this, &Vec2Node::onDetailValueChanged);
    }

    /// Setter : the value of this node.
    void Vec2Node::set(const glm::vec2& value)
    {
        m_value = value;
        m_spinBoxX->setValue(value.x);
        m_spinBoxY->setValue(value.y);

        m_detailsPanelSpinBoxX->setValue(value.x);
        m_detailsPanelSpinBoxY->setValue(value.y);
    }

    void Vec2Node::showDetails(QTreeWidget * tree)
    {
        if (m_axisSection == nullptr)
        {
            // Axis section
            m_axisSection = new QTreeWidgetItem(tree);
            m_axisSection->setText(0, "Axis");
            m_axisSection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_axisSection->setTextColor(0, QColor("white"));
            m_axisSection->setExpanded(true);

            // Red Channel section
            m_xSection = new QTreeWidgetItem(m_axisSection);
            m_xSection->setText(0, "X-Axis");
            m_xSection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_xSection->setTextColor(0, QColor("white"));
            m_xSection->setExpanded(true);
            // Red Channel item
            m_xItem = new QTreeWidgetItem(m_xSection);
            tree->setItemWidget(m_xItem, 0, m_detailsPanelSpinBoxX);

            // Green Channel section
            m_ySection = new QTreeWidgetItem(m_axisSection);
            m_ySection->setText(0, "Y-Axis");
            m_ySection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_ySection->setTextColor(0, QColor("white"));
            m_ySection->setExpanded(true);
            // Green Channel item
            m_yItem = new QTreeWidgetItem(m_ySection);
            tree->setItemWidget(m_yItem, 0, m_detailsPanelSpinBoxY);
        }
        else
        {
            m_axisSection->setHidden(false);
        }

        Node::showDetails(tree);
    }

    void Vec2Node::hideDetails(QTreeWidget * tree)
    {
        m_axisSection->setHidden(true);

        Node::hideDetails(tree);
    }

    //====================================================================================================
    // Vector3 Node
    //====================================================================================================

    Vec3Node::Vec3Node() :
            Node("Vector3", "Vector3"),
            m_value(glm::vec3(0.f)),
            m_embeddedWidget(new QWidget()),
            m_layout(new QBoxLayout(QBoxLayout::TopToBottom, m_embeddedWidget)),

            m_spinBoxX(new QDoubleSpinBox()),
            m_spinBoxY(new QDoubleSpinBox()),
            m_spinBoxZ(new QDoubleSpinBox()),

            m_detailsPanelSpinBoxX(new QDoubleSpinBox()),
            m_detailsPanelSpinBoxY(new QDoubleSpinBox()),
            m_detailsPanelSpinBoxZ(new QDoubleSpinBox())
    {

        outputs() = std::vector<PIN>{
                std::make_shared<Vector3>("Result", this)
        };

        m_layout->addWidget(m_spinBoxX);
        m_layout->addWidget(m_spinBoxY);
        m_layout->addWidget(m_spinBoxZ);

        m_spinBoxX->setSingleStep(SPINBOX_STEP);
        m_spinBoxX->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxX->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxY->setSingleStep(SPINBOX_STEP);
        m_spinBoxY->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxY->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxZ->setSingleStep(SPINBOX_STEP);
        m_spinBoxZ->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxZ->setFixedWidth(WIDGET_NODE_SIZE);

        connect(m_spinBoxX, SPINBOX_VALUE_CHANGED_SLOT, this, &Vec3Node::onValueChanged);
        connect(m_spinBoxY, SPINBOX_VALUE_CHANGED_SLOT, this, &Vec3Node::onValueChanged);
        connect(m_spinBoxZ, SPINBOX_VALUE_CHANGED_SLOT, this, &Vec3Node::onValueChanged);

        m_detailsPanelSpinBoxX->setSingleStep(SPINBOX_STEP);
        m_detailsPanelSpinBoxX->setRange(-FLT_MAX, FLT_MAX);
        m_detailsPanelSpinBoxX->setFixedWidth(WIDGET_NODE_SIZE);

        m_detailsPanelSpinBoxY->setSingleStep(SPINBOX_STEP);
        m_detailsPanelSpinBoxY->setRange(-FLT_MAX, FLT_MAX);
        m_detailsPanelSpinBoxY->setFixedWidth(WIDGET_NODE_SIZE);

        m_detailsPanelSpinBoxZ->setSingleStep(SPINBOX_STEP);
        m_detailsPanelSpinBoxZ->setRange(-FLT_MAX, FLT_MAX);
        m_detailsPanelSpinBoxZ->setFixedWidth(WIDGET_NODE_SIZE);

        connect(m_detailsPanelSpinBoxX, SPINBOX_VALUE_CHANGED_SLOT, this, &Vec3Node::onDetailValueChanged);
        connect(m_detailsPanelSpinBoxY, SPINBOX_VALUE_CHANGED_SLOT, this, &Vec3Node::onDetailValueChanged);
        connect(m_detailsPanelSpinBoxZ, SPINBOX_VALUE_CHANGED_SLOT, this, &Vec3Node::onDetailValueChanged);
    }

    /// Setter : the value of this node.
    void Vec3Node::set(const glm::vec3& value)
    {
        m_value = value;
        m_spinBoxX->setValue(value.x);
        m_spinBoxY->setValue(value.y);
        m_spinBoxZ->setValue(value.z);

        m_detailsPanelSpinBoxX->setValue(value.x);
        m_detailsPanelSpinBoxY->setValue(value.y);
        m_detailsPanelSpinBoxZ->setValue(value.z);
    }

    void Vec3Node::showDetails(QTreeWidget * tree)
    {
        if (m_axisSection == nullptr)
        {
            // Axis section
            m_axisSection = new QTreeWidgetItem(tree);
            m_axisSection->setText(0, "Axis");
            m_axisSection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_axisSection->setTextColor(0, QColor("white"));
            m_axisSection->setExpanded(true);

            // Red Channel section
            m_xSection = new QTreeWidgetItem(m_axisSection);
            m_xSection->setText(0, "X-Axis");
            m_xSection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_xSection->setTextColor(0, QColor("white"));
            m_xSection->setExpanded(true);
            // Red Channel item
            m_xItem = new QTreeWidgetItem(m_xSection);
            tree->setItemWidget(m_xItem, 0, m_detailsPanelSpinBoxX);

            // Green Channel section
            m_ySection = new QTreeWidgetItem(m_axisSection);
            m_ySection->setText(0, "Y-Axis");
            m_ySection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_ySection->setTextColor(0, QColor("white"));
            m_ySection->setExpanded(true);
            // Green Channel item
            m_yItem = new QTreeWidgetItem(m_ySection);
            tree->setItemWidget(m_yItem, 0, m_detailsPanelSpinBoxY);

            // Blue Channel section
            m_zSection = new QTreeWidgetItem(m_axisSection);
            m_zSection->setText(0, "Z-Axis");
            m_zSection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_zSection->setTextColor(0, QColor("white"));
            m_zSection->setExpanded(true);
            // Blue Channel item
            m_zItem = new QTreeWidgetItem(m_zSection);
            tree->setItemWidget(m_zItem, 0, m_detailsPanelSpinBoxZ);
        }
        else
        {
            m_axisSection->setHidden(false);
        }

        Node::showDetails(tree);
    }

    void Vec3Node::hideDetails(QTreeWidget * tree)
    {
        m_axisSection->setHidden(true);

        Node::hideDetails(tree);
    }

    //====================================================================================================
    // Vector4 Node
    //====================================================================================================

    Vec4Node::Vec4Node() :
            Node("Vector4", "Vector4"),
            m_value(glm::vec4(0.f)),
            m_embeddedWidget(new QWidget()),
            m_layout(new QBoxLayout(QBoxLayout::TopToBottom, m_embeddedWidget)),

            m_spinBoxX(new QDoubleSpinBox()),
            m_spinBoxY(new QDoubleSpinBox()),
            m_spinBoxZ(new QDoubleSpinBox()),
            m_spinBoxW(new QDoubleSpinBox()),

            m_detailsPanelSpinBoxX(new QDoubleSpinBox()),
            m_detailsPanelSpinBoxY(new QDoubleSpinBox()),
            m_detailsPanelSpinBoxZ(new QDoubleSpinBox()),
            m_detailsPanelSpinBoxW(new QDoubleSpinBox())
    {

        outputs() = std::vector<PIN>{
                std::make_shared<Vector4>("Result", this)
        };

        m_layout->addWidget(m_spinBoxX);
        m_layout->addWidget(m_spinBoxY);
        m_layout->addWidget(m_spinBoxZ);
        m_layout->addWidget(m_spinBoxW);

        m_spinBoxX->setSingleStep(SPINBOX_STEP);
        m_spinBoxX->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxX->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxY->setSingleStep(SPINBOX_STEP);
        m_spinBoxY->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxY->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxZ->setSingleStep(SPINBOX_STEP);
        m_spinBoxZ->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxZ->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxW->setSingleStep(SPINBOX_STEP);
        m_spinBoxW->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxW->setFixedWidth(WIDGET_NODE_SIZE);

        connect(m_spinBoxX, SPINBOX_VALUE_CHANGED_SLOT, this, &Vec4Node::onValueChanged);
        connect(m_spinBoxY, SPINBOX_VALUE_CHANGED_SLOT, this, &Vec4Node::onValueChanged);
        connect(m_spinBoxZ, SPINBOX_VALUE_CHANGED_SLOT, this, &Vec4Node::onValueChanged);
        connect(m_spinBoxW, SPINBOX_VALUE_CHANGED_SLOT, this, &Vec4Node::onValueChanged);

        m_detailsPanelSpinBoxX->setSingleStep(SPINBOX_STEP);
        m_detailsPanelSpinBoxX->setRange(-FLT_MAX, FLT_MAX);
        m_detailsPanelSpinBoxX->setFixedWidth(WIDGET_NODE_SIZE);

        m_detailsPanelSpinBoxY->setSingleStep(SPINBOX_STEP);
        m_detailsPanelSpinBoxY->setRange(-FLT_MAX, FLT_MAX);
        m_detailsPanelSpinBoxY->setFixedWidth(WIDGET_NODE_SIZE);

        m_detailsPanelSpinBoxZ->setSingleStep(SPINBOX_STEP);
        m_detailsPanelSpinBoxZ->setRange(-FLT_MAX, FLT_MAX);
        m_detailsPanelSpinBoxZ->setFixedWidth(WIDGET_NODE_SIZE);

        m_detailsPanelSpinBoxW->setSingleStep(SPINBOX_STEP);
        m_detailsPanelSpinBoxW->setRange(-FLT_MAX, FLT_MAX);
        m_detailsPanelSpinBoxW->setFixedWidth(WIDGET_NODE_SIZE);

        connect(m_detailsPanelSpinBoxX, SPINBOX_VALUE_CHANGED_SLOT, this, &Vec4Node::onDetailValueChanged);
        connect(m_detailsPanelSpinBoxY, SPINBOX_VALUE_CHANGED_SLOT, this, &Vec4Node::onDetailValueChanged);
        connect(m_detailsPanelSpinBoxZ, SPINBOX_VALUE_CHANGED_SLOT, this, &Vec4Node::onDetailValueChanged);
        connect(m_detailsPanelSpinBoxW, SPINBOX_VALUE_CHANGED_SLOT, this, &Vec4Node::onDetailValueChanged);
    }

    /// Setter : the value of this node.
    void Vec4Node::set(const glm::vec4& value)
    {
        m_value = value;
        m_spinBoxX->setValue(value.x);
        m_spinBoxY->setValue(value.y);
        m_spinBoxZ->setValue(value.z);
        m_spinBoxW->setValue(value.w);

        m_detailsPanelSpinBoxX->setValue(value.x);
        m_detailsPanelSpinBoxY->setValue(value.y);
        m_detailsPanelSpinBoxZ->setValue(value.z);
        m_detailsPanelSpinBoxW->setValue(value.w);
    }

    void Vec4Node::showDetails(QTreeWidget * tree)
    {
        if (m_axisSection == nullptr)
        {
            // Axis section
            m_axisSection = new QTreeWidgetItem(tree);
            m_axisSection->setText(0, "Axis");
            m_axisSection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_axisSection->setTextColor(0, QColor("white"));
            m_axisSection->setExpanded(true);

            // Red Channel section
            m_xSection = new QTreeWidgetItem(m_axisSection);
            m_xSection->setText(0, "X-Axis");
            m_xSection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_xSection->setTextColor(0, QColor("white"));
            m_xSection->setExpanded(true);
            // Red Channel item
            m_xItem = new QTreeWidgetItem(m_xSection);
            tree->setItemWidget(m_xItem, 0, m_detailsPanelSpinBoxX);

            // Green Channel section
            m_ySection = new QTreeWidgetItem(m_axisSection);
            m_ySection->setText(0, "Y-Axis");
            m_ySection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_ySection->setTextColor(0, QColor("white"));
            m_ySection->setExpanded(true);
            // Green Channel item
            m_yItem = new QTreeWidgetItem(m_ySection);
            tree->setItemWidget(m_yItem, 0, m_detailsPanelSpinBoxY);

            // Blue Channel section
            m_zSection = new QTreeWidgetItem(m_axisSection);
            m_zSection->setText(0, "Z-Axis");
            m_zSection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_zSection->setTextColor(0, QColor("white"));
            m_zSection->setExpanded(true);
            // Blue Channel item
            m_zItem = new QTreeWidgetItem(m_zSection);
            tree->setItemWidget(m_zItem, 0, m_detailsPanelSpinBoxZ);

            // Alpha Channel section
            m_wSection = new QTreeWidgetItem(m_axisSection);
            m_wSection->setText(0, "W-Axis");
            m_wSection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_wSection->setTextColor(0, QColor("white"));
            m_wSection->setExpanded(true);
            // Alpha Channel item
            m_wItem = new QTreeWidgetItem(m_wSection);
            tree->setItemWidget(m_wItem, 0, m_detailsPanelSpinBoxW);
        }
        else
        {
            m_axisSection->setHidden(false);
        }

        Node::showDetails(tree);
    }

    void Vec4Node::hideDetails(QTreeWidget * tree)
    {
        m_axisSection->setHidden(true);

        Node::hideDetails(tree);
    }
}
