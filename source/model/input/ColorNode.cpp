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
            Node("Color", "Color"),

            m_embeddedWidget(new QWidget()),

            m_rSpinBox(new QDoubleSpinBox),
            m_gSpinBox(new QDoubleSpinBox),
            m_bSpinBox(new QDoubleSpinBox),
            m_aSpinBox(new QDoubleSpinBox),

            m_isUniform(new QCheckBox),
            m_uniformName(new QLineEdit)
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

        connect(m_rSpinBox, SPINBOX_VALUE_CHANGED_SLOT, this, &ColorNode::onColorValueChanged);
        connect(m_gSpinBox, SPINBOX_VALUE_CHANGED_SLOT, this, &ColorNode::onColorValueChanged);
        connect(m_bSpinBox, SPINBOX_VALUE_CHANGED_SLOT, this, &ColorNode::onColorValueChanged);
        connect(m_aSpinBox, SPINBOX_VALUE_CHANGED_SLOT, this, &ColorNode::onColorValueChanged);

        connect(m_isUniform, &QCheckBox::stateChanged, this, &ColorNode::onIsUniformValueChanged);


        m_uniformName->setMinimumSize(100, 20);
        m_uniformName->setMaximumSize(200, 20);
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

    void  ColorNode::onColorValueChanged(double value)
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

    void ColorNode::onIsUniformValueChanged(int check)
    {
        if (check == Qt::Checked)
        {
            LOG_DEBUG("{0} is now a uniform", getID());
        }
        else
        {
            LOG_DEBUG("{0} is no longer a uniform", getID());
        }
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

    void ColorNode::showDetails(QTreeWidget * tree)
    {
        if (!m_isDetailBuilt)
        {
            m_isDetailBuilt = true;

            m_colorDetails = DetailNode(tree, "Color", this);

            m_colorLeaf = DetailColor(m_rSpinBox,
                                      m_gSpinBox,
                                      m_bSpinBox,
                                      m_aSpinBox,
                                      m_colorDetails.QNode(),
                                      "RGBA",
                                      this);

            m_uniformLeaf = DetailUniform(m_isUniform,
                                          m_uniformName,
                                          m_colorDetails.QNode(),
                                          "Uniform",
                                          this);
        }
        else
        {
            m_colorDetails.show();
        }
        Node::showDetails(tree);
    }

    void ColorNode::hideDetails(QTreeWidget * tree)
    {
        m_colorDetails.hide();
        Node::hideDetails(tree);
    }
}
