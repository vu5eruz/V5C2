//==========================================================
//
//  V5C2  --  src/client/texture.cpp
//
//==========================================================


#include "client/platform.h"
#include "client/texture.h"
#include "core/stbs.h"

#include <stdexcept>


namespace v5c2::client
{
    namespace
    {
        constexpr GLenum GlEnumFromPixelFormat(PixelFormat Format)
        {
            switch (Format)
            {
                default:
                case PixelFormat::Red: return GL_RED;
                case PixelFormat::Green: return GL_GREEN;
                case PixelFormat::Blue: return GL_BLUE;
                case PixelFormat::Alpha: return GL_ALPHA;
                case PixelFormat::Rgb: return GL_RGB;
                case PixelFormat::Bgr: return GL_BGR;
                case PixelFormat::RgbAlpha: return GL_RGBA;
                case PixelFormat::BgrAlpha: return GL_BGRA;
                case PixelFormat::Luminance: return GL_LUMINANCE;
                case PixelFormat::LuminanceAlpha: return GL_LUMINANCE_ALPHA;
            };
        }


        constexpr GLenum GlEnumFromPixelType(PixelType Type)
        {
            switch (Type)
            {
                default:
                case PixelType::Uint8: return GL_UNSIGNED_BYTE;
                case PixelType::Sint8: return GL_BYTE;
                case PixelType::Uint16: return GL_UNSIGNED_SHORT;
                case PixelType::Sint16: return GL_SHORT;
                case PixelType::Uint32: return GL_UNSIGNED_INT;
                case PixelType::Sint32: return GL_INT;
                case PixelType::Float32: return GL_FLOAT;
            }
        }
    }


    Texture::Texture()
    {
        ::glGenTextures(1, &m_TexId);
    }


    Texture::~Texture()
    {
        ::glDeleteTextures(1, &m_TexId);
    }


    void Texture::Bind(const Texture* PtrTxt)
    {
        if (PtrTxt)
        {
            ::glBindTexture(GL_TEXTURE_2D, PtrTxt->m_TexId);
        }
        else
        {
            ::glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
    
        
    void Texture::Image(const std::string_view& Path)
    {
        int Width{};
        int Height{};
        int Components{};
        void* Data{ ::stbi_load(Path.data(), &Width, &Height, &Components, 0) };
        if (!Data)
        {
            char Message[256];
            ::stbsp_snprintf(Message, sizeof(Message), "Can't load %s : %s", Path.data(), stbi_failure_reason());
            throw std::runtime_error(Message);
        }

        PixelFormat Format{};
        switch (Components)
        {
            case 1: Format = PixelFormat::Luminance; break;
            case 2: Format = PixelFormat::Luminance; break;
            case 3: Format = PixelFormat::Rgb; break;
            case 4: Format = PixelFormat::RgbAlpha; break;
        }

        Image(Width, Height, Format, PixelType::Uint8, Data);

        ::stbi_image_free(Data);
    }


    void Texture::Image(std::size_t Width, std::size_t Height, PixelFormat Format, PixelType Type, const void* Data)
    {
        ::glTexImage2D(
            GL_TEXTURE_2D,
            0,
            4,
            static_cast<GLsizei>(Width),
            static_cast<GLsizei>(Height),
            0,
            GlEnumFromPixelFormat(Format),
            GlEnumFromPixelType(Type),
            Data
        );
    }


    void Texture::SubImage(std::size_t X, std::size_t Y, std::size_t Width, std::size_t Height, PixelFormat Format, PixelType Type, const void* Data)
    {
        ::glTexImage2D(
            GL_TEXTURE_2D,
            0,
            X,
            Y,
            static_cast<GLsizei>(Width),
            static_cast<GLsizei>(Height),
            GlEnumFromPixelFormat(Format),
            GlEnumFromPixelType(Type),
            Data
        );
    }


    void Texture::Parameter(ParameterType Ptype, ParameterValue Pvalue)
    {
        GLenum Type{};
        GLenum Value{};

        switch (Ptype)
        {
            case MinFilter: Type = GL_TEXTURE_MIN_FILTER; break;
            case MagFilter: Type = GL_TEXTURE_MAG_FILTER; break;
        }

        switch (Pvalue)
        {
            case Nearest: Value = GL_NEAREST; break;
            case Linear: Value = GL_LINEAR; break;
        }

        ::glTexParameteri(GL_TEXTURE_2D, Type, Value);
    }
}
