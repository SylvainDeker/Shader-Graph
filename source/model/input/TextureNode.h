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

        /// Show all node's properties in the node panel.
        void showDetails(QTreeWidget * tree) override;

        /// Hide all node's properties from the node panel.
        void hideDetails(QTreeWidget * tree) override;

        /// Setter : The path to the image.
        void setPath(const QString &path);

        GLSLData nodeToGLSL() override;

    protected:
        /// The event filter: see Qt documentation.
        bool eventFilter(QObject *object, QEvent *event) override;

    private:
        /// The path to the image.
        QString m_path;

        /// Where the image will be displayed.
        QLabel * m_label;

        /// Where the image is stored.
        QPixmap m_pixmap;
    };


}


#endif //SHADERGRAPH_TEXTURENODE_H
