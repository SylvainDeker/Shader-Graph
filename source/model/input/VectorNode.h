#ifndef SHADERGRAPH_VECTORNODE_H
#define SHADERGRAPH_VECTORNODE_H

#include <memory>
#include <limits>

#include <QBoxLayout>
#include <QTreeWidget>
#include <QDoubleSpinBox>
#include <QTreeWidgetItem>

#include <core/Core.h>

#include "../Node.h"

#define SPINBOX_STEP 0.1
#define SPINBOX_VALUE_CHANGED_SLOT static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged)

namespace ShaderGraph
{
  class ScalarNode : public Node
  {
      Q_OBJECT

  public:
      ScalarNode();

      /// Getter : the value of this node.
      inline float get() const { return m_value; };

      /// Setter : the value of this node.
      inline void set(const float& value)
      {
          m_value = value;
          m_spinBoxX->setValue(value);
          m_detailsPanelSpinBoxX->setValue(value);
      }

      /// Specified the embedded widget in the Node.
      /// @return : the widget.
      QWidget * embeddedWidget() override
      {
          return m_embeddedWidget;
      }

      void showDetails(QTreeWidget * tree) override;

      void hideDetails(QTreeWidget * tree) override;

      std::string nodeToGLSL() override
      {
          std::string buffer;
          GLSL_CODE(buffer,
                    "declVector({0}, ...",
                    autoName(outputs()[0]));
          return buffer;
      }

  public slots:
    inline void onValueChanged()
    {
          set(static_cast<float>(m_spinBoxX->value()));
    }

    inline void onDetailValueChanged()
    {
          set(static_cast<float>(m_detailsPanelSpinBoxX->value()));
    }

  private:
      float m_value;

      QWidget * m_embeddedWidget;

      QBoxLayout * m_layout;

      QDoubleSpinBox * m_spinBoxX;
      QDoubleSpinBox * m_detailsPanelSpinBoxX;

      /* =============== Start QTreeWidget items definition ===============*/

      QTreeWidgetItem * m_axisSection = nullptr;
        QTreeWidgetItem * m_xSection = nullptr;
            QTreeWidgetItem * m_xItem = nullptr;

      /* =============== End QTreeWidget items definition ===============*/
  };

    class Vec2Node : public Node
    {
        Q_OBJECT

    public :
        Vec2Node();

        /// Getter : the value of this node.
        inline glm::vec2 get() const { return m_value; };

        /// Setter : the value of this node.
        void set(const glm::vec2& value);

        /// Specified the embedded widget in the Node.
        /// @return : the widget.
        QWidget * embeddedWidget() override
        {
            return m_embeddedWidget;
        }

        /// Show all node's properties in the node panel.
        void showDetails(QTreeWidget * tree) override;

        /// Hide all node's properties from the node panel.
        void hideDetails(QTreeWidget * tree) override;

        std::string nodeToGLSL() override
        {
            std::string buffer;
            GLSL_CODE(buffer,
                      "declVector({0}, ...",
                      autoName(outputs()[0]));
            return buffer;
        }

    public slots:
        inline void onValueChanged()
        {
            set(glm::vec2(
                    m_spinBoxX->value(),
                    m_spinBoxY->value())
            );
        }

        inline void onDetailValueChanged()
        {
            set(glm::vec2(
                    m_detailsPanelSpinBoxX->value(),
                    m_detailsPanelSpinBoxY->value())
            );
        }

    private:
        glm::vec2 m_value;
        QWidget * m_embeddedWidget;
        QBoxLayout * m_layout;

        QDoubleSpinBox * m_spinBoxX;
        QDoubleSpinBox * m_spinBoxY;

        QDoubleSpinBox * m_detailsPanelSpinBoxX;
        QDoubleSpinBox * m_detailsPanelSpinBoxY;

        /* =============== Start QTreeWidget items definition ===============*/
        QTreeWidgetItem * m_axisSection = nullptr;

        QTreeWidgetItem * m_xSection = nullptr;
        QTreeWidgetItem * m_xItem = nullptr;

        QTreeWidgetItem * m_ySection = nullptr;
        QTreeWidgetItem * m_yItem = nullptr;

        /* =============== End QTreeWidget items definition ===============*/
};

    class Vec3Node : public Node
    {
        Q_OBJECT

    public:
        Vec3Node();

        /// Getter : the value of this node.
        inline glm::vec3 get() const { return m_value; };

        /// Setter : the value of this node.
        void set(const glm::vec3& value);

