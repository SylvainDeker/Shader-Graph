#include "ColorNode.h"

#include <QString>
#include <QMessageBox>

namespace ShaderGraph
{
    ColorNode::ColorNode() :
            InputNode("Color", "Color"),

            m_embeddedWidget(new QWidget())
    {
        outputs() = std::vector<PIN >{
                std::make_shared<Vector4>("RGBA"), // RGBA
                std::make_shared<Float>("R"),   // Red channel
                std::make_shared<Float>("G"),   // Green channel
                std::make_shared<Float>("B"),   // Blue channel
                std::make_shared<Float>("A")    // Alpha channel
        };

        m_embeddedWidget->setFixedSize(WIDGET_NODE_SIZE, WIDGET_NODE_SIZE);
        m_embeddedWidget->setAutoFillBackground(true);

        setColor(glm::vec4(1.f));
        m_embeddedWidget->setPalette(QPalette(QColor(Qt::white)));

        m_embeddedWidget->setFixedSize(IMAGE_NODE_SIZE, IMAGE_NODE_SIZE);
        m_embeddedWidget->installEventFilter(this);
    }

    bool ColorNode::eventFilter(QObject * object, QEvent * event)
    {
        if (object == m_embeddedWidget && event->type() == QEvent::MouseButtonPress)
        {
            QPalette p;
            QColor c;

            glm::vec4 currentColor = getColor();

            c.setRedF(currentColor[0]);
            c.setGreenF(currentColor[1]);
            c.setBlueF(currentColor[2]);
            c.setAlphaF(currentColor[3]);

            c = QColorDialog::getColor(c);

            setColor(glm::vec4(c.redF(), c.greenF(), c.blueF(), c.alphaF()));

            return true;
        }
        return false;
    }


    glm::vec4 ColorNode::getColor()
    {
        auto *v = dynamic_cast<Vector4 *>( outData(0).get());
        return (v == nullptr) ? glm::vec4(1.f) : v->value();
    }

    void ColorNode::setColor(const glm::vec4 &color)
    {

        auto *v = dynamic_cast<Vector4 *>(outData(0).get());

        if (v)
        {
            QColor c;

            // ...
            v->setValue(color);

            // Set the preview
            c.setRedF(color[0]);
            c.setGreenF(color[1]);
            c.setBlueF(color[2]);
            c.setAlphaF(color[3]);
            m_embeddedWidget->setPalette(c);
        }
    }
}
