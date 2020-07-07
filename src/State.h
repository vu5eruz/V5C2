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


#ifndef V5C2_STATE_H
#define V5C2_STATE_H 1

namespace v5c2
{

    class Event;

    class State
    {
    public:

        State() = default;

        virtual ~State() = default;

        virtual void HandleEvent(const Event& Ev);

        virtual void HandleUpdate(double Dt);

        virtual void HandleDraw() const;

    };

}

#endif // !V5C2_STATE_H
