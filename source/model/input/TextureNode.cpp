#include "TextureNode.h"

#include <QFileDialog>
#include <QtCore/QDir>
#include <QtCore/QEvent>

namespace ShaderGraph
{
    /// Constructor.
    TextureNode::TextureNode() :
            Node("Texture", "Load a texture"),
            m_path(QString()),
            m_label(new QLabel("Double click \n to load image")),
            m_detail(new QWidget()),
            m_labeldetail(new QLabel()),
            m_mainlayout(new QVBoxLayout())

    {
        inputs() = std::vector<PIN> {
            std::make_shared<Vector2>("UVs") // UVs
        };

        outputs() = std::vector<PIN >{
                std::make_shared<Vector4>("RGBA", this), // RGBA
                std::make_shared<Float>("R", this),   // Red channel
                std::make_shared<Float>("G", this),   // Green channel
                std::make_shared<Float>("B", this),   // Blue channel
                std::make_shared<Float>("A", this)    // Alpha channel
        };

        m_label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

        QFont font = m_label->font();
        font.setBold(true);
        font.setItalic(true);
        m_label->setFont(font);

        m_label->setFixedSize(IMAGE_NODE_SIZE, IMAGE_NODE_SIZE);

        m_label->installEventFilter(this);

        m_detail->setLayout(m_mainlayout);
        m_mainlayout->addWidget(m_labeldetail);


        updateNodeValidation(NodeValidationState::Warning, "Invalid Texture");
    }

    bool TextureNode::eventFilter(QObject * object, QEvent * event)
    {
        if (object == m_label)
        {
            int w = m_label->width();
            int h = m_label->height();

            if (event->type() == QEvent::MouseButtonPress)
            {
                // Get the filename
                m_path = QFileDialog::getOpenFileName(nullptr,
                                                      tr("Open Image"),
                                                      QDir::currentPath(),
                                                      tr("Image Files (*.png *.jpg *.bmp)"));
                set(m_path);
                return true;

            }
            else if (event->type() == QEvent::Resize)
            {
                if (!m_pixmap.isNull())
                {
                    m_label->setPixmap(m_pixmap.scaled(w, h, Qt::KeepAspectRatio));
                }
            }
        }

        return false;
    }

    void TextureNode::set(const QString & path) {
      // Get the image in the Qt format : QPixmap
      m_pixmap = QPixmap(path);
      int w = m_label->width();
      int h = m_label->height();
      // If the image is valid display it else print a log message.
      if (!m_pixmap.isNull())
      {
          m_label->setPixmap(m_pixmap.scaled(w, h, Qt::KeepAspectRatio));
          m_labeldetail->setPixmap(m_pixmap.scaled(w*1.7, h*1.7, Qt::KeepAspectRatio));
          updateNodeValidation(NodeValidationState::Valid);
      }
      else
      {
          LOG_INFO("TextureNode : No texture or Invalid texture");
          m_label->setText("Double click \n to load image");
          updateNodeValidation(NodeValidationState::Warning, "Invalid Texture");
      }

      // Update
      emit dataUpdated(0);
    }

    void TextureNode::showDetails(QVBoxLayout   * layout){
      Node::showDetails(layout);
      if( !isDetailsPanelLayoutInit()){
          setDetailsPanelLayout(layout);
          setDetailsPanelIndexLayout(layout->count());
        layout->addWidget(m_detail);
      }

      layout->itemAt(getDetailsPanelIndexLayout())->widget()->setVisible(true);

      set(m_path); // Allow update data
    }

}
