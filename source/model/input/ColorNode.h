#ifndef SHADERGRAPH_COLORNODE_H
#define SHADERGRAPH_COLORNODE_H

#include <memory>

#include <QWidget>
#include <QColor>
#include <QDoubleSpinBox>

#include <QCheckBox>
#include <QLineEdit>

#include <core/Core.h>

#include "../Node.h"

#define DEFAULT_COLOR QColor(Qt::white)
#define SPINBOX_VALUE_CHANGED_SLOT static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged)

namespace ShaderGraph
{
    class ColorNode : public Node, public IUniform
    {
        Q_OBJECT

    public:
        /// Constructor.
        ColorNode();

        /// Destructor.
        ~ColorNode() override = default;

        /// Setter only : color (glm format).
        void setColor(const glm::vec4& color);

        /// Setter only : color (Qt format).
        void setColor(const QColor &color);

        /// Specified the embedded widget in the Node.
        /// @return : the widget.
        inline QWidget * embeddedWidget() override { return m_embeddedWidget; }

        /// Show all node's properties in the node panel.
        void showDetails(QTreeWidget * tree) override;

        /// Hide all node's properties from the node panel.
        void hideDetails(QTreeWidget * tree) override;

        /// @return : True if this node is a uniform.
        inline bool isUniform() override { return m_isUniform->isChecked(); }

        /// @return : The name of the uniform.
        /// @warning : Only valid if @isUniform equals true.
        inline std::string getUniformName() override { return m_uniformName->text().toStdString(); }

        /// @return : The default value of the uniform.
        /// @warning : Only valid if @isUniform equals true.
        inline std::string getUniformDefaultValue() override
        {
            // function to_str defined in model/Node.h and used to avoid
            // float to string conversion with comas from french OS
            return  "vec4(" +
                    to_str(m_rSpinBox->value()) + ", " +
                    to_str(m_gSpinBox->value()) + ", " +
                    to_str(m_bSpinBox->value()) + ", " +
                    to_str(m_aSpinBox->value()) + ") " ;
        };

        GLSLData nodeToGLSL() override;

    public slots:
        void onColorValueChanged(double value);

        void onIsUniformValueChanged(int check);

    protected:
        /// The event filter : see Qt documentation.
        bool eventFilter(QObject *object, QEvent *event) override;

    private:
        /// The color.
        QColor m_color;

        /// The embedded widget.
        QWidget * m_embeddedWidget;

        QDoubleSpinBox * m_rSpinBox;
        QDoubleSpinBox * m_gSpinBox;
        QDoubleSpinBox * m_bSpinBox;
        QDoubleSpinBox * m_aSpinBox;

        QCheckBox * m_isUniform;

        QLineEdit * m_uniformName;

        bool m_isDetailBuilt = false;

        DetailNode m_colorDetails;

        /// Color Leaf
        DetailColor m_colorLeaf;

        /// Uniform Leaf
        DetailUniform m_uniformLeaf;

    };


}

#endif //SHADERGRAPH_COLORNODE_H
