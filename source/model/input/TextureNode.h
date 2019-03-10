#ifndef SHADERGRAPH_TEXTURENODE_H
#define SHADERGRAPH_TEXTURENODE_H

#include "model/Node.h"

#include <memory>

#include <QLabel>
#include <QPixmap>

namespace ShaderGraph
{
    class TextureNode : public Node
    {
    Q_OBJECT

    public:
        /// Constructor.
        TextureNode();

        /// Destructor.
        ~TextureNode() override = default;

        /// Specified the embedded widget in the Node.
        /// @return : the widget.
        QWidget * embeddedWidget() override { return m_label; }

        /// Make this node resizable.
        bool resizable() const override { return true; }

    protected:
        /// The event filter: see Qt documentation.
        bool eventFilter(QObject *object, QEvent *event) override;

    private:
        QLabel * m_label;
        QPixmap m_pixmap;
    };


}


#endif //SHADERGRAPH_TEXTURENODE_H
