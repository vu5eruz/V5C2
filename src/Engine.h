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


#ifndef V5C2_ENGINE_H
#define V5C2_ENGINE_H 1

#include <memory>


namespace v5c2
{

    class State;

    using StatePtr = std::unique_ptr<State>;

    class Engine
    {
        static void Initialize();

        static void Finalize();

    public:

        struct InitializerManager
        {
            inline InitializerManager()
            {
                Engine::Initialize();
            }


            inline ~InitializerManager()
            {
                Engine::Finalize();
            }
        };

        static void GetCursorPosition(double& X, double& Y);

        static void SetCursorPosition(double& X, double& Y);

        static bool GetRunning();

        static void SetRunning(bool Running);

        static void SetState(StatePtr&& NewState);

        static void Mainloop();
    };

}

#endif // !V5C2_ENGINE_H
