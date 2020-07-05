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


#ifndef V5C2_PIECE_H
#define V5C2_PIECE_H 1

enum class PieceColor
{
    White,
    Black
};

enum class PieceType
{
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
};

class Piece
{
public:

    constexpr Piece(PieceColor color, PieceType type) noexcept;

    constexpr PieceColor getColor() const noexcept;

    constexpr PieceType getType() const noexcept;

private:

    const PieceColor m_color;
    const PieceType m_type;
};

#include "Piece.inl"

#endif // V5C2_PIECE_H
