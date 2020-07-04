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

        GLenum Format{};
        switch (Components)
        {
            case 1: Format = GL_LUMINANCE; break;
            case 2: Format = GL_LUMINANCE_ALPHA; break;
            case 3: Format = GL_RGB; break;
            case 4: Format = GL_RGBA; break;
        }

        ::glTexImage2D(GL_TEXTURE_2D, 0, 4, Width, Height, 0, Format, GL_UNSIGNED_BYTE, Data);

        ::stbi_image_free(Data);
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
