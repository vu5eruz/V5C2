////////////////////////////////////////////////////////////
//
// V5C2 — Vu5eruz's Chess For Two
// Copyright (C) 2020 vu5eruz (undefined@disroot.org)
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////


#include "OpenGL.h"

#include <glad/glad.h>

#include <sstream>
#include <string>


namespace v5c2::gl
{

    void ThrowOnError()
    {
        GetErrorEnum Error{ GetError() };
        if (Error == GetErrorEnum::NoError)
        {
            return;
        }

        std::string Message("OpenGL Error(s) :");

        do
        {
            switch (Error)
            {
                case GetErrorEnum::InvalidEnum:
                    Message += "\n\tEnumeration argument out of range";
                    break;

                case GetErrorEnum::InvalidValue:
                    Message += "\n\tNumeric argument out of range";
                    break;

                case GetErrorEnum::InvalidOperation:
                    Message += "\n\tOperation illegal in current state";
                    break;

                case GetErrorEnum::OutOfMemory:
                    Message += "\n\tNot enough memory left to execute command";
                    break;

                case GetErrorEnum::StackOverflow:
                    Message += "\n\tCommand would cause a stack overflow";
                    break;

                case GetErrorEnum::StackUnderflow:
                    Message += "\n\tCommand would cause a stack underflow";
                    break;

                case GetErrorEnum::UnknownError:
                    Message += "\n\tUnknown Error";
                    break;
            }
        }
        while ((Error = GetError()) != GetErrorEnum::NoError);

        throw std::runtime_error(Message);
    }


    GetErrorEnum GetError()
    {
        switch (::glGetError())
        {
            case GL_INVALID_ENUM: return GetErrorEnum::InvalidEnum;
            case GL_INVALID_VALUE: return GetErrorEnum::InvalidValue;
            case GL_INVALID_OPERATION: return GetErrorEnum::InvalidOperation;
            case GL_NO_ERROR: return GetErrorEnum::NoError;
            case GL_OUT_OF_MEMORY: return GetErrorEnum::OutOfMemory;
            case GL_STACK_OVERFLOW: return GetErrorEnum::StackOverflow;
            case GL_STACK_UNDERFLOW: return GetErrorEnum::StackUnderflow;
            default: return GetErrorEnum::UnknownError;
        }
    }


    void VertexAttribPointer(unsigned int Index, int Size, VertexAttribPointerTypeEnum Type, bool Normalized, std::size_t Stride, const void* Pointer)
    {
        GLenum TypeInGL{};

        switch (Type)
        {
            case VertexAttribPointerTypeEnum::Byte: TypeInGL = GL_BYTE; break;
            case VertexAttribPointerTypeEnum::UByte: TypeInGL = GL_UNSIGNED_BYTE; break;
            case VertexAttribPointerTypeEnum::Short: TypeInGL = GL_SHORT; break;
            case VertexAttribPointerTypeEnum::UShort: TypeInGL = GL_UNSIGNED_SHORT; break;
            case VertexAttribPointerTypeEnum::Int: TypeInGL = GL_INT; break;
            case VertexAttribPointerTypeEnum::UInt: TypeInGL = GL_UNSIGNED_INT; break;
            case VertexAttribPointerTypeEnum::Float: TypeInGL = GL_FLOAT; break;
            case VertexAttribPointerTypeEnum::Double: TypeInGL = GL_DOUBLE; break;
        }

        ::glVertexAttribPointer(Index, Size, TypeInGL, Normalized, Stride, Pointer);

        ThrowOnError();
    }


    void EnableVertexAttribArray(unsigned int Index)
    {
        ::glEnableVertexAttribArray(Index);

        ThrowOnError();
    }


    void DisableVertexAttribArray(unsigned int Index)
    {
        ::glDisableVertexAttribArray(Index);

        ThrowOnError();
    }


