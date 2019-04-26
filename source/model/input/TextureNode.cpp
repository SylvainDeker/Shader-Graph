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
            m_label(new QLabel("Click here\n to load an image"))

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

        QFont font = m_label->font();
        font.setBold(true);
        font.setItalic(true);
        m_label->setFont(font);

        m_label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        m_label->installEventFilter(this);
        m_label->resize(IMAGE_NODE_SIZE, IMAGE_NODE_SIZE);

        setValidation(NodeValidationState::Warning, "Invalid Texture");
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
                setPath(m_path);
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

    void TextureNode::setPath(const QString &path) {
      // Get the image in the Qt format : QPixmap
      m_pixmap = QPixmap(path);
      int w = m_label->width();
      int h = m_label->height();

      // Display this image if valid, else print a log message.
      if (!m_pixmap.isNull())
      {
          m_label->setPixmap(m_pixmap.scaled(w, h, Qt::KeepAspectRatio));
          m_label->adjustSize();
          setValidation(NodeValidationState::Valid);
      }
      else
      {
          LOG_INFO("TextureNode : No texture or Invalid texture");
          m_label->setText("Click here\n to load an image");
          m_label->resize(IMAGE_NODE_SIZE, IMAGE_NODE_SIZE);
          setValidation(NodeValidationState::Warning, "Invalid Texture");
      }

      // Update
      emit dataUpdated(0);
    }

    void TextureNode::showDetails(QTreeWidget * tree)
    {
        Node::showDetails(tree);
    }

    void TextureNode::hideDetails(QTreeWidget * tree)
    {
        Node::hideDetails(tree);
    }

    GLSLData TextureNode::nodeToGLSL() {
        GLSLData buffer;

        if (m_path.isNull())
        {
            buffer.hasFailed = true;
            buffer.errmsg = "Invalid Path\n";
            setValidation(NodeValidationState::Error, "Invalid Path");
        }
        else
        {
            std::string uName = m_path.toStdString();
            auto pred = []( auto const& c ) -> bool { return !std::isalnum(c); };
            uName.erase(std::remove_if(uName.begin(), uName.end(), pred), uName.end());
            GLSL_CODE(buffer.uniforms,
                      "// Uniform : \n"
                      "uniform sampler2D u_{0}; \n",
                      uName);

            buffer.texturePaths.push_back({uName, m_path.toStdString()});

            GLSL_CODE(buffer.generatedCode,
                      "{0} = texture(u_{1}, texCoord); \n"
                      "{2} = {0}.r; \n"
                      "{3} = {0}.g; \n"
                      "{4} = {0}.b; \n"
                      "{5} = {0}.a; \n",
                      autoName(outputs()[0]),
                      uName,
                      autoName(outputs()[1]),
                      autoName(outputs()[2]),
                      autoName(outputs()[3]),
                      autoName(outputs()[4]));
        }
        return buffer;
    }
}
