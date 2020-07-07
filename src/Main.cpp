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
#include "Engine.h"
#include "Main.h"
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

        MainState()
        {
            m_Bkg.SetInnerColor(0.1850f, 0.1850f, 0.1850f);
            m_Bkg.SetOuterColor(0.0025f, 0.0025f, 0.0025f);
            m_Bkg.Realize(800, 600);
        }


        void HandleDraw() const override
        {
            m_Bkg.Draw();
        }

    private:

        Background m_Bkg{};
    };


    void Main()
    {
        Engine::InitManager EngineIM{};

        auto StatePtr{ std::make_unique<MainState>() };

        Engine::SetState(std::move(StatePtr));
        Engine::Mainloop();
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
