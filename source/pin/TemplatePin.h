#ifndef SHADERGRAPH_TEMPLATEPIN_H
#define SHADERGRAPH_TEMPLATEPIN_H

#include <core/Core.h>

#include "Pin.h"

#include "BooleanPin.h"
#include "FloatPin.h"
#include "VectorPin.h"

namespace ShaderGraph
{
    class Template : public Pin
    {
    public:
        /// Constructor :
        /// Use this constructor to initialize a template pin with a known value.
        /// @type : The type of this pin.
        /// @templateID : The ID of this template, all template with an equals ID
        /// must have the same type.
        explicit Template(EPinType type,
                          unsigned int templateID = 0,
                          QString name = "?",
                          QtNodes::NodeDataModel * owner = nullptr) :
                Pin(std::move(name), owner, EPinType::TEMPLATE),
                m_templateID(templateID),
                m_connectableTypes({type})
        {
            (void) templateID;
            setPinType(type);
        };

        /// Constructor - LValue :
        /// Use this constructor to initialize a template pin that can be connected.
        /// @connectableTypes : A list of all the possible type which can be connected
        /// to this pin.
        /// @templateID : The ID of this template, all template with an equals ID
        /// must have the same type.
        explicit Template(std::vector<EPinType>& connectableTypes,
                          unsigned int templateID = 0,
                          QString name = "?",
                          QtNodes::NodeDataModel * owner = nullptr) :
                Pin(std::move(name), owner, EPinType::TEMPLATE),
                m_templateID(templateID),
                m_connectableTypes(connectableTypes)
        {
            (void) templateID;
            setPinType(EPinType::TEMPLATE);
        };

        /// Constructor - RValue :
        /// Use this constructor to initialize a template pin that can be connected.
        /// @connectableTypes : A list of all the possible type which can be connected
        /// to this pin.
        /// @templateID : The ID of this template, all template with an equals ID
        /// must have the same type.
        explicit Template(std::vector<EPinType>&& connectableTypes,
                          unsigned int templateID = 0,
                          QString name = "?",
                          QtNodes::NodeDataModel * owner = nullptr) :
                Pin(std::move(name), owner, EPinType::TEMPLATE),
                m_templateID(templateID),
                m_connectableTypes(connectableTypes)
        {
            setPinType(EPinType::TEMPLATE);
        };

        ~Template() override { delete m_pin; }

        /// @return : If @type is contain in m_connectablesTypes,
        /// i.e if @type is a valid candidate to be plug-in.
        inline bool isConnectable(EPinType type)
        {
            auto types = m_connectableTypes; // Alias - for esthetic only :P
            return (std::find(types.begin(), types.end(), type) != types.end());
        }

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType{"Template", name()};
        }

        /// Connect this pin.
        void connect(PIN inPin) override;

        /// Getter : The connected pin.
        /// @warning : returns nullptr if this pin isn't connected.
        std::shared_ptr<QtNodes::NodeData> getConnectedPin() override;

        /// Setter : The node which contains this pin.
        void setNode(QtNodes::NodeDataModel * owner) override;

        /// @return : Get the GLSL type (in string) which represents this pin.
        std::string typeToGLSL() override;

        // @return : Get the GLSL default value (in string),
        // in case of this pin is disconnected during code generation.
        std::string defaultValueToGLSL() override;

        /// Getter : The "true" pin.
        inline QtNodes::NodeData * getPin() { return m_pin; }

        /// Setter : The "true" pin.
        void setPinType(EPinType type);

        inline unsigned int getTemplateID() const { return m_templateID; }

        /// Force all the template pins in the node to be with the same type has @type.
        void forceUpdateNode(EPinType type);

        void forceUpdatePin(PIN pin, EPinType type);

        /// Event triggered when a invalid connection has occurred.
        /// TODO : break the connection !
        void onConnectionInvalid(EPinType type);

    private:
        /// The ID of this template, all template with an equals ID must have the same type
        unsigned int m_templateID;

        /// A list of all the possible type which can be connected to this pin.
        std::vector<EPinType> m_connectableTypes;

        /// The "true" pin.
        QtNodes::NodeData * m_pin = nullptr;
    };
}

#endif //SHADERGRAPH_TEMPLATEPIN_H
