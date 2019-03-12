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

        void showDetails(QVBoxLayout   * layout);

        void set(const QString & path);

    protected:
        /// The event filter: see Qt documentation.
        bool eventFilter(QObject *object, QEvent *event) override;

    private:
        QString m_path;
        QLabel * m_label;
        QPixmap m_pixmap;
        // detail
        QWidget * m_detail;
        QLabel *m_labeldetail;
        QVBoxLayout * m_mainlayout;

    };


}


#endif //SHADERGRAPH_TEXTURENODE_H
