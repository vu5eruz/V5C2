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
#include "State.h"
#include "Stbs.h"
#include "Utils.h"

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>


namespace v5c2
{

    namespace
    {

        void SetWindowIcon(GLFWwindow* Window, const char* Path)
        {
            int Width{}, Height{}, Channels{4};
            unsigned char* Pixels{ ::stbi_load(Path, &Width, &Height, &Channels, 4) };
            if (Pixels == nullptr)
            {
                char Message[512];
                ::stbsp_snprintf(Message, sizeof(Message), "Engine :  Could not open %s :  %s", Path, ::stbi_failure_reason());
                throw std::runtime_error(Message);
            }

            GLFWimage Icon{};
            Icon.width = Width;
            Icon.height = Height;
            Icon.pixels = Pixels;

            ::glfwSetWindowIcon(Window, 1, &Icon);

            ::stbi_image_free(Pixels);
        }

    }


    Engine* Engine::GlobalInstance{};


    Engine::Engine() try
    {
        ::glfwSetErrorCallback(Engine::ErrorCallback);

        if (!::glfwInit())
        {
            throw std::runtime_error("Engine :  GLFW :  Could not initialize library");
        }

        ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        ::glfwWindowHint(GLFW_DEPTH_BITS, 0);
        ::glfwWindowHint(GLFW_STENCIL_BITS, 0);
        ::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_Window = ::glfwCreateWindow(800, 600, "V5C2 " V5C2_VERSION, nullptr, nullptr);
        if (m_Window == nullptr)
        {
            throw std::runtime_error("Engine :  GLFW :  Could not create window");
        }

        SetWindowIcon(m_Window, "images/V5c2Icon.png");

        ::glfwMakeContextCurrent(m_Window);

        if (!::gladLoadGLLoader(reinterpret_cast<GLADloadproc>(::glfwGetProcAddress)))
        {
            throw std::runtime_error("Engine :  OpenGL :  Could not initialize context");
        }

        ::glfwSwapInterval(1);
    }
    catch (...)
    {
        ::glfwDestroyWindow(m_Window);
        ::glfwTerminate();

        throw;
    }


    Engine::~Engine()
    {
        ::glfwTerminate();
    }


    void Engine::Run()
    {
        while (IsRunning() && !::glfwWindowShouldClose(m_Window))
        {
            if (m_PendingState)
            {
                m_CurrentState = std::move(m_PendingState);
            }

            ::glfwPollEvents();

            DispatchUpdates();

            DispatchDraw();

            ::glfwSwapBuffers(m_Window);

            utils::Sleep(1000 / 60);
        }
    }


    void Engine::GetCursorPosition(double& X, double& Y)
    {
        ::glfwGetCursorPos(m_Window, &X, &Y);
    }


    void Engine::SetCursorPosition(double X, double Y)
    {
        ::glfwSetCursorPos(m_Window, X, Y);
    }


    void Engine::SetState(std::unique_ptr<State>&& NewState)
    {
        m_PendingState = std::move(NewState);
    }


    void Engine::DispatchUpdates()
    {
        m_CurrentState->HandleUpdate(1.0 / 60.0);
    }


    void Engine::DispatchDraw()
    {
        m_CurrentState->HandleDraw();
    }


    void Engine::ErrorCallback(int Error, const char* Description)
    {
        std::cerr << "Engine :  GLFW :  Error (" << Error << ") :\n\t" << Description << std::endl;
    }
}
