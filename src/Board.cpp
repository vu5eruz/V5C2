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


#include "Piece.h"
#include "Board.h"

#include <SFML/Graphics.hpp>

#include <cstddef>
#include <stdexcept>
#include <vector>


Board::Board()
{
    if (!m_boardFont.loadFromFile("fonts/DejaVuSans.ttf"))
    {
        throw std::runtime_error("Could not open file fonts/DejaVuSans.ttf");
    }

    if (!m_piecesTexture.loadFromFile("images/ChessPieces.png"))
    {
        throw std::runtime_error("Could not open file images/ChessPieces.png");
    }

    std::vector<sf::Vertex> vertices{};
    vertices.reserve(4 * 64);

    sf::Color whiteColor{238, 238, 238};
    sf::Color blackColor{98, 111, 98};

    for (int y{}; y < 8; y++)
    {
        for (int x{}; x < 8; x++)
        {
            constexpr float zero{ 0.0f };
            constexpr float size{ 50.0f };

            const sf::Vector2f squarePos{ x * size, y * size };
            const auto& squareColor{ ((x + y) % 2) ? whiteColor : blackColor  };

            vertices.emplace_back(sf::Vertex(squarePos + sf::Vector2f(zero, zero), squareColor));
            vertices.emplace_back(sf::Vertex(squarePos + sf::Vector2f(size, zero), squareColor));
            vertices.emplace_back(sf::Vertex(squarePos + sf::Vector2f(size, size), squareColor));
            vertices.emplace_back(sf::Vertex(squarePos + sf::Vector2f(zero, size), squareColor));
        }
    }

    if (!m_boardLayout.create(4 * 64) || !m_boardLayout.update(vertices.data()))
    {
        throw std::runtime_error("Not enough video memory");
    }

    m_piecesSprites[int(PieceColor::White)][int(PieceType::King)] = sf::Sprite(m_piecesTexture, { 0, 0, 24, 24 });
    m_piecesSprites[int(PieceColor::White)][int(PieceType::Queen)] = sf::Sprite(m_piecesTexture, { 24 * 1, 0, 24, 24 });
    m_piecesSprites[int(PieceColor::White)][int(PieceType::Bishop)] = sf::Sprite(m_piecesTexture, { 24 * 2, 0, 24, 24 });
    m_piecesSprites[int(PieceColor::White)][int(PieceType::Knight)] = sf::Sprite(m_piecesTexture, { 24 * 3, 0, 24, 24 });
    m_piecesSprites[int(PieceColor::White)][int(PieceType::Rook)] = sf::Sprite(m_piecesTexture, { 24 * 4, 0, 24, 24 });
    m_piecesSprites[int(PieceColor::White)][int(PieceType::Pawn)] = sf::Sprite(m_piecesTexture, { 24 * 5, 0, 24, 24 });

    m_piecesSprites[int(PieceColor::Black)][int(PieceType::King)] = sf::Sprite(m_piecesTexture, { 0, 24, 24, 24 });
    m_piecesSprites[int(PieceColor::Black)][int(PieceType::Queen)] = sf::Sprite(m_piecesTexture, { 24 * 1, 24, 24, 24 });
    m_piecesSprites[int(PieceColor::Black)][int(PieceType::Bishop)] = sf::Sprite(m_piecesTexture, { 24 * 2, 24, 24, 24 });
    m_piecesSprites[int(PieceColor::Black)][int(PieceType::Knight)] = sf::Sprite(m_piecesTexture, { 24 * 3, 24, 24, 24 });
    m_piecesSprites[int(PieceColor::Black)][int(PieceType::Rook)] = sf::Sprite(m_piecesTexture, { 24 * 4, 24, 24, 24 });
    m_piecesSprites[int(PieceColor::Black)][int(PieceType::Pawn)] = sf::Sprite(m_piecesTexture, { 24 * 5, 24, 24, 24 });

    for (auto& row : m_piecesSprites)
    {
        for (auto& piece : row)
        {
            piece.setOrigin(12.0f, 12.0f);
            piece.setScale(2.0f, 2.0f);
        }
    }

    const char* letters{ "87654321abcdefgh" };
    for (auto& row : m_locationsTexts)
    {
        for (auto& text : row)
        {
            const char str[2] = { *letters++, '\0' };

            text.setFont(m_boardFont);
            text.setCharacterSize(24);
            text.setString(str);

            // auto bounds{ text.getLocalBounds() };
            // text.setOrigin(bounds.width / 2, bounds.height / 2);
        }
    }

    newPiece(/* a8 */{ 0, 0 }, PieceColor::Black, PieceType::Rook);
    newPiece(/* b8 */{ 1, 0 }, PieceColor::Black, PieceType::Knight);
    newPiece(/* c8 */{ 2, 0 }, PieceColor::Black, PieceType::Bishop);
    newPiece(/* d8 */{ 3, 0 }, PieceColor::Black, PieceType::Queen);
    newPiece(/* e8 */{ 4, 0 }, PieceColor::Black, PieceType::King);
    newPiece(/* f8 */{ 5, 0 }, PieceColor::Black, PieceType::Bishop);
    newPiece(/* g8 */{ 6, 0 }, PieceColor::Black, PieceType::Knight);
    newPiece(/* h8 */{ 7, 0 }, PieceColor::Black, PieceType::Rook);
    newPiece(/* a7 */{ 0, 1 }, PieceColor::Black, PieceType::Pawn);
    newPiece(/* b7 */{ 1, 1 }, PieceColor::Black, PieceType::Pawn);
    newPiece(/* c7 */{ 2, 1 }, PieceColor::Black, PieceType::Pawn);
    newPiece(/* d7 */{ 3, 1 }, PieceColor::Black, PieceType::Pawn);
    newPiece(/* e7 */{ 4, 1 }, PieceColor::Black, PieceType::Pawn);
    newPiece(/* f7 */{ 5, 1 }, PieceColor::Black, PieceType::Pawn);
    newPiece(/* g7 */{ 6, 1 }, PieceColor::Black, PieceType::Pawn);
    newPiece(/* h7 */{ 7, 1 }, PieceColor::Black, PieceType::Pawn);

    newPiece(/* a1 */{ 0, 7 }, PieceColor::White, PieceType::Rook);
    newPiece(/* b1 */{ 1, 7 }, PieceColor::White, PieceType::Knight);
    newPiece(/* c1 */{ 2, 7 }, PieceColor::White, PieceType::Bishop);
    newPiece(/* d1 */{ 3, 7 }, PieceColor::White, PieceType::Queen);
    newPiece(/* e1 */{ 4, 7 }, PieceColor::White, PieceType::King);
    newPiece(/* f1 */{ 5, 7 }, PieceColor::White, PieceType::Bishop);
    newPiece(/* g1 */{ 6, 7 }, PieceColor::White, PieceType::Knight);
    newPiece(/* h1 */{ 7, 7 }, PieceColor::White, PieceType::Rook);
    newPiece(/* a2 */{ 0, 6 }, PieceColor::White, PieceType::Pawn);
    newPiece(/* b2 */{ 1, 6 }, PieceColor::White, PieceType::Pawn);
    newPiece(/* c2 */{ 2, 6 }, PieceColor::White, PieceType::Pawn);
    newPiece(/* d2 */{ 3, 6 }, PieceColor::White, PieceType::Pawn);
    newPiece(/* e2 */{ 4, 6 }, PieceColor::White, PieceType::Pawn);
    newPiece(/* f2 */{ 5, 6 }, PieceColor::White, PieceType::Pawn);
    newPiece(/* g2 */{ 6, 6 }, PieceColor::White, PieceType::Pawn);
    newPiece(/* h2 */{ 7, 6 }, PieceColor::White, PieceType::Pawn);
}


