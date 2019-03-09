#ifndef SHADERGRAPH_COORDNODE_VEC2_H
#define SHADERGRAPH_COORDNODE_VEC2_H

#include <QBoxLayout>
#include <memory>
#include <QDoubleSpinBox>

#include "InputNode.h"

namespace ShaderGraph
{
    class Vec2Node : public InputNode
    {
        Q_OBJECT

    public:
        Vec2Node();

        glm::vec2 getVec2();
        void setVec2(const glm::vec2& v2,bool loop=false);

    public slots:
      void onValue();

    private:
      QDoubleSpinBox * m_spinbox_x;
      QDoubleSpinBox * m_spinbox_y;
    };


}

#endif //SHADERGRAPH_COORDNODE_VEC2_H
