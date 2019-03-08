//
// Created by Sylvain on 2019-03-08.
//


#include <QDoubleSpinBox>

#include "Vec3Node.h"


using namespace ShaderGraph;

Vec3Node::Vec3Node() :
    InputNode("Vector3","Vector3"),
    m_spinbox_x(new QDoubleSpinBox()),
    m_spinbox_y(new QDoubleSpinBox()),
    m_spinbox_z(new QDoubleSpinBox())
{

    outputs() = std::vector<PIN>{
        std::make_shared<Vector3>()
    };

    m_layout->addWidget(m_spinbox_x);
    m_layout->addWidget(m_spinbox_y);
    m_layout->addWidget(m_spinbox_z);


    m_spinbox_x->setSingleStep(m_spinbox_step);
    m_spinbox_x->setRange(m_spinbox_min,m_spinbox_max);
    m_spinbox_x->setFixedWidth(m_size_widget_node);

    m_spinbox_y->setSingleStep(m_spinbox_step);
    m_spinbox_y->setRange(m_spinbox_min,m_spinbox_max);
    m_spinbox_y->setFixedWidth(m_size_widget_node);

    m_spinbox_z->setSingleStep(m_spinbox_step);
    m_spinbox_z->setRange(m_spinbox_min,m_spinbox_max);
    m_spinbox_z->setFixedWidth(m_size_widget_node);

    connect(
      m_spinbox_x,
      static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
      this,
      &Vec3Node::onValue
    );
    connect(
      m_spinbox_y,
      static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
      this,
      &Vec3Node::onValue
    );
    connect(
      m_spinbox_y,
      static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
      this,
      &Vec3Node::onValue
    );


}

void Vec3Node::onValue(){
    setVec3(glm::vec3(m_spinbox_x->value(),
                      m_spinbox_y->value(),
                      m_spinbox_z->value()),
                      true
                    );
}

//
glm::vec3 Vec3Node::getVec3() {
  std::shared_ptr<QtNodes::NodeData> sptr = outData(0);
  Vector3 *v3 = static_cast<Vector3*>( sptr.get());
  if(v3==nullptr) return glm::vec3(0.f,0.f,0.f);
  return v3->value();
}

void Vec3Node::setVec3(const glm::vec3& value,bool loop ) {
  std::shared_ptr<QtNodes::NodeData> sptr = outData(0);
  Vector3 *v3 = static_cast<Vector3*>( sptr.get());
  v3->setValue(value);
  if(!loop){
    emit m_spinbox_x->valueChanged(static_cast<double>(value[0]));
    emit m_spinbox_y->valueChanged(static_cast<double>(value[1]));
    emit m_spinbox_z->valueChanged(static_cast<double>(value[2]));

  }

}
