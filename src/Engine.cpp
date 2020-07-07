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
#include "State.h"

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <memory>
#include <utility>


namespace v5c2
{

    void Engine::Initialize()
    {
        ::glfwInit();

        ::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        ::glfwWindowHint(GLFW_DEPTH_BITS, 0);
        ::glfwWindowHint(GLFW_STENCIL_BITS, 0);
        ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

        g_Window = ::glfwCreateWindow(800, 600, "V5C2", nullptr, nullptr);
        ::glfwMakeContextCurrent(g_Window);
        ::glfwSwapInterval(1);

        ::gladLoadGLLoader(reinterpret_cast<GLADloadproc>(::glfwGetProcAddress));
    }


    void Engine::Uninitialize()
    {
        g_CurrentState.reset();
        g_PendingState.reset();

        ::glfwTerminate();
    }


    void Engine::Mainloop()
    {
        while (!::glfwWindowShouldClose(g_Window))
        {
            if (g_PendingState)
            {
                g_CurrentState = std::move(g_PendingState);
            }

            ::glfwPollEvents();

            g_CurrentState->HandleUpdate(1.0 / 60.0);

            g_CurrentState->HandleDraw();

            ::glfwSwapBuffers(g_Window);
        }
    }


    GLFWwindow* Engine::g_Window{};
    std::unique_ptr<State> Engine::g_CurrentState{};
    std::unique_ptr<State> Engine::g_PendingState{};
}