    void DrawElements(DrawElementsModeEnum Mode, std::size_t Count, DrawElementsTypeEnum Type, const void* Indices)
    {
        GLenum ModeInGL{};
        GLenum TypeInGL{};

        switch (Mode)
        {
            case DrawElementsModeEnum::Points: ModeInGL = GL_POINTS; break;
            case DrawElementsModeEnum::LineStrip: ModeInGL = GL_LINE_STRIP; break;
            case DrawElementsModeEnum::LineLoop: ModeInGL = GL_LINE_LOOP; break;
            case DrawElementsModeEnum::Lines: ModeInGL = GL_LINES; break;
            case DrawElementsModeEnum::TriangleStrip: ModeInGL = GL_TRIANGLE_STRIP; break;
            case DrawElementsModeEnum::TriangleFan: ModeInGL = GL_TRIANGLE_FAN; break;
            case DrawElementsModeEnum::Triangles: ModeInGL = GL_TRIANGLES; break;
        }

        switch (Type)
        {
            case DrawElementsTypeEnum::UByte: TypeInGL = GL_UNSIGNED_BYTE; break;
            case DrawElementsTypeEnum::UShort: TypeInGL = GL_UNSIGNED_SHORT; break;
            case DrawElementsTypeEnum::UInt: TypeInGL = GL_UNSIGNED_INT; break;
        }

        ::glDrawElements(ModeInGL, Count, TypeInGL, Indices);
    }


    void BindBuffer(BufferTargetEnum Target, unsigned int Buffer)
    {
        GLenum TargetInGL{};

        switch (Target)
        {
            case BufferTargetEnum::ArrayBuffer: TargetInGL = GL_ARRAY_BUFFER; break;
            case BufferTargetEnum::ElementArrayBuffer: TargetInGL = GL_ELEMENT_ARRAY_BUFFER; break;
            case BufferTargetEnum::PixelUnpackBuffer: TargetInGL = GL_PIXEL_UNPACK_BUFFER; break;
            case BufferTargetEnum::PixelPackBuffer: TargetInGL = GL_PIXEL_PACK_BUFFER; break;
        }

        ::glBindBuffer(TargetInGL, Buffer);

        ThrowOnError();
    }


    unsigned int CreateBuffer()
    {
        GLuint BufferInGL{};

        ::glGenBuffers(1, &BufferInGL);

        ThrowOnError();

        return BufferInGL;
    }


    void DeleteBuffer(unsigned int Buffer)
    {
        GLuint BufferInGL{Buffer};

        ::glDeleteBuffers(1, &BufferInGL);

        ThrowOnError();
    }


    void BufferData(BufferTargetEnum Target, std::size_t Size, const void* Data, BufferDataUsageEnum Usage)
    {
        GLenum TargetInGL{};
        GLenum UsageInGL{};

        switch (Target)
        {
            case BufferTargetEnum::ArrayBuffer: TargetInGL = GL_ARRAY_BUFFER; break;
            case BufferTargetEnum::ElementArrayBuffer: TargetInGL = GL_ELEMENT_ARRAY_BUFFER; break;
            case BufferTargetEnum::PixelUnpackBuffer: TargetInGL = GL_PIXEL_UNPACK_BUFFER; break;
            case BufferTargetEnum::PixelPackBuffer: TargetInGL = GL_PIXEL_PACK_BUFFER; break;
        }

        switch (Usage)
        {
            case BufferDataUsageEnum::StreamDraw: UsageInGL = GL_STREAM_DRAW; break;
            case BufferDataUsageEnum::StreamRead: UsageInGL = GL_STREAM_READ; break;
            case BufferDataUsageEnum::StreamCopy: UsageInGL = GL_STREAM_COPY; break;
            case BufferDataUsageEnum::StaticDraw: UsageInGL = GL_STATIC_DRAW; break;
            case BufferDataUsageEnum::StaticRead: UsageInGL = GL_STATIC_READ; break;
            case BufferDataUsageEnum::StaticCopy: UsageInGL = GL_STATIC_COPY; break;
            case BufferDataUsageEnum::DynamicDraw: UsageInGL = GL_DYNAMIC_DRAW; break;
            case BufferDataUsageEnum::DynamicRead: UsageInGL = GL_DYNAMIC_READ; break;
            case BufferDataUsageEnum::DynamicCopy: UsageInGL = GL_DYNAMIC_COPY; break;
        }

        ::glBufferData(TargetInGL, Size, Data, UsageInGL);

        ThrowOnError();
    }


    unsigned int CreateShader(ShaderTypeEnum Type)
    {
        GLenum TypeInGL{};
        GLuint Shader{};

        switch (Type)
        {
            case ShaderTypeEnum::VertexShader: TypeInGL = GL_VERTEX_SHADER; break;
            case ShaderTypeEnum::FragmentShader: TypeInGL = GL_FRAGMENT_SHADER; break;
        }

        Shader = ::glCreateShader(TypeInGL);
        if (Shader <= 0)
        {
            ThrowOnError();
        }

        return Shader;
    }


