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

        /// Getter only : color.
        glm::vec4 getColor();

        /// Getter only : color.
        QColor getQColor();

        /// Setter only : color.
        void setColor(const glm::vec4& color);

        /// Setter only : color.
        void setColor(const QColor &color);


        /// Specified the embedded widget in the Node.
        /// @return : the widget.
        QWidget * embeddedWidget() override
        {
            return m_embeddedWidget;
        }

        /// Function that display properties in the layout (details)
        void showDetails(QVBoxLayout * layout) override;

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

        // details
        QWidget * m_detail;
        QVBoxLayout * m_mainlayout;
        QHBoxLayout * m_layoutcolor;
        QVBoxLayout * m_coordlayout;
        QDoubleSpinBox * m_boxr;
        QDoubleSpinBox * m_boxg;
        QDoubleSpinBox * m_boxb;
        QDoubleSpinBox * m_boxa;
        QWidget * m_display;
    };


}

#endif //SHADERGRAPH_COLORNODE_H
