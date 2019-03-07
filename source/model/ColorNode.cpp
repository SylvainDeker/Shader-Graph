//
// Created by Sylvain on 2019-03-07.
//
#include <QBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QColorDialog>
#include <QMessageBox>
#include <QString>

#include "ColorNode.h"

using namespace ShaderGraph;

ColorNode::ColorNode() :
    InputNode("Color","Color"),
    _mainwidget(new QWidget()),
    _layout(new QBoxLayout(QBoxLayout::  TopToBottom,_mainwidget)),
    _color_preview(new QFrame()),
    _selecter(new QPushButton("Select"))
{

    outputs() = std::vector<PIN>{
        std::make_shared<Vector4>()
    };

    _layout->addWidget(_selecter);
    _layout->addWidget(_color_preview);


    _color_preview->setFixedSize(75,75);
    _color_preview->setPalette(QPalette(QColor(Qt::green)));
    _selecter->setFixedWidth(75);
    _color_preview->setAutoFillBackground(true);

    connect(_selecter,&QPushButton::pressed,this,&ColorNode::onColor);


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
  _color_preview->setPalette(c);
}
