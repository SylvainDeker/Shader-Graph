#ifndef SHADERGRAPH_DATA_H
#define SHADERGRAPH_DATA_H

#include <memory>

#include <nodes/NodeData>
#include <nodes/NodeDataModel>

#define PIN std::shared_ptr<GenType>

namespace ShaderGraph
{
    using GenType = QtNodes::NodeData;

    class Boolean : public QtNodes::NodeData
    {
    public:

        /// Default constructor.
        Boolean() : m_value(false) {};

        /// Constructor.
        Boolean(bool value) : m_value(value) {};

        /// Getter only of the value.
        inline bool value() const
        {
            return m_value;
        }

        /// Setter only of the value.
        inline void setValue( const bool value)
        {
            m_value = value;
        }

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType {"bool", "bool"};
        }

    private:
        bool m_value;
    };

    class Float : public QtNodes::NodeData
    {
    public:

        /// Default constructor.
        inline Float() : m_value(0.0f) {};

        /// Constructor.
        inline Float(float value) : m_value(value) {};

        /// Getter only of the value.
        inline float value() const
        {
            return m_value;
        }

        /// Setter only of the value.
        inline void setValue( const float value)
        {
            m_value = value;
        }

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType {"float", "float"};
        }

    private:
        float m_value;
    };

    class Vector2 : public QtNodes::NodeData
    {
    public:

        /// Default constructor.
        inline Vector2() : m_value(glm::vec2(0.0f)) {};

        /// Constructor.
        inline Vector2(glm::vec2 value) : m_value(value) {};

        /// Getter only of the value.
        inline glm::vec2 value() const
        {
            return m_value;
        }
        /// Setter only of the value.
        inline void setValue( const glm::vec2 & v2)
        {
            m_value = v2;
        }

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType {"vec2", "vec2"};
        }

    private:
        glm::vec2 m_value;
    };

    class Vector3 : public QtNodes::NodeData
    {
    public:

        /// Default constructor.
        inline Vector3() : m_value(glm::vec3(0.0f)) {};

        /// Constructor.
        inline Vector3(glm::vec3 value) : m_value(value) {};

        /// Getter only of the value.
        inline glm::vec3 value() const
        {
            return m_value;
        }

        /// Setter only of the value.
        inline void setValue( const glm::vec3 & v3)
        {
            m_value = v3;
        }

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType {"vec3", "vec3"};
        }

    private:
        glm::vec3 m_value;
    };

    class Vector4 : public QtNodes::NodeData
    {
    public:

        /// Default constructor.
        inline Vector4() : m_value(glm::vec4(0.0f)) {};

        /// Constructor.
        inline Vector4(glm::vec4 value) : m_value(value) {};

        /// Getter only of the value.
        inline glm::vec4 value() const
        {
            return m_value;
        }

        /// Setter only of the value.
        inline void setValue( const glm::vec4 & v4)
        {
            m_value = v4;
        }

        /// @return : the id and the name of this data.
        QtNodes::NodeDataType type() const override
        {
            return QtNodes::NodeDataType {"vec4", "vec4"};
        }

    private:
        glm::vec4 m_value;
    };
}

#endif //SHADERGRAPH_DATA_H
