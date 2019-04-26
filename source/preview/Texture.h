#pragma once

#include <fstream>

#include <core/Core.h>

#include "OpenGL.h"

#include "../vendor/stb/stb_image.h"

namespace ShaderGraph
{
    class Texture
    {
    public:
        /// Default Constructor.
        Texture() = default;

        /// Constructor.
        Texture(const std::string& path, const std::string& name);

        /// Destructor.
        ~Texture();

        /// Bind this image.
        /// @warning : Only a binded image can be manipulated by OpenGL.
        void bind(const int slot = 0);

        /// Unbind this image.
        /// @warning : Only a binded image can be manipulated by OpenGL.
        void unbind() const;

        /// Getter :
        inline unsigned getId() const { return m_id; }

        /// Getter :
        inline int getSlot() const { return m_slot; }

        /// Getter :
        inline int getWidth() const { return m_width; }

        /// Getter :
        inline int getHeight() const { return m_height; }

        /// Getter :
        inline int getBitsPerPixel() const { return m_bitsPerPixel; }

        inline const std::string& getName() const { return m_name; }

        inline const std::string& getPath() const { return m_filename; }

    private:
        /// The uniform name
        std::string m_name;

        /// The (unique) id of this image.
        unsigned int m_id;

        /// The filename/path of this image.
        std::string m_filename;

        /// The openGL slot of this image.
        int m_slot;

        /// The width of the image.
        int m_width;

        /// The height of the image.
        int m_height;

        /// The number of bits per pixel.
        int m_bitsPerPixel;

        /// The buffer of pixels.
        unsigned char * m_localBuffer;
    };
}