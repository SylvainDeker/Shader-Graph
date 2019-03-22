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
      void set(const float& v);


      /// Specified the embedded widget in the Node.
      /// @return : the widget.
      QWidget * embeddedWidget() override
      {
          return m_embeddedWidget;
      }

      /// Function that display properties in the layout (details)
      void showDetails(QVBoxLayout * layout) override;

      std::string nodeToGLSL() override
      {
          std::string buffer;
          GLSL_CODE(buffer,
                    "declVector({0}, ...",
                    autoName(outputs()[0]));
          return buffer;
      }

  public slots:
    void onValue();
    void onValueDetail();

  private:
      float m_value;
      QWidget * m_embeddedWidget;
      QBoxLayout * m_layout;

      QDoubleSpinBox * m_spinBoxX;
      QDoubleSpinBox * m_spinBoxY;
      QDoubleSpinBox * m_spinBoxZ;
      QDoubleSpinBox * m_spinBoxW;

      QWidget * m_detail;
      QVBoxLayout * m_mainlayout;
      QDoubleSpinBox * m_spinBoxXdetail;
      QDoubleSpinBox * m_spinBoxYdetail;
      QDoubleSpinBox * m_spinBoxZdetail;
      QDoubleSpinBox * m_spinBoxWdetail;

  };

    class Vec2Node : public InputNode
    {
        Q_OBJECT

    public:
        Vec2Node();

        glm::vec2 get();
        void set(const glm::vec2& v);


        /// Specified the embedded widget in the Node.
        /// @return : the widget.
        QWidget * embeddedWidget() override
        {
            return m_embeddedWidget;
        }

        /// Function that display properties in the layout (details)
        void showDetails(QVBoxLayout * layout) override;

    public slots:
      void onValue();
      void onValueDetail();

    private:
        glm::vec2 m_value;
        QWidget * m_embeddedWidget;
        QBoxLayout * m_layout;

        QDoubleSpinBox * m_spinBoxX;
        QDoubleSpinBox * m_spinBoxY;


        QWidget * m_detail;
        QVBoxLayout * m_mainlayout;
        QDoubleSpinBox * m_spinBoxXdetail;
        QDoubleSpinBox * m_spinBoxYdetail;

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "declVector({0}, ...",
                      autoName(outputs()[0]));
            return buffer;
        }
    };

    class Vec3Node : public InputNode
    {
        Q_OBJECT

    public:
        Vec3Node();

        glm::vec3 get();
        void set(const glm::vec3& v);


        /// Specified the embedded widget in the Node.
        /// @return : the widget.
        QWidget * embeddedWidget() override
        {
            return m_embeddedWidget;
        }

        /// Function that display properties in the layout (details)
        void showDetails(QVBoxLayout * layout) override;

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "declVector({0}, ...",
                      autoName(outputs()[0]));
            return buffer;
        }

    public slots:
      void onValue();
      void onValueDetail();

    private:
        glm::vec3 m_value;
        QWidget * m_embeddedWidget;
        QBoxLayout * m_layout;

        QDoubleSpinBox * m_spinBoxX;
        QDoubleSpinBox * m_spinBoxY;
        QDoubleSpinBox * m_spinBoxZ;
        QDoubleSpinBox * m_spinBoxW;

        QWidget * m_detail;
        QVBoxLayout * m_mainlayout;
        QDoubleSpinBox * m_spinBoxXdetail;
        QDoubleSpinBox * m_spinBoxYdetail;
        QDoubleSpinBox * m_spinBoxZdetail;
        QDoubleSpinBox * m_spinBoxWdetail;

    };

    class Vec4Node : public InputNode
    {
        Q_OBJECT

    public:
        Vec4Node();

        glm::vec4 get();
        void set(const glm::vec4& v);


        /// Specified the embedded widget in the Node.
        /// @return : the widget.
        QWidget * embeddedWidget() override
        {
            return m_embeddedWidget;
        }

        /// Function that display properties in the layout (details)
        void showDetails(QVBoxLayout * layout) override;

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "declVector({0}, ...",
                      autoName(outputs()[0]));
            return buffer;
        }

    public slots:
      void onValue();
      void onValueDetail();

    private:
        glm::vec4 m_value;
        QWidget * m_embeddedWidget;
        QBoxLayout * m_layout;

        QDoubleSpinBox * m_spinBoxX;
        QDoubleSpinBox * m_spinBoxY;
        QDoubleSpinBox * m_spinBoxZ;
        QDoubleSpinBox * m_spinBoxW;

        QWidget * m_detail;
        QVBoxLayout * m_mainlayout;
        QDoubleSpinBox * m_spinBoxXdetail;
        QDoubleSpinBox * m_spinBoxYdetail;
        QDoubleSpinBox * m_spinBoxZdetail;
        QDoubleSpinBox * m_spinBoxWdetail;

    };
}

#endif //SHADERGRAPH_VECTORNODE_H
