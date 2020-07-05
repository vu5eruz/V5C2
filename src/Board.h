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


#ifndef V5C2_BOARD_H
#define V5C2_BOARD_H 1

#include "Piece.h"

#include <SFML/Graphics.hpp>

class Board : public sf::Drawable, public sf::Transformable
{
public:

    Board();

    void movePiece(const sf::Vector2i& src, const sf::Vector2i& dst);

    void newPiece(const sf::Vector2i& at, PieceColor color, PieceType type);

    void removePiece(const sf::Vector2i& at);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Font m_boardFont{};
    sf::Texture m_piecesTexture{};
    sf::VertexBuffer m_boardLayout{sf::Quads, sf::VertexBuffer::Static};
    sf::Sprite m_piecesSprites[2][6]{};
    sf::Text m_locationsTexts[2][8]{};
    Piece* m_boardData[64]{};
};

#endif // V5C2_BOARD_H
