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


#ifndef V5C2_OPENGL_H
#define V5C2_OPENGL_H 1

#include <cstddef>
#include <cstdint>

namespace v5c2::gl
{

    enum class GetErrorEnum
    {
        InvalidEnum,
        InvalidValue,
        InvalidOperation,
        NoError,
        OutOfMemory,
        StackOverflow,
        StackUnderflow,
        UnknownError
    };

    enum class VertexAttribPointerTypeEnum
    {
        Byte,
        UByte,
        Short,
        UShort,
        Int,
        UInt,
        Float,
        Double
    };

    enum class DrawElementsModeEnum
    {
        Points,
        LineStrip,
        LineLoop,
        Lines,
        TriangleStrip,
        TriangleFan,
        Triangles
    };

    enum class DrawElementsTypeEnum
    {
        UByte,
        UShort,
        UInt
    };

    enum class BufferTargetEnum
    {
        ArrayBuffer,
        ElementArrayBuffer,
        PixelUnpackBuffer,
        PixelPackBuffer
    };

    enum class BufferDataUsageEnum
    {
        StreamDraw,
        StreamRead,
        StreamCopy,
        StaticDraw,
        StaticRead,
        StaticCopy,
        DynamicDraw,
        DynamicRead,
        DynamicCopy
    };

    enum class ShaderTypeEnum
    {
        VertexShader,
        FragmentShader
    };

    GetErrorEnum GetError();

    void VertexAttribPointer(unsigned int Index, int Size, VertexAttribPointerTypeEnum Type, bool Normalized, std::size_t Stride, const void* Pointer);

    void EnableVertexAttribArray(unsigned int Index);

    void DisableVertexAttribArray(unsigned int Index);

    void DrawElements(DrawElementsModeEnum Mode, std::size_t Count, DrawElementsTypeEnum Type, const void* Indices);

    void BindBuffer(BufferTargetEnum Target, unsigned int Buffer);

    unsigned int CreateBuffer();

    void DeleteBuffer(unsigned int Buffer);

    void BufferData(BufferTargetEnum Target, std::size_t Size, const void* Data, BufferDataUsageEnum Usage);

    unsigned int CreateShader(ShaderTypeEnum Type);

    void ShaderSource(unsigned int Shader, const char* Source, std::size_t Length);

    void CompileShader(unsigned int Shader);

    void DeleteShader(unsigned int Shader);

    unsigned int CreateProgram();

    void AttachShader(unsigned int Program, unsigned int Shader);

    void DetachShader(unsigned int Program, unsigned int Shader);

    void LinkProgram(unsigned int Program);

    void UseProgram(unsigned int Program);

    void DeleteProgram(unsigned int Program);

    void ValidateProgram(unsigned int Program);

    unsigned int GetAttribLocation(unsigned int Program, const char* Name);

    void Clear();

}

#endif // !V5C2_OPENGL_H
