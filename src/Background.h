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


#ifndef V5C2_BACKGROUND_H
#define V5C2_BACKGROUND_H 1

namespace v5c2
{

    class Background
    {
    public:

        Background();

        ~Background();

        void SetInnerColor(float R, float G, float B);

        void SetOuterColor(float R, float G, float B);

        void Realize(unsigned int Width, unsigned int Height);

        void Draw() const;

    private:

        float m_InnerColor[3]{};
        float m_OuterColor[3]{};
        float m_CenterCoord[2]{};
        unsigned int m_Vbo{};
        unsigned int m_Ibo{};
        unsigned int m_Program{};
        unsigned int m_Program_uInnerColor{};
        unsigned int m_Program_uOuterColor{};
        unsigned int m_Program_uCenterCoord{};
    };

}

#endif // !V5C2_BACKGROUND_H
