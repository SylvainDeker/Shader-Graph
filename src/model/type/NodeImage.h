#ifndef SHADERGRAPH_NODEIMAGE_H
#define SHADERGRAPH_NODEIMAGE_H

#include <nodes/NodeData>
#include <nodes/NodeDataModel>

#include <memory>

#include "NodeFloat.h"

namespace ShaderGraph
{
    class ImageNode : public QtNodes::NodeDataModel
    {

        Q_OBJECT;

    public:
        ImageNode() = default;

        virtual ~ImageNode() = default;

        QString caption() const override
        {
            return QString("Image");
        }

        QString name() const override
        {
            return QString("Image");
        }

    public:

        unsigned int nPorts(QtNodes::PortType portType) const override
        {

            switch (portType)
            {
                case QtNodes::PortType::In :
                    return 0; // No input

                case QtNodes::PortType::Out :
                    return 4; // The values

                case QtNodes::PortType::None :
                    return 1;
            }
        }

        QtNodes::NodeDataType dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const override
        {
            switch (portType)
            {
                case QtNodes::PortType::In :
                    break;

                case QtNodes::PortType::Out :
                    return FloatNodeData().type();


                case QtNodes::PortType::None:
                    break;
            }
            return QtNodes::NodeDataType();
        }

        std::shared_ptr<QtNodes::NodeData> outData(QtNodes::PortIndex port) override
        {
            return std::make_shared<FloatNodeData>();
        }

        void setInData(std::shared_ptr<QtNodes::NodeData>, int) override
        {
            // No input
        }

        QWidget * embeddedWidget() override
        {
            return nullptr;
        }
    };

}

#endif //SHADERGRAPH_NODEIMAGE_H