        /// Specified the embedded widget in the Node.
        /// @return : the widget.
        QWidget * embeddedWidget() override
        {
            return m_embeddedWidget;
        }

        /// Show all node's properties in the node panel.
        void showDetails(QTreeWidget * tree) override;

        /// Hide all node's properties from the node panel.
        void hideDetails(QTreeWidget * tree) override;

        std::string nodeToGLSL() override
        {
            return "";
        }

    public slots:
        inline void onValueChanged()
        {
            set(glm::vec3(
                    m_spinBoxX->value(),
                    m_spinBoxY->value(),
                    m_spinBoxZ->value())
            );
        }

        inline void onDetailValueChanged()
        {
            set(glm::vec3(
                    m_detailsPanelSpinBoxX->value(),
                    m_detailsPanelSpinBoxY->value(),
                    m_detailsPanelSpinBoxZ->value())
            );
        }

    private:
        glm::vec3 m_value;
        QWidget * m_embeddedWidget;
        QBoxLayout * m_layout;

        QDoubleSpinBox * m_spinBoxX;
        QDoubleSpinBox * m_spinBoxY;
        QDoubleSpinBox * m_spinBoxZ;

        QDoubleSpinBox * m_detailsPanelSpinBoxX;
        QDoubleSpinBox * m_detailsPanelSpinBoxY;
        QDoubleSpinBox * m_detailsPanelSpinBoxZ;

        /* =============== Start QTreeWidget items definition ===============*/

        QTreeWidgetItem * m_axisSection = nullptr;

        QTreeWidgetItem * m_xSection = nullptr;
        QTreeWidgetItem * m_xItem = nullptr;

        QTreeWidgetItem * m_ySection = nullptr;
        QTreeWidgetItem * m_yItem = nullptr;

        QTreeWidgetItem * m_zSection = nullptr;
        QTreeWidgetItem * m_zItem = nullptr;

        /* =============== End QTreeWidget items definition ===============*/

    };

    class Vec4Node : public Node
    {
        Q_OBJECT

    public:
        Vec4Node();


        /// Getter : the value of this node.
        inline glm::vec4 get() const { return m_value; };

        /// Setter : the value of this node.
        void set(const glm::vec4& value);

        /// Specified the embedded widget in the Node.
        /// @return : the widget.
        QWidget * embeddedWidget() override
        {
            return m_embeddedWidget;
        }

        /// Show all node's properties in the node panel.
        void showDetails(QTreeWidget * tree) override;

        /// Hide all node's properties from the node panel.
        void hideDetails(QTreeWidget * tree) override;

        std::string nodeToGLSL() override
        {
            return "";
        }

    public slots:
      inline void onValueChanged()
      {
          set(glm::vec4(
                  m_spinBoxX->value(),
                  m_spinBoxY->value(),
                  m_spinBoxZ->value(),
                  m_spinBoxW->value())
          );
      }

        inline void onDetailValueChanged()
        {
            set(glm::vec4(
                    m_detailsPanelSpinBoxX->value(),
                    m_detailsPanelSpinBoxY->value(),
                    m_detailsPanelSpinBoxZ->value(),
                    m_detailsPanelSpinBoxW->value())
            );
        }

    private:
        glm::vec4 m_value;

        QWidget * m_embeddedWidget;

        QBoxLayout * m_layout;

        QDoubleSpinBox * m_spinBoxX;
        QDoubleSpinBox * m_spinBoxY;
        QDoubleSpinBox * m_spinBoxZ;
        QDoubleSpinBox * m_spinBoxW;

        QDoubleSpinBox * m_detailsPanelSpinBoxX;
        QDoubleSpinBox * m_detailsPanelSpinBoxY;
        QDoubleSpinBox * m_detailsPanelSpinBoxZ;
        QDoubleSpinBox * m_detailsPanelSpinBoxW;

        /* =============== Start QTreeWidget items definition ===============*/

        QTreeWidgetItem * m_axisSection = nullptr;

        QTreeWidgetItem * m_xSection = nullptr;
        QTreeWidgetItem * m_xItem = nullptr;

        QTreeWidgetItem * m_ySection = nullptr;
        QTreeWidgetItem * m_yItem = nullptr;

        QTreeWidgetItem * m_zSection = nullptr;
        QTreeWidgetItem * m_zItem = nullptr;

        QTreeWidgetItem * m_wSection = nullptr;
        QTreeWidgetItem * m_wItem = nullptr;

        /* =============== End QTreeWidget items definition ===============*/
    };
}

#endif //SHADERGRAPH_VECTORNODE_H
