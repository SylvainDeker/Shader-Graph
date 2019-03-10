#include "TextureNode.h"

#include <QFileDialog>
#include <QtCore/QDir>
#include <QtCore/QEvent>

namespace ShaderGraph
{
    /// Constructor.
    TextureNode::TextureNode() :
            Node("Texture", "Load a texture"),
            m_label(new QLabel("Double click \n to load image"))
    {
        inputs() = std::vector<PIN> {
            std::make_shared<Vector2>("UVs") // UVs
        };

        outputs() = std::vector<PIN >{
                std::make_shared<Vector4>("RGBA"), // RGBA
                std::make_shared<Float>("R"),   // Red channel
                std::make_shared<Float>("G"),   // Green channel
                std::make_shared<Float>("B"),   // Blue channel
                std::make_shared<Float>("A")    // Alpha channel
        };

        m_label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

        QFont font = m_label->font();
        font.setBold(true);
        font.setItalic(true);
        m_label->setFont(font);

        m_label->setFixedSize(IMAGE_NODE_SIZE, IMAGE_NODE_SIZE);
        m_label->installEventFilter(this);
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
                QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                                tr("Open Image"),
                                                                QDir::currentPath(),
                                                                tr("Image Files (*.png *.jpg *.bmp)"));
                // Get the image in the Qt format : QPixmap
                m_pixmap = QPixmap(fileName);

                // If the image is valid display it else print a log message.
                if (!m_pixmap.isNull())
                {
                    m_label->setPixmap(m_pixmap.scaled(w, h, Qt::KeepAspectRatio));
                }
                else
                {
                    LOG_INFO("TextureNode : No texture or Invalid texture");
                    m_label->setText("Double click \n to load image");
                }

                // Update
                emit dataUpdated(0);
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
}