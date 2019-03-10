#ifndef SHADERGRAPH_COLORNODE_H
#define SHADERGRAPH_COLORNODE_H

#include "model/InputNode.h"

#include <memory>

#include <QWidget>
#include <QMouseEvent>
#include <QColorDialog>

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

        /// Setter only : color.
        void setColor(const glm::vec4& color);

        /// Specified the embedded widget in the Node.
        /// @return : the widget.
        QWidget * embeddedWidget() override
        {
            return m_embeddedWidget;
        }

    protected:
        /// The event filter : see Qt documentation.
        bool eventFilter(QObject *object, QEvent *event) override;

    private:
        QWidget * m_embeddedWidget;
    };


}

#endif //SHADERGRAPH_COLORNODE_H
