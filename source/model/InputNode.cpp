//
// Created by Sykvain on 2019-03-07.
//

#include "InputNode.h"
using namespace ShaderGraph;

InputNode::InputNode(QString name, QString caption) : Node(name,caption)
{
    inputs() = std::vector<PIN>();

}