void Board::movePiece(const sf::Vector2i& src, const sf::Vector2i& dst)
{
    delete m_boardData[dst.x + dst.y * 8];
    m_boardData[dst.x + dst.y * 8] = m_boardData[src.x + src.y * 8];
    m_boardData[src.x + src.y * 8] = nullptr;
}


void Board::newPiece(const sf::Vector2i& at, PieceColor color, PieceType type)
{
    delete m_boardData[at.x + at.y * 8];
    m_boardData[at.x + at.y * 8] = new Piece(color, type);
}


void Board::removePiece(const sf::Vector2i& at)
{
    delete m_boardData[at.x + at.y * 8];
    m_boardData[at.x + at.y * 8] = nullptr;
}


void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(m_boardLayout, states);

    states.transform.translate(25.0f, 25.0f);

    int index{};
    for (const auto& rank : m_locationsTexts[0])
    {
        auto leftRanks{ states };
        auto rightRanks{ states };

        leftRanks.transform.translate(-50.0f, 50.0f * index - 12.0f);
        rightRanks.transform.translate(50.0f * 8 - 16.0f, 50.0f * index - 12.0f);

        target.draw(rank, leftRanks);
        target.draw(rank, rightRanks);

        index++;
    }

    index = 0;
    for (const auto& file : m_locationsTexts[1])
    {
        auto upperFiles{ states };
        auto lowerFiles{ states };

        upperFiles.transform.translate(50.0f * index - 8.0f, -50.0f - 12.0f);
        lowerFiles.transform.translate(50.0f * index - 8.0f, 50.0f * 8 - 12.0f);

        target.draw(file, upperFiles);
        target.draw(file, lowerFiles);

        index++;
    }

    index = -1;    
    for (const auto* piece : m_boardData)
    {
        index++;

        if (!piece)
        {
            continue;
        }

        const int x{ index % 8 };
        const int y{ index / 8 };
        const auto& spr{ m_piecesSprites[int(piece->getColor())][int(piece->getType())] };
        auto sprStates{ states };
        sprStates.transform.translate(50.0f * x, 50.0f * y);

        target.draw(spr, sprStates);
    }
}
