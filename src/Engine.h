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

// Dangerous forward declaration
// Anything to avoid including <GLFW/glfw3.h> here
struct GLFWwindow;

namespace v5c2
{

    class State;

    class Engine
    {
        friend class State;

    public:

        Engine();

        ~Engine();

        void Run();

        void GetCursorPosition(double& X, double& Y);

        void SetCursorPosition(double X, double Y);

        static inline Engine& GetInstance() { return *GlobalInstance; }

        static inline void SetInstance(Engine& Instance) { GlobalInstance = &Instance; }

        inline bool IsRunning() const { return m_IsRunning; }

        inline void SetRunning(bool Running) { m_IsRunning = Running; }

        void SetState(std::unique_ptr<State>&& NewState);

    private:

        void DispatchUpdates();

        void DispatchDraw();

        static void ErrorCallback(int Error, const char* Description);

        bool m_IsRunning{};
        GLFWwindow* m_Window{};
        std::unique_ptr<State> m_CurrentState{};
        std::unique_ptr<State> m_PendingState{};

        static Engine* GlobalInstance;
    };

}

#endif // !V5C2_ENGINE_H
