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


#include "Background.h"

#include <glad/glad.h>

#include <iostream>
#include <stdexcept>
#include <string>


namespace v5c2
{

    namespace
    {
        const char* VertexShaderSource =
            "#version 120\n"
            "attribute vec2 aPosition;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = vec4(aPosition.x, aPosition.y, 0.0, 1.0);\n"
            "}\n";

        const char* FragmentShaderSource =
            "#version 120\n"
            "uniform vec2 uCenterCoord;\n"
            "uniform vec3 uInnerColor;\n"
            "uniform vec3 uOuterColor;\n"
            "void main()\n"
            "{\n"
            "    float MaxDistance = length(uCenterCoord);\n"
            "    float Distance = distance(gl_FragCoord.xy, uCenterCoord);\n"
            "    vec3 Color = mix(uInnerColor, uOuterColor, Distance / MaxDistance);\n"
            "    gl_FragColor = vec4(Color, 1.0);\n"
            "}\n";

        float Vertices[] =
        {
            -1.0f, -1.0f,  // 0: Top Left
            +1.0f, -1.0f,  // 1: Top Right
            +1.0f, +1.0f,  // 2: Bottom Right
            -1.0f, +1.0f   // 3: Bottom Left
        };

        unsigned int Indices[] =
        {
            0, 1, 2,
            0, 2, 3
        };
    }


    Background::Background() try
    {
        ::glGenBuffers(1, &m_Vbo);
        ::glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
        ::glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
        ::glBindBuffer(GL_ARRAY_BUFFER, 0);

        ::glGenBuffers(1, &m_Ibo);
        ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
        ::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
        ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        auto CheckShader = [](unsigned int Shader)
        {
            if (GLint Status{}; ::glGetShaderiv(Shader, GL_COMPILE_STATUS, &Status), Status == GL_TRUE)
            {
                return;
            }

            GLint InfoLogLength{};
            ::glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &InfoLogLength);

            std::string InfoLog(InfoLogLength, '\0');
            ::glGetShaderInfoLog(Shader, InfoLog.size(), nullptr, InfoLog.data());

            throw std::runtime_error("Background :  Shader Compilation Failure :\n" + InfoLog);
        };

        auto VertexShader{ ::glCreateShader(GL_VERTEX_SHADER) };
        ::glShaderSource(VertexShader, 1, &VertexShaderSource, nullptr);
        ::glCompileShader(VertexShader);
        CheckShader(VertexShader);

        auto FragmentShader{ ::glCreateShader(GL_FRAGMENT_SHADER) };
        ::glShaderSource(FragmentShader, 1, &FragmentShaderSource, nullptr);
        ::glCompileShader(FragmentShader);
        CheckShader(FragmentShader);

        m_Program = ::glCreateProgram();
        ::glAttachShader(m_Program, VertexShader);
        ::glAttachShader(m_Program, FragmentShader);
        ::glLinkProgram(m_Program);

        ::glDeleteShader(FragmentShader);
        ::glDeleteShader(VertexShader);

        ::glBindAttribLocation(m_Program, 0, "aPosition");

        m_Program_uInnerColor = ::glGetUniformLocation(m_Program, "uInnerColor");
        m_Program_uOuterColor = ::glGetUniformLocation(m_Program, "uOuterColor");
        m_Program_uCenterCoord = ::glGetUniformLocation(m_Program, "uCenterCoord");
    }
    catch (...)
    {
        this->~Background();

        throw;
    }


    Background::~Background()
    {
        ::glDeleteBuffers(1, &m_Vbo);
        ::glDeleteBuffers(1, &m_Ibo);
        ::glDeleteProgram(m_Program);
    }


    void Background::SetInnerColor(float R, float G, float B)
    {
        m_InnerColor[0] = R;
        m_InnerColor[1] = G;
        m_InnerColor[2] = B;
    }


    void Background::SetOuterColor(float R, float G, float B)
    {
        m_OuterColor[0] = R;
        m_OuterColor[1] = G;
        m_OuterColor[2] = B;
    }


    void Background::Realize(unsigned int Width, unsigned int Height)
    {
        m_CenterCoord[0] = 0.5f * Width;
        m_CenterCoord[1] = 0.5f * Height;
    }


    void Background::Draw() const
    {
        ::glClear(GL_COLOR_BUFFER_BIT);

        ::glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
        ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);

        ::glUseProgram(m_Program);

        ::glEnableVertexAttribArray(0);
        ::glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);

        ::glUniform3fv(m_Program_uInnerColor, 1, m_InnerColor);
        ::glUniform3fv(m_Program_uOuterColor, 1, m_OuterColor);
        ::glUniform2fv(m_Program_uCenterCoord, 1, m_CenterCoord);

        ::glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        ::glUseProgram(0);

        ::glBindBuffer(GL_ARRAY_BUFFER, 0);
        ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}
