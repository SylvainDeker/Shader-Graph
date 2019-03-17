#include "VectorNode.h"

namespace ShaderGraph
{
    //====================================================================================================
    // Scalar Node
    //====================================================================================================

    ScalarNode::ScalarNode() :
            InputNode("Scalar", "Scalar"),

            m_embeddedWidget(new QWidget()),
            m_layout(new QBoxLayout(QBoxLayout::TopToBottom, m_embeddedWidget)),

            m_spinBoxX(new QDoubleSpinBox())
    {

        outputs() = std::vector<PIN>{
                std::make_shared<Float>()
        };

        m_layout->addWidget(m_spinBoxX);

        m_spinBoxX->setSingleStep(SPINBOX_STEP);
        m_spinBoxX->setRange(FLT_MIN, FLT_MAX);
        m_spinBoxX->setFixedWidth(WIDGET_NODE_SIZE);

        connect(m_spinBoxX, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &ScalarNode::onValue);
    }

    void ScalarNode::onValue()
    {
        set(m_spinBoxX->value(), true);
    }

    float ScalarNode::get()
    {
        Float * v = dynamic_cast<Float*>(outData(0).get());
        return (v == nullptr) ? 0.f : v->value();
    }

    void ScalarNode::set(float value, bool loop)
    {
        Float * v = dynamic_cast<Float*>(outData(0).get());
        v->setValue(value);

        if(!loop)
        {
            emit m_spinBoxX->valueChanged(static_cast<double>(value));
        }
    }

    void ScalarNode::showDetails(QVBoxLayout   * layout){
      Node::showDetails(layout);
    }

    //====================================================================================================
    // Vector2 Node
    //====================================================================================================

    Vec2Node::Vec2Node() :
            InputNode("Vector2", "Vector2"),

            m_embeddedWidget(new QWidget()),
            m_layout(new QBoxLayout(QBoxLayout::TopToBottom, m_embeddedWidget)),

            m_spinBoxX(new QDoubleSpinBox()),
            m_spinBoxY(new QDoubleSpinBox())
    {

        outputs() = std::vector<PIN>{
                std::make_shared<Vector2>()
        };

        m_layout->addWidget(m_spinBoxX);
        m_layout->addWidget(m_spinBoxY);

        m_spinBoxX->setSingleStep(SPINBOX_STEP);
        m_spinBoxX->setRange(FLT_MIN, FLT_MAX);
        m_spinBoxX->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxY->setSingleStep(SPINBOX_STEP);
        m_spinBoxY->setRange(FLT_MIN, FLT_MAX);
        m_spinBoxY->setFixedWidth(WIDGET_NODE_SIZE);

        connect(m_spinBoxX, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec2Node::onValue);
        connect(m_spinBoxY, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec2Node::onValue);
    }

    void Vec2Node::onValue()
    {
        set(glm::vec2(m_spinBoxX->value(),
                      m_spinBoxY->value()),
            true);
    }

    glm::vec2 Vec2Node::get()
    {
        Vector2 * v = dynamic_cast<Vector2*>(outData(0).get());
        return (v == nullptr) ? glm::vec2(0.f) : v->value();
    }

    void Vec2Node::set(const glm::vec2& value, bool loop)
    {
        Vector2 * v = dynamic_cast<Vector2*>(outData(0).get());
        v->setValue(value);

        if(!loop)
        {
            emit m_spinBoxX->valueChanged(static_cast<double>(value.x));
            emit m_spinBoxY->valueChanged(static_cast<double>(value.y));
        }
    }
    void Vec2Node::showDetails(QVBoxLayout   * layout){
        Node::showDetails(layout);
    }

    //====================================================================================================
    // Vector3 Node
    //====================================================================================================

    Vec3Node::Vec3Node() :
        InputNode("Vector3", "Vector3"),

        m_embeddedWidget(new QWidget()),
        m_layout(new QBoxLayout(QBoxLayout::TopToBottom, m_embeddedWidget)),

