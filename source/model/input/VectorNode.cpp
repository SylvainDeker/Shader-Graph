#include "VectorNode.h"

namespace ShaderGraph
{
    //====================================================================================================
    // Scalar Node
    //====================================================================================================

    ScalarNode::ScalarNode() :
            InputNode("Scalar", "Scalar"),
            m_value(0.f),
            m_embeddedWidget(new QWidget()),
            m_layout(new QBoxLayout(QBoxLayout::TopToBottom, m_embeddedWidget)),

            m_spinBoxX(new QDoubleSpinBox()),

            m_detail(new QWidget()),
            m_mainlayout(new QVBoxLayout()),
            m_spinBoxXdetail(new QDoubleSpinBox())
    {

        outputs() = std::vector<PIN>{
                std::make_shared<Float>("Result", this)
        };

        m_layout->addWidget(m_spinBoxX);

        m_spinBoxX->setSingleStep(SPINBOX_STEP);
        m_spinBoxX->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxX->setFixedWidth(WIDGET_NODE_SIZE);

        connect(m_spinBoxX, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &ScalarNode::onValue);

        m_detail->setLayout(m_mainlayout);
        m_mainlayout->addWidget(m_spinBoxXdetail);

        m_spinBoxXdetail->setSingleStep(SPINBOX_STEP);
        m_spinBoxXdetail->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxXdetail->setFixedWidth(WIDGET_NODE_SIZE);

        connect(m_spinBoxXdetail, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &ScalarNode::onValueDetail);

    }

    void ScalarNode::onValue()
    {
        set(m_spinBoxX->value());
    }

    void ScalarNode::onValueDetail()
    {
        set(m_spinBoxXdetail->value());
    }

    float ScalarNode::get()
    {
        return m_value;
    }

    void ScalarNode::set(const float& v)
    {
      m_value = v;
      m_spinBoxX->setValue(v);

      m_spinBoxXdetail->setValue(v);
    }

    void ScalarNode::showDetails(QVBoxLayout * layout)
    {
        Node::showDetails(layout);
        if (!isLayoutInit())
        {
          setLayout(layout);
          setIndexLayout(layout->count());
          layout->addWidget(m_detail);
        }

        layout->itemAt(getIndexLayout())->widget()->setVisible(true);

        set(m_value); // Allow update data
    }



    //====================================================================================================
    // Vector2 Node
    //====================================================================================================

    Vec2Node::Vec2Node() :
            InputNode("Vector2", "Vector2"),
            m_value(glm::vec2(0.f)),
            m_embeddedWidget(new QWidget()),
            m_layout(new QBoxLayout(QBoxLayout::TopToBottom, m_embeddedWidget)),

            m_spinBoxX(new QDoubleSpinBox()),
            m_spinBoxY(new QDoubleSpinBox()),
            m_detail(new QWidget()),
            m_mainlayout(new QVBoxLayout()),
            m_spinBoxXdetail(new QDoubleSpinBox()),
            m_spinBoxYdetail(new QDoubleSpinBox())
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


        connect(m_spinBoxX, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec2Node::onValue);
        connect(m_spinBoxY, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec2Node::onValue);

        m_detail->setLayout(m_mainlayout);
        m_mainlayout->addWidget(m_spinBoxXdetail);
        m_mainlayout->addWidget(m_spinBoxYdetail);

        m_spinBoxXdetail->setSingleStep(SPINBOX_STEP);
        m_spinBoxXdetail->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxXdetail->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxYdetail->setSingleStep(SPINBOX_STEP);
        m_spinBoxYdetail->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxYdetail->setFixedWidth(WIDGET_NODE_SIZE);


