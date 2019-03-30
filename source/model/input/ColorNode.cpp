#include "ColorNode.h"

#include <QString>
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFrame>
#include <QColorDialog>

#include <QTreeWidgetItem>

namespace ShaderGraph
{
    ColorNode::ColorNode() :
            InputNode("Color", "Color"),

            m_embeddedWidget(new QWidget()),

            m_rSpinBox(new QDoubleSpinBox()),
            m_gSpinBox(new QDoubleSpinBox()),
            m_bSpinBox(new QDoubleSpinBox()),
            m_aSpinBox(new QDoubleSpinBox())
    {
        outputs() = std::vector<PIN> {
                std::make_shared<Vector4>("RGBA", this),  // RGBA
                std::make_shared<Float>("R",      this),  // Red channel
                std::make_shared<Float>("G",      this),  // Green channel
                std::make_shared<Float>("B",      this),  // Blue channel
                std::make_shared<Float>("A",      this)   // Alpha channel
        };

        setColor(DEFAULT_COLOR);
        m_embeddedWidget->setPalette(QPalette(DEFAULT_COLOR));
        m_embeddedWidget->setFixedSize(IMAGE_NODE_SIZE, IMAGE_NODE_SIZE);
        m_embeddedWidget->installEventFilter(this);

        m_rSpinBox->setRange(0,1);
        m_gSpinBox->setRange(0,1);
        m_bSpinBox->setRange(0,1);
        m_aSpinBox->setRange(0,1);

        m_rSpinBox->setSingleStep(0.1);
        m_gSpinBox->setSingleStep(0.1);
        m_bSpinBox->setSingleStep(0.1);
        m_aSpinBox->setSingleStep(0.1);

        connect(m_rSpinBox, SPINBOX_VALUE_CHANGED_SLOT, this, &ColorNode::onValueChanged);
        connect(m_gSpinBox, SPINBOX_VALUE_CHANGED_SLOT, this, &ColorNode::onValueChanged);
        connect(m_bSpinBox, SPINBOX_VALUE_CHANGED_SLOT, this, &ColorNode::onValueChanged);
        connect(m_aSpinBox, SPINBOX_VALUE_CHANGED_SLOT, this, &ColorNode::onValueChanged);

    }

    bool ColorNode::eventFilter(QObject * object, QEvent * event)
    {
        if (object == m_embeddedWidget && event->type() == QEvent::MouseButtonPress)
        {
            setColor(QColorDialog::getColor(m_color));
            return true;
        }
        return false;
    }

    void  ColorNode::onValueChanged(double value)
    {
        (void) value; // This event update each field, to make this event more generic.

        glm::vec4 color = {
                static_cast<float>(m_rSpinBox->value()),
                static_cast<float>(m_gSpinBox->value()),
                static_cast<float>(m_bSpinBox->value()),
                static_cast<float>(m_aSpinBox->value())
        };

        setColor(color);
    }


    void ColorNode::setColor(const glm::vec4 &color)
    {
        // Cast the glm::vec4 to QColor.
        QColor qColor;
        qColor.setRedF(color.r);
        qColor.setGreenF(color.g);
        qColor.setBlueF(color.b);
        qColor.setAlphaF(color.a);

        // Update the color.
        setColor(qColor);
    }

    void ColorNode::setColor(const QColor &color)
    {
        // Set the variable
        m_color = color;

        // Update the widget
        m_embeddedWidget->setPalette(color);

        // Update the spin boxes
        m_rSpinBox->setValue(color.redF());
        m_gSpinBox->setValue(color.greenF());
        m_bSpinBox->setValue(color.blueF());
        m_aSpinBox->setValue(color.alphaF());
    }

    void ColorNode::showDetails(QVBoxLayout * layout)
    {
        (void) layout;
    }

    void ColorNode::showDetails(QTreeWidget * tree)
    {
        if (m_rgbaSection == nullptr)
        {
            // RGBA section
            m_rgbaSection = new QTreeWidgetItem(tree);
            m_rgbaSection->setText(0, "RGBA");
            m_rgbaSection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_rgbaSection->setTextColor(0, QColor("white"));
            m_rgbaSection->setExpanded(true);

            // Red Channel section
            m_rSection = new QTreeWidgetItem(m_rgbaSection);
            m_rSection->setText(0, "Red Channel");
            m_rSection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_rSection->setTextColor(0, QColor("white"));
            m_rSection->setExpanded(true);
            // Red Channel item
            m_rItem = new QTreeWidgetItem(m_rSection);
            tree->setItemWidget(m_rItem, 0, m_rSpinBox);

            // Green Channel section
            m_gSection = new QTreeWidgetItem(m_rgbaSection);
            m_gSection->setText(0, "Green Channel");
            m_gSection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_gSection->setTextColor(0, QColor("white"));
            m_gSection->setExpanded(true);
            // Green Channel item
            m_gItem = new QTreeWidgetItem(m_gSection);
            tree->setItemWidget(m_gItem, 0, m_gSpinBox);

            // Blue Channel section
            m_bSection = new QTreeWidgetItem(m_rgbaSection);
            m_bSection->setText(0, "Blue Channel");
            m_bSection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_bSection->setTextColor(0, QColor("white"));
            m_bSection->setExpanded(true);
            // Blue Channel item
            m_bItem = new QTreeWidgetItem(m_bSection);
            tree->setItemWidget(m_bItem, 0, m_bSpinBox);

            // Alpha Channel section
            m_aSection = new QTreeWidgetItem(m_rgbaSection);
            m_aSection->setText(0, "Alpha Channel");
            m_aSection->setData(0, Qt::UserRole, QStringLiteral("skip me"));
            m_aSection->setTextColor(0, QColor("white"));
            m_aSection->setExpanded(true);
            // Alpha Channel item
            m_aItem = new QTreeWidgetItem(m_aSection);
            tree->setItemWidget(m_aItem, 0, m_aSpinBox);
        }
        else
        {
            m_rgbaSection->setHidden(false);
        }

        Node::showDetails(tree);
    }

    void ColorNode::hideDetails(QTreeWidget * tree)
    {
        m_rgbaSection->setHidden(true);

        Node::hideDetails(tree);
    }
}
