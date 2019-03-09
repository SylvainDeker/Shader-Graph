//
// Created by Sylvain on 2019-03-08.
//


#include <QDoubleSpinBox>

#include "ScalarNode.h"


namespace ShaderGraph
{
ScalarNode::ScalarNode() :
    InputNode("Scalar","Scalar"),
    m_spinbox_x(new QDoubleSpinBox())
{

    outputs() = std::vector<PIN>{
        std::make_shared<Float>()
    };

    m_layout->addWidget(m_spinbox_x);

    m_spinbox_x->setSingleStep(m_spinbox_step);
    m_spinbox_x->setRange(m_spinbox_min,m_spinbox_max);
    m_spinbox_x->setFixedWidth(m_size_widget_node);

    connect(
        m_spinbox_x,
        static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        this,
        &ScalarNode::onValue
    );
}

void ScalarNode::onValue(){
    setScalar(m_spinbox_x->value(),  true );
}


float ScalarNode::getScalar() {

    std::shared_ptr<QtNodes::NodeData> sptr = outData(0);
    Float *v = static_cast<Float*>(sptr.get());
    if(v==nullptr) return 0.f;
    return v->value();
}

void ScalarNode::setScalar(const float value, bool loop) {
    std::shared_ptr<QtNodes::NodeData> sptr = outData(0);
    Float *v2 = static_cast<Float*>( sptr.get());

    v2->setValue(value);

    if(!loop){
      emit m_spinbox_x->valueChanged(static_cast<double>(value));
    }

}
}