        connect(m_spinBoxXdetail, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec2Node::onValueDetail);
        connect(m_spinBoxYdetail, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec2Node::onValueDetail);
    }

    void Vec2Node::onValue()
    {
        set(glm::vec2(m_spinBoxX->value(),
                      m_spinBoxY->value())
                    );
    }
    void Vec2Node::onValueDetail()
    {
        set(glm::vec2(m_spinBoxXdetail->value(),
                      m_spinBoxYdetail->value())
                    );
    }

    glm::vec2 Vec2Node::get()
    {

        return m_value;
    }

    void Vec2Node::set(const glm::vec2& v)
    {
      m_value = v;
      m_spinBoxX->setValue(v[0]);
      m_spinBoxY->setValue(v[1]);

      m_spinBoxXdetail->setValue(v[0]);
      m_spinBoxYdetail->setValue(v[1]);
    }

    void Vec2Node::showDetails(QVBoxLayout * layout)
    {
        Node::showDetails(layout);
        if( ! isLayoutInit()){
          setLayout(layout);
          setIndexLayout(layout->count());
          layout->addWidget(m_detail);
        }

        layout->itemAt(getIndexLayout())->widget()->setVisible(true);

        set(m_value); // Allow update data
    }




    //====================================================================================================
    // Vector3 Node
    //====================================================================================================

    Vec3Node::Vec3Node() :
            InputNode("Vector3", "Vector3"),
            m_value(glm::vec3(0.f)),
            m_embeddedWidget(new QWidget()),
            m_layout(new QBoxLayout(QBoxLayout::TopToBottom, m_embeddedWidget)),

            m_spinBoxX(new QDoubleSpinBox()),
            m_spinBoxY(new QDoubleSpinBox()),
            m_spinBoxZ(new QDoubleSpinBox()),
            m_detail(new QWidget()),
            m_mainlayout(new QVBoxLayout()),
            m_spinBoxXdetail(new QDoubleSpinBox()),
            m_spinBoxYdetail(new QDoubleSpinBox()),
            m_spinBoxZdetail(new QDoubleSpinBox())
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

        connect(m_spinBoxX, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec3Node::onValue);
        connect(m_spinBoxY, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec3Node::onValue);
        connect(m_spinBoxZ, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec3Node::onValue);

        m_detail->setLayout(m_mainlayout);
        m_mainlayout->addWidget(m_spinBoxXdetail);
        m_mainlayout->addWidget(m_spinBoxYdetail);
        m_mainlayout->addWidget(m_spinBoxZdetail);

        m_spinBoxXdetail->setSingleStep(SPINBOX_STEP);
        m_spinBoxXdetail->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxXdetail->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxYdetail->setSingleStep(SPINBOX_STEP);
        m_spinBoxYdetail->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxYdetail->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxZdetail->setSingleStep(SPINBOX_STEP);
        m_spinBoxZdetail->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxZdetail->setFixedWidth(WIDGET_NODE_SIZE);

        connect(m_spinBoxXdetail, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec3Node::onValueDetail);
        connect(m_spinBoxYdetail, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec3Node::onValueDetail);
        connect(m_spinBoxZdetail, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec3Node::onValueDetail);

    }

    void Vec3Node::onValue()
    {
        set(glm::vec3(m_spinBoxX->value(),
                      m_spinBoxY->value(),
                      m_spinBoxZ->value())
                    );
    }
    void Vec3Node::onValueDetail()
    {
        set(glm::vec3(m_spinBoxXdetail->value(),
                      m_spinBoxYdetail->value(),
                      m_spinBoxZdetail->value())
                    );
    }

    glm::vec3 Vec3Node::get()
    {
        return m_value;
    }

    void Vec3Node::set(const glm::vec3& v)
    {
      m_value = v;
      m_spinBoxX->setValue(v[0]);
      m_spinBoxY->setValue(v[1]);
      m_spinBoxZ->setValue(v[2]);

      m_spinBoxXdetail->setValue(v[0]);
      m_spinBoxYdetail->setValue(v[1]);
      m_spinBoxZdetail->setValue(v[2]);
    }

    void Vec3Node::showDetails(QVBoxLayout * layout)
    {
        Node::showDetails(layout);
        if( ! isLayoutInit()){
          setLayout(layout);
          setIndexLayout(layout->count());
          layout->addWidget(m_detail);
        }

        layout->itemAt(getIndexLayout())->widget()->setVisible(true);

        set(m_value); // Allow update data
    }



    //====================================================================================================
    // Vector4 Node
    //====================================================================================================

    Vec4Node::Vec4Node() :
            InputNode("Vector4", "Vector4"),
            m_value(glm::vec4(0.f)),
            m_embeddedWidget(new QWidget()),
            m_layout(new QBoxLayout(QBoxLayout::TopToBottom, m_embeddedWidget)),

            m_spinBoxX(new QDoubleSpinBox()),
            m_spinBoxY(new QDoubleSpinBox()),
            m_spinBoxZ(new QDoubleSpinBox()),
            m_spinBoxW(new QDoubleSpinBox()),
            m_detail(new QWidget()),
            m_mainlayout(new QVBoxLayout()),
            m_spinBoxXdetail(new QDoubleSpinBox()),
            m_spinBoxYdetail(new QDoubleSpinBox()),
            m_spinBoxZdetail(new QDoubleSpinBox()),
            m_spinBoxWdetail(new QDoubleSpinBox())
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

        connect(m_spinBoxX, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec4Node::onValue);
        connect(m_spinBoxY, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec4Node::onValue);
        connect(m_spinBoxZ, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec4Node::onValue);
        connect(m_spinBoxW, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec4Node::onValue);

        m_detail->setLayout(m_mainlayout);
        m_mainlayout->addWidget(m_spinBoxXdetail);
        m_mainlayout->addWidget(m_spinBoxYdetail);
        m_mainlayout->addWidget(m_spinBoxZdetail);
        m_mainlayout->addWidget(m_spinBoxWdetail);

        m_spinBoxXdetail->setSingleStep(SPINBOX_STEP);
        m_spinBoxXdetail->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxXdetail->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxYdetail->setSingleStep(SPINBOX_STEP);
        m_spinBoxYdetail->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxYdetail->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxZdetail->setSingleStep(SPINBOX_STEP);
        m_spinBoxZdetail->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxZdetail->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxWdetail->setSingleStep(SPINBOX_STEP);
        m_spinBoxWdetail->setRange(-FLT_MAX, FLT_MAX);
        m_spinBoxWdetail->setFixedWidth(WIDGET_NODE_SIZE);

        connect(m_spinBoxXdetail, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec4Node::onValueDetail);
        connect(m_spinBoxYdetail, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec4Node::onValueDetail);
        connect(m_spinBoxZdetail, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec4Node::onValueDetail);
        connect(m_spinBoxWdetail, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec4Node::onValueDetail);
    }

    void Vec4Node::onValue()
    {
        set(glm::vec4(m_spinBoxX->value(),
                      m_spinBoxY->value(),
                      m_spinBoxZ->value(),
                      m_spinBoxW->value())
                    );
    }
    void Vec4Node::onValueDetail()
    {
        set(glm::vec4(m_spinBoxXdetail->value(),
                      m_spinBoxYdetail->value(),
                      m_spinBoxZdetail->value(),
                      m_spinBoxWdetail->value())
                    );
    }

    glm::vec4 Vec4Node::get()
    {
        return m_value;
    }

    void Vec4Node::set(const glm::vec4& v)
    {
      m_value = v;
      m_spinBoxX->setValue(v[0]);
      m_spinBoxY->setValue(v[1]);
      m_spinBoxZ->setValue(v[2]);
      m_spinBoxW->setValue(v[3]);

      m_spinBoxXdetail->setValue(v[0]);
      m_spinBoxYdetail->setValue(v[1]);
      m_spinBoxZdetail->setValue(v[2]);
      m_spinBoxWdetail->setValue(v[3]);
    }

    void Vec4Node::showDetails(QVBoxLayout   * layout){
        Node::showDetails(layout);
        if( ! isLayoutInit()){
          setLayout(layout);
          setIndexLayout(layout->count());
          layout->addWidget(m_detail);
        }

        layout->itemAt(getIndexLayout())->widget()->setVisible(true);

        set(m_value); // Allow update data
    }




}
