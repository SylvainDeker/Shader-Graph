#include "ColorNode.h"

#include <QString>
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFrame>
#include <QColorDialog>



namespace ShaderGraph
{
    ColorNode::ColorNode() :
            InputNode("Color", "Color"),
            m_color(QColor(0,0,0,0)),
            m_embeddedWidget(new QWidget()),
            m_detail(new QWidget()),
            m_mainlayout(new QVBoxLayout()),
            m_layoutcolor(new QHBoxLayout()),
            m_coordlayout(new QVBoxLayout()),
            m_boxr(new QDoubleSpinBox() ),
            m_boxg(new QDoubleSpinBox() ),
            m_boxb(new QDoubleSpinBox() ),
            m_boxa(new QDoubleSpinBox() ),
            m_display(new QWidget())
    {
        outputs() = std::vector<PIN> {
                std::make_shared<Vector4>("RGBA", this),  // RGBA
                std::make_shared<Float>("R", this),       // Red channel
                std::make_shared<Float>("G", this),       // Green channel
                std::make_shared<Float>("B", this),       // Blue channel
                std::make_shared<Float>("A", this)        // Alpha channel
        };

        m_embeddedWidget->setFixedSize(WIDGET_NODE_SIZE, WIDGET_NODE_SIZE);
        m_embeddedWidget->setAutoFillBackground(true);

        setColor(glm::vec4(1.f));
        m_embeddedWidget->setPalette(QPalette(QColor(Qt::white)));

        m_embeddedWidget->setFixedSize(IMAGE_NODE_SIZE, IMAGE_NODE_SIZE);
        m_embeddedWidget->installEventFilter(this);

        m_detail->setLayout(m_mainlayout);
        m_mainlayout->addLayout(m_layoutcolor);
        m_layoutcolor->addWidget(m_display);
        m_layoutcolor->addLayout(m_coordlayout);
        m_coordlayout->addWidget(m_boxr);
        m_coordlayout->addWidget(m_boxg);
        m_coordlayout->addWidget(m_boxb);
        m_coordlayout->addWidget(m_boxa);

        // m_display->setFixedSize(100,100);
        m_display->setMinimumWidth(75);
        QColor color = Qt::white;
        QString s("background: #"
                         + QString(color.red() < 16? "0" : "") + QString::number(color.red(), 16)
                         + QString(color.green() < 16? "0" : "") + QString::number(color.green(), 16)
                         + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(), 16) + ";");

         m_display->setStyleSheet(s);
         m_display->update();
         m_boxr->setRange(0,1);
         m_boxg->setRange(0,1);
         m_boxb->setRange(0,1);
         m_boxa->setRange(0,1);
         m_boxr->setSingleStep(0.1);
         m_boxg->setSingleStep(0.1);
         m_boxb->setSingleStep(0.1);
         m_boxa->setSingleStep(0.1);

         connect(m_boxr, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                 this,&ColorNode::onValueChanged);

         connect(m_boxg, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                 this,&ColorNode::onValueChanged);

         connect(m_boxb, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                 this,&ColorNode::onValueChanged);

         connect(m_boxa, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                 this,&ColorNode::onValueChanged);

    }

    bool ColorNode::eventFilter(QObject * object, QEvent * event)
    {
        if (object == m_embeddedWidget && event->type() == QEvent::MouseButtonPress)
        {
            QColor c;
            c = QColorDialog::getColor(m_color);
            setColor(c);

            return true;
        }
        return false;
    }
    void  ColorNode::onValueChanged(double value){
      (void) value ;
      glm::vec4 c;
      c[0] = static_cast<float>(m_boxr->value());
      c[1] = static_cast<float>(m_boxg->value());
      c[2] = static_cast<float>(m_boxb->value());
      c[3] = static_cast<float>(m_boxa->value());
      setColor(c);
    }


    glm::vec4 ColorNode::getColor()
    {
        glm::vec4 c;
        c[0] = m_color.redF();
        c[0] = m_color.greenF();
        c[0] = m_color.blueF();
        c[0] = m_color.alphaF();
        return c;
    }

    QColor ColorNode::getQColor()
    {
        return m_color;
    }

    void ColorNode::setColor(const glm::vec4 &color)
    {
      QColor c;
      c.setRedF(color[0]);
      c.setGreenF(color[1]);
      c.setBlueF(color[2]);
      c.setAlphaF(color[3]);
      setColor(c);
    }

    void ColorNode::setColor(const QColor &color)
    {
        m_color = color;
        m_embeddedWidget->setPalette(color);
        m_boxr->setValue(color.redF());
        m_boxg->setValue(color.greenF());
        m_boxb->setValue(color.blueF());
        m_boxa->setValue(color.alphaF());
        QString s("background: #"
                         + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                         + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                         + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";");
         m_display->setStyleSheet(s);
         m_display->update();
    }

    void ColorNode::showDetails(QVBoxLayout * layout)
    {
        Node::showDetails(layout);

        if (!isLayoutInit())
        {
          setLayout(layout);
          setIndexLayout(layout->count());
          layout->addWidget(m_detail);
        }

        layout->itemAt(getIndexLayout())->widget()->setVisible(true);

        setColor(m_color); // Allow update data
    }
}
