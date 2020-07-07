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
#include <utility>

struct GLFWwindow;

namespace v5c2
{

    class State;

    class Engine
    {

        static void Initialize();

        static void Uninitialize();

    public:

        struct InitManager
        {

            inline InitManager() { Engine::Initialize(); }

            inline ~InitManager() { Engine::Uninitialize(); }

        };

        static void Mainloop();

        static inline void SetState(std::unique_ptr<State>&& NewState)
        {
            if (g_CurrentState)
            {
                g_PendingState = std::move(NewState);
            }
            else
            {
                g_CurrentState = std::move(NewState);
            }
        }

        static inline std::unique_ptr<State>&& GetState()
        {
            return std::move(g_CurrentState);
        }

    private:

        static GLFWwindow* g_Window;
        static std::unique_ptr<State> g_CurrentState;
        static std::unique_ptr<State> g_PendingState;
    };

}

#endif // !V5C2_ENGINE_H
