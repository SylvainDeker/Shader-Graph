#ifndef SHADERGRAPH_VECTORNODE_H
#define SHADERGRAPH_VECTORNODE_H

#include "model/InputNode.h"

#include <memory>
#include <limits>

#include <QBoxLayout>
#include <QDoubleSpinBox>

#include <core/Core.h>

#define SPINBOX_STEP 0.1

namespace ShaderGraph
{
    class ScalarNode : public InputNode
    {
    Q_OBJECT

    public:
        ScalarNode();

        float get();
        void set(float v, bool loop = false);

        /// Specified the embedded widget in the Node.
        /// @return : the widget.
        QWidget * embeddedWidget() override
        {
            return m_embeddedWidget;
        }

    public slots:
        void onValue();

    private:
        QWidget * m_embeddedWidget;
        QBoxLayout * m_layout;

        QDoubleSpinBox * m_spinBoxX;
    };

    class Vec2Node : public InputNode
    {
    Q_OBJECT

    public:
        Vec2Node();

        glm::vec2 get();
        void set(const glm::vec2& v, bool loop = false);

        /// Specified the embedded widget in the Node.
        /// @return : the widget.
        QWidget * embeddedWidget() override
        {
            return m_embeddedWidget;
        }

    public slots:
        void onValue();

    private:
        QWidget * m_embeddedWidget;
        QBoxLayout * m_layout;

        QDoubleSpinBox * m_spinBoxX;
        QDoubleSpinBox * m_spinBoxY;
    };

    class Vec3Node : public InputNode
    {
    Q_OBJECT

    public:
        Vec3Node();

        glm::vec3 get();
        void set(const glm::vec3& v, bool loop = false);

        /// Specified the embedded widget in the Node.
        /// @return : the widget.
        QWidget * embeddedWidget() override
        {
            return m_embeddedWidget;
        }

    public slots:
        void onValue();

    private:
        QWidget * m_embeddedWidget;
        QBoxLayout * m_layout;

        QDoubleSpinBox * m_spinBoxX;
        QDoubleSpinBox * m_spinBoxY;
        QDoubleSpinBox * m_spinBoxZ;
    };

    class Vec4Node : public InputNode
    {
        Q_OBJECT

    public:
        Vec4Node();

        glm::vec4 get();
        void set(const glm::vec4& v, bool loop = false);

        /// Specified the embedded widget in the Node.
        /// @return : the widget.
        QWidget * embeddedWidget() override
        {
            return m_embeddedWidget;
        }

    public slots:
      void onValue();

    private:
        QWidget * m_embeddedWidget;
        QBoxLayout * m_layout;

        QDoubleSpinBox * m_spinBoxX;
        QDoubleSpinBox * m_spinBoxY;
        QDoubleSpinBox * m_spinBoxZ;
        QDoubleSpinBox * m_spinBoxW;
    };
}

#endif //SHADERGRAPH_VECTORNODE_H
