#ifndef SHADERGRAPH_COORDNODE_VEC4_H
#define SHADERGRAPH_COORDNODE_VEC4_H

#include <QBoxLayout>
#include <memory>
#include <QDoubleSpinBox>

#include "InputNode.h"

namespace ShaderGraph
{
    class Vec4Node : public InputNode
    {
        Q_OBJECT

    public:
        Vec4Node();

        glm::vec4 getVec4();
        void setVec4(const glm::vec4& v4,bool loop=false);

    public slots:
      void onValue();

    private:
      QDoubleSpinBox * m_spinbox_x;
      QDoubleSpinBox * m_spinbox_y;
      QDoubleSpinBox * m_spinbox_z;
      QDoubleSpinBox * m_spinbox_w;
    };


}

#endif //SHADERGRAPH_COORDNODE_VEC4_H
