//
// Created by Valentin on 2019-02-18.
//

#include "Texture.h"

namespace ShaderGraph
{
    Texture::Texture(const std::string& path, const std::string& name) :
        m_name(name),
        m_filename(path),
        m_slot(-1)
    {
        stbi_set_flip_vertically_on_load(1);

        m_localBuffer = stbi_load(
                path.c_str(),
                &m_width,
                &m_height,
                &m_bitsPerPixel,
                4 /* RGBA channel */);

        // if the file in not found 
        if (!m_localBuffer)
        {
            LOG_ERROR("Texture::Texture : {0} : file not found", path);
        }
        else
        {
            GL_ASSERT(glGenTextures(1, &m_id));
            GL_ASSERT(glBindTexture(GL_TEXTURE_2D, m_id));

            GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
            GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
            GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
            GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

            GL_ASSERT(
                    glTexImage2D(
                            GL_TEXTURE_2D,
                            0 /* No multi level texture */,
                            GL_RGBA8,
                            m_width,
                            m_height,
                            0 /* No border */,
                            GL_RGBA,
                            GL_UNSIGNED_BYTE,
                            m_localBuffer
                    ) // glTexImage2D
            ); // GL_ASSERT

            GL_ASSERT(glBindTexture(GL_TEXTURE_2D, GL_NULL_ID));
        }

        // free the buffer if the it's valid
        if (m_localBuffer) stbi_image_free(m_localBuffer);
    }

    Texture::~Texture()
    {
        GL_ASSERT(glDeleteTextures(1, &m_id));
    }

    void Texture::bind(const int slot)
    {
        m_slot = slot;
        GL_ASSERT(glActiveTexture(GL_TEXTURE0 + slot));
        GL_ASSERT(glBindTexture(GL_TEXTURE_2D, m_id));
    }

    void Texture::unbind() const
    {
        GL_ASSERT(glBindTexture(GL_TEXTURE_2D, GL_NULL_ID));
    }
}
