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
        QWidget * embeddedWidget() override { return _mainwidget; }
        glm::vec4 getColor()  ;
        void setColor(const glm::vec4& color ) ;
    private:
      QWidget * _mainwidget;
      QBoxLayout * _layout;
      QFrame * _color_preview;
      QPushButton * _selecter;
      
    public slots:
      void onColor();
    };


}

#endif //SHADERGRAPH_COLORNODE_H
