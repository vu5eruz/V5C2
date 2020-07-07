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
#include "Main.h"

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <memory>


namespace v5c2
{

    void Main()
    {
        ::glfwInit();
        ::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        auto* Window{ ::glfwCreateWindow(800, 600, "V5C2", nullptr, nullptr) };
        ::glfwMakeContextCurrent(Window);
        ::gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        ::glfwSwapInterval(1);

        Background Bkg{};
        Bkg.SetInnerColor(0.1850f, 0.1850f, 0.1850f);
        Bkg.SetOuterColor(0.0025f, 0.0025f, 0.0025f);
        Bkg.Realize(800, 600);

        while (!::glfwWindowShouldClose(Window))
        {
            ::glfwPollEvents();

            Bkg.Draw();

            ::glfwSwapBuffers(Window);
        }

        ::glfwTerminate();
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
        ::MessageBoxA(nullptr, Exc.what(), "V5C2 " V5C2_VERSION " Error", MB_OK | MB_ICONEXCLAMATION);
#endif

        ExitStatus = EXIT_FAILURE;
    }

    return ExitStatus;
}
