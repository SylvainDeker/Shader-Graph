#ifndef SHADERGRAPH_COLORNODE_H
#define SHADERGRAPH_COLORNODE_H

#include "model/InputNode.h"

#include <memory>

#include <QWidget>
#include <QMouseEvent>
#include <QColor>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <core/Core.h>

#define DEFAULT_COLOR QColor(Qt::white)
#define SPINBOX_VALUE_CHANGED_SLOT static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged)

namespace ShaderGraph
{
    class ColorNode : public InputNode
    {
        Q_OBJECT

    public:
        /// Constructor.
        ColorNode();

        /// Destructor.
        ~ColorNode() override = default;

        /// Getter only : color (glm format).
        /// @warning : Cast the Qt format (QColor) to the glm format (vec4).
        inline glm::vec4 asVec4() const
        {
            return glm::vec4(
                    static_cast<float>(m_color.redF()),
                    static_cast<float>(m_color.greenF()),
                    static_cast<float>(m_color.blueF()),
                    static_cast<float>(m_color.alphaF())
            );
        }

        /// Getter only : color (Qt format).
        inline QColor asQColor() const { return m_color; }

        /// Setter only : color (glm format).
        void setColor(const glm::vec4& color);

        /// Setter only : color (Qt format).
        void setColor(const QColor &color);

        /// Specified the embedded widget in the Node.
        /// @return : the widget.
        QWidget * embeddedWidget() override
        {
            return m_embeddedWidget;
        }

        /// Function that display properties in the layout (details)
        void showDetails(QVBoxLayout * layout) override;

        void showDetails(QTreeWidget * tree) override;

        void hideDetails(QTreeWidget * tree) override;

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "declColor({0}, {1}, {2}, ...",
                      autoName(outputs()[0]),
                      autoName(outputs()[1]),
                      autoName(outputs()[2]));
            return buffer;
        }

    public slots:
        void onValueChanged(double value);

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

        /* =============== Start QTreeWidget items definition ===============*/

        QTreeWidgetItem * m_rgbaSection = nullptr;

            QTreeWidgetItem * m_rSection = nullptr;
                QTreeWidgetItem * m_rItem = nullptr;

            QTreeWidgetItem * m_gSection = nullptr;
                QTreeWidgetItem * m_gItem = nullptr;

            QTreeWidgetItem * m_bSection = nullptr;
                QTreeWidgetItem * m_bItem = nullptr;

            QTreeWidgetItem * m_aSection = nullptr;
                QTreeWidgetItem * m_aItem = nullptr;

        /* =============== End QTreeWidget items definition ===============*/
    };


}

#endif //SHADERGRAPH_COLORNODE_H
