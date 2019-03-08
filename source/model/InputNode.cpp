//
// Created by Sykvain on 2019-03-07.
//
#include <QBoxLayout>

#include "InputNode.h"

using namespace ShaderGraph;

InputNode::InputNode(QString name, QString caption) :
  Node(name,caption),
  m_mainwidget(new QWidget()),
  m_layout(new QBoxLayout(QBoxLayout:: TopToBottom,m_mainwidget))
{
    inputs() = std::vector<PIN>();

}
