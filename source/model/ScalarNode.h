#ifndef SHADERGRAPH_SCALARNODE_H
#define SHADERGRAPH_SCALARNODE_H

#include <QBoxLayout>
#include <memory>
#include <QDoubleSpinBox>

#include "InputNode.h"

namespace ShaderGraph
{
    class ScalarNode : public InputNode
    {
        Q_OBJECT

    public:
        ScalarNode();

        float getScalar();
        void setScalar(const float v,bool loop=false);

    public slots:
      void onValue();

    private:
      QDoubleSpinBox * m_spinbox_x;
    };


}

#endif //SHADERGRAPH_SCALARNODE_H
