#ifndef SHADERGRAPH_COLORNODE_H
#define SHADERGRAPH_COLORNODE_H

#include "model/InputNode.h"

#include <memory>

#include <QFrame>
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
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

    public slots:
        /// Lets the user define @m_color, with a QColorDialog.
        void onColor();

    private:
        QWidget * m_embeddedWidget;
        QBoxLayout * m_layout;

        QFrame * m_colorPreview;
        QPushButton * m_selector;
    };


}

#endif //SHADERGRAPH_COLORNODE_H
