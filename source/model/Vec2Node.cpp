//
// Created by Sylvain on 2019-03-08.
//


#include <QDoubleSpinBox>

#include "Vec2Node.h"


namespace ShaderGraph
{
    Vec2Node::Vec2Node() :
        InputNode("Vector2","Vector2"),
        m_spinbox_x(new QDoubleSpinBox()),
        m_spinbox_y(new QDoubleSpinBox())
    {

        outputs() = std::vector<PIN>{
            std::make_shared<Vector2>()
        };

        m_layout->addWidget(m_spinbox_x);
        m_layout->addWidget(m_spinbox_y);


        m_spinbox_x->setSingleStep(m_spinbox_step);
        m_spinbox_x->setRange(m_spinbox_min,m_spinbox_max);
        m_spinbox_x->setFixedWidth(m_size_widget_node);

        m_spinbox_y->setSingleStep(m_spinbox_step);
        m_spinbox_y->setRange(m_spinbox_min,m_spinbox_max);
        m_spinbox_y->setFixedWidth(m_size_widget_node);


        connect(
          m_spinbox_x,
          static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
          this,
          &Vec2Node::onValue
        );
        connect(
          m_spinbox_y,
          static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
          this,
          &Vec2Node::onValue
        );


    }

    void Vec2Node::onValue(){
        setVec2(glm::vec2(m_spinbox_x->value(),
                          m_spinbox_y->value()),
                          true
                        );
    }

    //
    glm::vec2 Vec2Node::getVec2() {

      std::shared_ptr<QtNodes::NodeData> sptr = outData(0);
      Vector2 *v2 = static_cast<Vector2*>(sptr.get());
      if(v2==nullptr) return glm::vec2(0.f);
      return v2->value();
    }

    void Vec2Node::setVec2(const glm::vec2& value, bool loop) {
    std::shared_ptr<QtNodes::NodeData> sptr = outData(0);
    Vector2 *v2 = static_cast<Vector2*>( sptr.get());

      v2->setValue(value);

      if(!loop){
        emit m_spinbox_x->valueChanged(static_cast<double>(value[0]));
        emit m_spinbox_y->valueChanged(static_cast<double>(value[1]));
      }

    }

}
