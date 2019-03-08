//
// Created by Sylvain on 2019-03-08.
//


#include <QDoubleSpinBox>

#include "Vec4Node.h"


namespace ShaderGraph
{
    Vec4Node::Vec4Node() :
        InputNode("Vector4","Vector4"),

        m_spinbox_x(new QDoubleSpinBox()),
        m_spinbox_y(new QDoubleSpinBox()),
        m_spinbox_z(new QDoubleSpinBox()),
        m_spinbox_w(new QDoubleSpinBox())
    {

        outputs() = std::vector<PIN>{
            std::make_shared<Vector4>()
        };

        m_layout->addWidget(m_spinbox_x);
        m_layout->addWidget(m_spinbox_y);
        m_layout->addWidget(m_spinbox_z);
        m_layout->addWidget(m_spinbox_w);


        m_spinbox_x->setSingleStep(m_spinbox_step);
        m_spinbox_x->setRange(m_spinbox_min,m_spinbox_max);
        m_spinbox_x->setFixedWidth(m_size_widget_node);

        m_spinbox_y->setSingleStep(m_spinbox_step);
        m_spinbox_y->setRange(m_spinbox_min,m_spinbox_max);
        m_spinbox_y->setFixedWidth(m_size_widget_node);

        m_spinbox_z->setSingleStep(m_spinbox_step);
        m_spinbox_z->setRange(m_spinbox_min,m_spinbox_max);
        m_spinbox_z->setFixedWidth(m_size_widget_node);

        m_spinbox_w->setSingleStep(m_spinbox_step);
        m_spinbox_w->setRange(m_spinbox_min,m_spinbox_max);
        m_spinbox_w->setFixedWidth(m_size_widget_node);

        connect(
          m_spinbox_x,
          static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
          this,
          &Vec4Node::onValue
        );
        connect(
          m_spinbox_y,
          static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
          this,
          &Vec4Node::onValue
        );
        connect(
          m_spinbox_y,
          static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
          this,
          &Vec4Node::onValue
        );
        connect(
          m_spinbox_w,
          static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
          this,
          &Vec4Node::onValue
        );


    }

    void Vec4Node::onValue(){
        setVec4(glm::vec4(m_spinbox_x->value(),
                          m_spinbox_y->value(),
                          m_spinbox_z->value(),
                          m_spinbox_w->value()),
                          true
                        );
    }

    //
    glm::vec4 Vec4Node::getVec4() {

      std::shared_ptr<QtNodes::NodeData> sptr = outData(0);
      Vector4 *v4 = static_cast<Vector4*>(sptr.get());
      if(v4==nullptr) return glm::vec4(0.f);
      return v4->value();
    }

    void Vec4Node::setVec4(const glm::vec4& value, bool loop) {
    std::shared_ptr<QtNodes::NodeData> sptr = outData(0);
    Vector4 *v4 = static_cast<Vector4*>( sptr.get());

      v4->setValue(value);

      if(!loop){
        emit m_spinbox_x->valueChanged(static_cast<double>(value[0]));
        emit m_spinbox_y->valueChanged(static_cast<double>(value[1]));
        emit m_spinbox_z->valueChanged(static_cast<double>(value[2]));
        emit m_spinbox_w->valueChanged(static_cast<double>(value[3]));
      }

    }

}
