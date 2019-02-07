#ifndef SHADERGRAPH_NODEMANAGER_H
#define SHADERGRAPH_NODEMANAGER_H

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>

#include <memory>
#include <string>

namespace ShaderGraph
{
    class NodeManager
    {
    public:

        inline NodeManager()
        {
            m_dataModelRegistry = std::make_shared<QtNodes::DataModelRegistry>();
        }

        ~NodeManager() = default;

        /// Load the code style from a file
        bool loadNodeStyle(const QString filename);

        /// Set the style of the editor
        inline const void setNodeStyle(const QString& codeStyle) const
        {
            QtNodes::ConnectionStyle::setConnectionStyle(codeStyle);
        }

        /// Getter and Setter of m_dataModelRegistry
        inline std::shared_ptr<QtNodes::DataModelRegistry> registry()
        {
            return m_dataModelRegistry;
        }

        /// Getter and Setter of m_codeStyleFilename
        inline const QString& getCodeStyleFilename() const
        {
            return m_codeStyleFilename;
        }

    private:

        QString m_codeStyleFilename = "the code style doesn't come from a file";

        std::shared_ptr<QtNodes::DataModelRegistry> m_dataModelRegistry;

    };
}

#endif //SHADERGRAPH_NODEMANAGER_H
