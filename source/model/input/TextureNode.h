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

        /// Function that display properties in the layout (details)
        void showDetails(QVBoxLayout * layout) override;

        void showDetails(QTreeWidget * tree) override;

        void hideDetails(QTreeWidget * tree) override;

        void setPath(const QString &path);

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "declTexture({0}, {1}, {2}, ...",
                      autoName(outputs()[0]),
                      autoName(outputs()[1]),
                      autoName(outputs()[2]));
            return buffer;
        }

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

        // detail
        QWidget * m_detail;
        QLabel *m_labeldetail;
        QVBoxLayout * m_mainlayout;

    };


}


#endif //SHADERGRAPH_TEXTURENODE_H
