//
// Created by Sylvain on 2019-03-07.
//

#include <QFrame>
#include <QPushButton>
#include <QColorDialog>
#include <QMessageBox>
#include <QString>

#include "ColorNode.h"

using namespace ShaderGraph;

ColorNode::ColorNode() :
    InputNode("Color","Color"),
    m_color_preview(new QFrame()),
    m_selecter(new QPushButton("Select"))
{

    outputs() = std::vector<PIN>{
        std::make_shared<Vector4>()
    };

    m_layout->addWidget(m_selecter);
    m_layout->addWidget(m_color_preview);


    m_color_preview->setFixedSize(75,75);
    m_color_preview->setPalette(QPalette(QColor(Qt::green)));
    m_selecter->setFixedWidth(75);
    m_color_preview->setAutoFillBackground(true);

    connect(m_selecter,&QPushButton::pressed,this,&ColorNode::onColor);


}

void ColorNode::onColor(){
    QPalette p;
    glm::vec4 ic = getColor();
    QColor c;
    c.setRedF(ic[0]);
    c.setGreenF(ic[1]);
    c.setBlueF(ic[2]);
    c.setAlphaF(ic[3]);
    c = QColorDialog::getColor(c);

    setColor(glm::vec4(c.redF(),c.greenF(),c.blueF(),c.alphaF()));
}


glm::vec4 ColorNode::getColor() {
  std::shared_ptr<QtNodes::NodeData> sptr = outData(0);
  Vector4 *v4 = static_cast<Vector4*>( sptr.get());
  if(v4==nullptr) return glm::vec4(0.f,1.f,0.f,1.f);
  return v4->value();
}

void ColorNode::setColor(const glm::vec4& color ) {
  std::shared_ptr<QtNodes::NodeData> sptr = outData(0);
  Vector4 *v4 = static_cast<Vector4*>( sptr.get());
  v4->setValue(color);

  // set the preview
  QColor c;
  c.setRedF(color[0]);
  c.setGreenF(color[1]);
  c.setBlueF(color[2]);
  c.setAlphaF(color[3]);
  m_color_preview->setPalette(c);
}
