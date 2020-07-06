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

        bool g_Running{ false };
        StatePtr g_CurrentState{};
        StatePtr g_PendingState{};
        GLFWwindow* g_Window{};


        void ErrorCallback(int Error, const char* Description)
        {
            std::cerr << "Engine :  GLFW :  Error (" << Error << ") :\n\t" << Description << std::endl;
        }


    }


    void Engine::Initialize()
    {
        try
        {
            ::glfwSetErrorCallback(ErrorCallback);

            if (!::glfwInit())
            {
                throw std::runtime_error("Engine :  GLFW :  Could not initialize library");
            }

            ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
            ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            ::glfwWindowHint(GLFW_DEPTH_BITS, 0);
            ::glfwWindowHint(GLFW_STENCIL_BITS, 0);
            ::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

            g_Window = ::glfwCreateWindow(800, 600, "V5C2 " V5C2_VERSION, nullptr, nullptr);
            if (g_Window == nullptr)
            {
                throw std::runtime_error("Engine :  GLFW :  Could not create window");
            }

            {
                const char* Path{ "images/V5c2Icon.png" };
                int Width{}, Height{}, Channels{ 4 };
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

                ::glfwSetWindowIcon(g_Window, 1, &Icon);

                ::stbi_image_free(Pixels);
            }

            ::glfwMakeContextCurrent(g_Window);

            if (!::gladLoadGLLoader(reinterpret_cast<GLADloadproc>(::glfwGetProcAddress)))
            {
                throw std::runtime_error("Engine :  OpenGL :  Could not initialize context");
            }

            ::glfwSwapInterval(1);
        }
        catch (...)
        {
            ::glfwTerminate();

            throw;
        }
    }


    void Engine::Finalize()
    {
        g_PendingState.reset();
        g_CurrentState.reset();

        ::glfwTerminate();
    }


    void Engine::GetCursorPosition(double& X, double& Y)
    {
        ::glfwGetCursorPos(g_Window, &X, &Y);
    }


    void Engine::SetCursorPosition(double& X, double& Y)
    {
        ::glfwSetCursorPos(g_Window, X, Y);
    }


    bool Engine::GetRunning()
    {
        return g_Running;
    }


    void Engine::SetRunning(bool Running)
    {
        g_Running = Running;
    }


    void Engine::SetState(StatePtr&& NewState)
    {
        g_PendingState = std::move(NewState);
    }


    void Engine::Mainloop()
    {
        while (g_Running && !::glfwWindowShouldClose(g_Window))
        {
            if (g_PendingState)
            {
                g_CurrentState = std::move(g_PendingState);
            }

            ::glfwPollEvents();

            g_CurrentState->HandleUpdate(1.0 / 60.0);

            g_CurrentState->HandleDraw();

            ::glfwSwapBuffers(g_Window);

            utils::Sleep(1000 / 60);
        }
    }

}
