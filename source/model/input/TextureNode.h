#ifndef SHADERGRAPH_TEXTURE_H
#define SHADERGRAPH_TEXTURE_H

#include "model/InputNode.h"

#include <memory>

namespace ShaderGraph
{
    class TextureNode : public InputNode
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

        bool resizable() const override { return true; }

    protected:
        bool eventFilter(QObject *object, QEvent *event) override;

    private:
        QLabel * m_label;

    };


}


#endif //SHADERGRAPH_TEXTURE_H
