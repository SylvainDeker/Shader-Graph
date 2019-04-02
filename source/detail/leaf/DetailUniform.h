#ifndef SHADERGRAPH_DETAILUNIFORM_H
#define SHADERGRAPH_DETAILUNIFORM_H

#include <core/Core.h>

#include "../DetailNode.h"

#include "DetailBoolean.h"
#include "DetailText.h"

namespace ShaderGraph
{
    class IUniform
    {
    public:
        virtual ~IUniform() = default;

        /// @return : True if this node is a uniform.
        virtual bool isUniform() = 0;

        /// @return : The name of the uniform.
        /// @warning : Only valid if @isUniform equals true.
        virtual std::string getUniformName() = 0;

        /// @return : The default value of the uniform.
        /// @warning : Only valid if @isUniform equals true.
        virtual std::string getUniformDefaultValue() = 0;
    };

    class DetailUniform : public DetailNode
    {
    public:
        /// Default Constructor.
        DetailUniform() = default;

        /// Constructor :
        /// Construct a uniform Item.
        /// @node : the leaf parent.
        /// @tree : the root of this leaf.
        /// @parent : The node to detail.
        explicit DetailUniform(QCheckBox * isUniformCheckBox,
                               QLineEdit * uniformName,
                               QTreeWidgetItem * node,
                               QString name,
                               QtNodes::NodeDataModel * nodeDataModel = nullptr,
                               QColor textColor = QColor("white")) :
                DetailNode(node, name, nodeDataModel, textColor)
        {
            m_isUniform = DetailBool(isUniformCheckBox, QNode(), "Is Uniform ?", nodeDataModel);
            m_uniformName = DetailText(uniformName, QNode(), "Name", nodeDataModel);
        }

        /// Destructor.
        ~DetailUniform() override = default;

    private:
        DetailBool m_isUniform;
        DetailText m_uniformName;
    };
}

#endif //SHADERGRAPH_DETAILUNIFORM_H
