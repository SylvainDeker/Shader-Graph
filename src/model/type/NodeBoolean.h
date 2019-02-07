#ifndef SHADERGRAPH_NODEBOOLEAN_H
#define SHADERGRAPH_NODEBOOLEAN_H

#include <nodes/NodeData>
#include <nodes/NodeDataModel>

#include <memory>

namespace ShaderGraph
{

    class BooleanNodeData : public QtNodes::NodeData
    {
    public:

        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType {"Boolean", "Boolean"};
        }
    };

    class BooleanNode : public QtNodes::NodeDataModel
    {

    Q_OBJECT;

    public:
        BooleanNode() = default;

        virtual ~BooleanNode() = default;

        QString caption() const override
        {
            return QString("Boolean");
        }

        QString name() const override
        {
            return QString("Boolean");
        }

    public:

        unsigned int nPorts(QtNodes::PortType portType) const override
        {

            switch (portType)
            {
                case QtNodes::PortType::In :
                    return 0; // No input

                case QtNodes::PortType::Out :
                    return 1; // The value

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
                    return BooleanNodeData().type();

                case QtNodes::PortType::None:
                    break;
            }
            return QtNodes::NodeDataType();
        }

        std::shared_ptr<QtNodes::NodeData> outData(QtNodes::PortIndex port) override
        {
            return std::make_shared<BooleanNodeData>();
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

#endif //SHADERGRAPH_NODEBOOLEAN_H
