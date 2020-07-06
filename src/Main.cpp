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


#include "Main.h"

#ifdef V5C2_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <tchar.h>
#include <windows.h>
#endif // V5C2_PLATFORM_WINDOWS

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdexcept>


namespace v5c2
{

    void Main()
    {
        if (!glfwInit())
        {
            throw std::runtime_error("GLFW: Could not initialize library");
        }

        auto* Window{ glfwCreateWindow(800, 600, "V5C2", nullptr, nullptr) };
        if (!Window)
        {
            throw std::runtime_error("GLFW: Could not create window");
        }

        glfwMakeContextCurrent(Window);
        glfwSwapInterval(1);

        auto Clear{ (void(*)(std::uint32_t))(glfwGetProcAddress("glClear")) };

        while (!glfwWindowShouldClose(Window))
        {
            glfwPollEvents();

            Clear(0x00004000);

            glfwSwapBuffers(Window);
        }

        glfwTerminate();
    }

}


#ifdef V5C2_PLATFORM_WINDOWS
int APIENTRY _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
#else
int main(int, char**)
#endif
{
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
    }

    return 0;
}