        m_spinBoxX(new QDoubleSpinBox()),
        m_spinBoxY(new QDoubleSpinBox()),
        m_spinBoxZ(new QDoubleSpinBox())
    {

        outputs() = std::vector<PIN>{
            std::make_shared<Vector3>()
        };

        m_layout->addWidget(m_spinBoxX);
        m_layout->addWidget(m_spinBoxY);
        m_layout->addWidget(m_spinBoxZ);

        m_spinBoxX->setSingleStep(SPINBOX_STEP);
        m_spinBoxX->setRange(FLT_MIN, FLT_MAX);
        m_spinBoxX->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxY->setSingleStep(SPINBOX_STEP);
        m_spinBoxY->setRange(FLT_MIN, FLT_MAX);
        m_spinBoxY->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxZ->setSingleStep(SPINBOX_STEP);
        m_spinBoxZ->setRange(FLT_MIN, FLT_MAX);
        m_spinBoxZ->setFixedWidth(WIDGET_NODE_SIZE);

        connect(m_spinBoxX, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec3Node::onValue);
        connect(m_spinBoxY, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec3Node::onValue);
        connect(m_spinBoxZ, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,       &Vec3Node::onValue);
    }

    void Vec3Node::onValue()
    {
        set(glm::vec3(m_spinBoxX->value(),
                      m_spinBoxY->value(),
                      m_spinBoxZ->value()),
            true);
    }

    glm::vec3 Vec3Node::get()
    {
      Vector3 * v = dynamic_cast<Vector3*>(outData(0).get());
      return (v == nullptr) ? glm::vec3(0.f) : v->value();
    }

    void Vec3Node::set(const glm::vec3& value,bool loop )
    {
      Vector3 * v = dynamic_cast<Vector3*>(outData(0).get());
      v->setValue(value);

      if(!loop)
      {
        emit m_spinBoxX->valueChanged(static_cast<double>(value.x));
        emit m_spinBoxY->valueChanged(static_cast<double>(value.y));
        emit m_spinBoxZ->valueChanged(static_cast<double>(value.z));
      }
    }

    void Vec3Node::showDetails(QVBoxLayout   * layout){
        Node::showDetails(layout);
    }

    //====================================================================================================
    // Vector4 Node
    //====================================================================================================

    Vec4Node::Vec4Node() :
            InputNode("Vector4", "Vector4"),

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
                std::make_shared<Vector4>()
        };

        m_layout->addWidget(m_spinBoxX);
        m_layout->addWidget(m_spinBoxY);
        m_layout->addWidget(m_spinBoxZ);
        m_layout->addWidget(m_spinBoxW);

        m_spinBoxX->setSingleStep(SPINBOX_STEP);
        m_spinBoxX->setRange(FLT_MIN, FLT_MAX);
        m_spinBoxX->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxY->setSingleStep(SPINBOX_STEP);
        m_spinBoxY->setRange(FLT_MIN, FLT_MAX);
        m_spinBoxY->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxZ->setSingleStep(SPINBOX_STEP);
        m_spinBoxZ->setRange(FLT_MIN, FLT_MAX);
        m_spinBoxZ->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxW->setSingleStep(SPINBOX_STEP);
        m_spinBoxW->setRange(FLT_MIN, FLT_MAX);
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
        m_spinBoxXdetail->setRange(FLT_MIN, FLT_MAX);
        m_spinBoxXdetail->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxYdetail->setSingleStep(SPINBOX_STEP);
        m_spinBoxYdetail->setRange(FLT_MIN, FLT_MAX);
        m_spinBoxYdetail->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxZdetail->setSingleStep(SPINBOX_STEP);
        m_spinBoxZdetail->setRange(FLT_MIN, FLT_MAX);
        m_spinBoxZdetail->setFixedWidth(WIDGET_NODE_SIZE);

        m_spinBoxWdetail->setSingleStep(SPINBOX_STEP);
        m_spinBoxWdetail->setRange(FLT_MIN, FLT_MAX);
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
        Vector4 * v = dynamic_cast<Vector4*>(outData(0).get());
        return (v == nullptr) ? glm::vec4(0.f) : v->value();
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
