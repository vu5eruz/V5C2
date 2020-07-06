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


#include "Engine.h"
#include "Main.h"
#include "OpenGL.h"
#include "State.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <memory>


namespace v5c2
{

    class MainState final : public State
    {
    public:

        MainState() :
            m_Vbo{ gl::CreateBuffer() },
            m_Ibo{ gl::CreateBuffer() },
            m_Program{ gl::CreateProgram() }
        {
            static float Vertices[] =
            {
                -0.5f, -0.5f,
                0.5f, -0.5f,
                0.0f,  0.5f
            };

            static unsigned int Indices[] =
            {
                0, 1, 2
            };

            static const char* VertexShaderSource =
                "#version 120\n"
                "attribute vec2 aPosition;\n"
                "void main()\n"
                "{\n"
                "    gl_Position = vec4(aPosition.x, aPosition.y, 0.0, 1.0);\n"
                "}\n";

            static const char* FragmentShaderSource =
                "#version 120\n"
                "void main()\n"
                "{\n"
                "    float Hue = (gl_FragCoord.x*0.75  + gl_FragCoord.y*0.33) * 3.141592 / 100.0;"
                "    float R = sin(Hue) * 0.5 + 0.5;\n"
                "    float G = sin(Hue + 2.0*3.141592/3.0) * 0.5 + 0.5;\n"
                "    float B = sin(Hue + 4.0*3.141592/3.0) * 0.5 + 0.5;\n"
                "    gl_FragColor = vec4(R, G, B, 1.0f);\n"
                "}\n";

            gl::BindBuffer(gl::BufferTargetEnum::ArrayBuffer, m_Vbo);
            gl::BufferData(gl::BufferTargetEnum::ArrayBuffer, sizeof(Vertices), Vertices, gl::BufferDataUsageEnum::StaticDraw);

            gl::BindBuffer(gl::BufferTargetEnum::ElementArrayBuffer, m_Ibo);
            gl::BufferData(gl::BufferTargetEnum::ElementArrayBuffer, sizeof(Indices), Indices, gl::BufferDataUsageEnum::StaticDraw);

            unsigned int VertexShader{ gl::CreateShader(gl::ShaderTypeEnum::VertexShader) };
            gl::ShaderSource(VertexShader, VertexShaderSource, std::size_t(-1));
            gl::CompileShader(VertexShader);

            unsigned int FragmentShader{ gl::CreateShader(gl::ShaderTypeEnum::FragmentShader) };
            gl::ShaderSource(FragmentShader, FragmentShaderSource, std::size_t(-1));
            gl::CompileShader(FragmentShader);

            gl::AttachShader(m_Program, VertexShader);
            gl::AttachShader(m_Program, FragmentShader);
            gl::LinkProgram(m_Program);
            gl::ValidateProgram(m_Program);

            gl::DeleteShader(VertexShader);
            gl::DeleteShader(FragmentShader);

            m_aPosition = gl::GetAttribLocation(m_Program, "aPosition");
        }


        ~MainState()
        {
            gl::DeleteBuffer(m_Vbo);
            gl::DeleteBuffer(m_Ibo);
        }


        void HandleEvent(const Event&)
        {

        }


        void HandleUpdate(double)
        {

        }


        void HandleDraw() const
        {
            gl::Clear();

            gl::VertexAttribPointer(m_aPosition, 2, gl::VertexAttribPointerTypeEnum::Float, false, sizeof(float) * 2, nullptr);
            gl::EnableVertexAttribArray(m_aPosition);

            gl::UseProgram(m_Program);

            gl::DrawElements(gl::DrawElementsModeEnum::Triangles, 3, gl::DrawElementsTypeEnum::UInt, nullptr);
        }

    private:

        unsigned int m_Vbo{};
        unsigned int m_Ibo{};
        unsigned int m_Program{};
        unsigned int m_aPosition{};
    };


    void Main()
    {
        Engine Eng{};
        Engine::SetInstance(Eng);

        auto StatePtr{ std::make_unique<MainState>() };

        Eng.SetRunning(true);
        Eng.SetState(std::move(StatePtr));
        Eng.Run();
    }

}


#ifdef V5C2_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
int main(int, char**)
#endif
{
    int ExitStatus{ EXIT_SUCCESS };

    try
    {
        v5c2::Main();
    }
    catch (const std::exception& Exc)
    {
        std::cerr <<
            "\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
            "\nUncaught Exception:\n\n\t" << Exc.what() << "\n"
            "\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
            << std::endl;

#if defined(V5C2_PLATFORM_WINDOWS) && defined(V5C2_DEBUG)
        ::FatalAppExitA(0, Exc.what());
#endif

        ExitStatus = EXIT_FAILURE;
    }

    return ExitStatus;
}
