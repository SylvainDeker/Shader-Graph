#ifndef SHADERGRAPH_COORDNODE_H
#define SHADERGRAPH_COORDNODE_H

#include <QBoxLayout>
#include <memory>
#include <QDoubleSpinBox>

#include "InputNode.h"


namespace ShaderGraph
{
    class Vec3Node : public InputNode
    {
        Q_OBJECT

    public:
        Vec3Node();
        glm::vec3 getVec3()  ;
        void setVec3(const glm::vec3& v3,bool loop=false ) ;
    public slots:
      void onValue();
    private:
      QDoubleSpinBox * m_spinbox_x;
      QDoubleSpinBox * m_spinbox_y;
      QDoubleSpinBox * m_spinbox_z;


    };


}

#endif //SHADERGRAPH_COORDNODE_H