    void ShaderSource(unsigned int Shader, const char* Source, std::size_t Length)
    {
        const GLchar* SourceInGL{ static_cast<const GLchar*>(Source) };
        const GLint LengthInGL{ (Length == std::size_t(-1)) ? -1 : static_cast<GLint>(Length) };

        ::glShaderSource(Shader, 1, &SourceInGL, &LengthInGL);

        ThrowOnError();
    }


    void CompileShader(unsigned int Shader)
    {
        ::glCompileShader(Shader);

        ThrowOnError();

        if (GLint Status{}; ::glGetShaderiv(Shader, GL_COMPILE_STATUS, &Status), !Status)
        {
            GLint InfoLogLength{};
            ::glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &InfoLogLength);

            std::string InfoLog(InfoLogLength, '\0');
            ::glGetShaderInfoLog(Shader, InfoLogLength, nullptr, InfoLog.data());

            std::string Message("Shader Compilation Failure :\n");
            Message += InfoLog;

            throw std::runtime_error(Message);
        }
    }


    void DeleteShader(unsigned int Shader)
    {
        ::glDeleteShader(Shader);

        ThrowOnError();
    }


    unsigned int CreateProgram()
    {
        GLuint Program{ ::glCreateProgram() };
        if (Program <= 0)
        {
            ThrowOnError();
        }

        return Program;
    }


    void AttachShader(unsigned int Program, unsigned int Shader)
    {
        ::glAttachShader(Program, Shader);

        ThrowOnError();
    }


    void DetachShader(unsigned int Program, unsigned int Shader)
    {
        ::glDetachShader(Program, Shader);

        ThrowOnError();
    }


    void LinkProgram(unsigned int Program)
    {
        ::glLinkProgram(Program);

        ThrowOnError();
    }


    void UseProgram(unsigned int Program)
    {
        ::glUseProgram(Program);

        ThrowOnError();
    }


    void DeleteProgram(unsigned int Program)
    {
        ::glDeleteProgram(Program);

        ThrowOnError();
    }


    void ValidateProgram(unsigned int Program)
    {
        ::glValidateProgram(Program);

        ThrowOnError();
    }


    unsigned int GetAttribLocation(unsigned int Program, const char* Name)
    {
        GLint AttribLoc{ ::glGetAttribLocation(Program, Name) };
        if (AttribLoc < 0)
        {
            ThrowOnError();
        }

        return AttribLoc;
    }


    unsigned int GetUniformLocation(unsigned int Program, const char* Name)
    {
        GLint UniformLoc{ ::glGetUniformLocation(Program, Name) };
        if (UniformLoc < 0)
        {
            ThrowOnError();
        }

        return UniformLoc;
    }


#define DEFINE_UNIFORM_FOR_VARIABLE(PARAMETERS, CALL) \
    void Uniform PARAMETERS                           \
    {                                                 \
        CALL;                                         \
        ThrowOnError();                               \
    }


    DEFINE_UNIFORM_FOR_VARIABLE((unsigned int UniformLoc, float V0), ::glUniform1f(UniformLoc, V0));
    DEFINE_UNIFORM_FOR_VARIABLE((unsigned int UniformLoc, float V0, float V1), ::glUniform2f(UniformLoc, V0, V1));
    DEFINE_UNIFORM_FOR_VARIABLE((unsigned int UniformLoc, float V0, float V1, float V2), ::glUniform3f(UniformLoc, V0, V1, V2));
    DEFINE_UNIFORM_FOR_VARIABLE((unsigned int UniformLoc, float V0, float V1, float V2, float V3), ::glUniform4f(UniformLoc, V0, V1, V2, V3));

    DEFINE_UNIFORM_FOR_VARIABLE((unsigned int UniformLoc, int V0), ::glUniform1i(UniformLoc, V0));
    DEFINE_UNIFORM_FOR_VARIABLE((unsigned int UniformLoc, int V0, int V1), ::glUniform2i(UniformLoc, V0, V1));
    DEFINE_UNIFORM_FOR_VARIABLE((unsigned int UniformLoc, int V0, int V1, int V2), ::glUniform3i(UniformLoc, V0, V1, V2));
    DEFINE_UNIFORM_FOR_VARIABLE((unsigned int UniformLoc, int V0, int V1, int V2, int V3), ::glUniform4i(UniformLoc, V0, V1, V2, V3));


#undef DEFINE_UNIFORM_FOR_VARIABLE


    void Clear()
    {
        ::glClear(GL_COLOR_BUFFER_BIT);
    }

}
