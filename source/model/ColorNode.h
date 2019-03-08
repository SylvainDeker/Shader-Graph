#ifndef SHADERGRAPH_COLORNODE_H
#define SHADERGRAPH_COLORNODE_H

#include <QBoxLayout>
#include <QFrame>
#include <memory>
#include <QPushButton>
#include <QColorDialog>

#include "InputNode.h"

namespace ShaderGraph
{
    class ColorNode : public InputNode
    {
        Q_OBJECT

    public:
        ColorNode();
        glm::vec4 getColor()  ;
        void setColor(const glm::vec4& color ) ;
    private:
      QFrame * m_color_preview;
      QPushButton * m_selecter;

    public slots:
      void onColor();
    };


}

#endif //SHADERGRAPH_COLORNODE_H
