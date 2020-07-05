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


#ifndef V5C2_INPUTS_H
#define V5C2_INPUTS_H 1

#include "Piece.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <string>
#include <vector>

union Command
{
    enum CommandType
    {
        None,
        MovePiece,
        NewPiece,
        RemovePiece
    };

    struct MovePieceCommand
    {
        sf::Vector2i src{};
        sf::Vector2i dst{};
    };

    struct NewPieceCommand
    {
        sf::Vector2i at{};
        PieceColor color{};
        PieceType type{};
    };

    struct RemovePieceCommand
    {
        sf::Vector2i at{};
    };

    MovePieceCommand movePiece;
    NewPieceCommand newPiece;
    RemovePieceCommand removePiece;
};

class Inputs : public sf::Drawable, public sf::Transformable
{
public:

    Inputs();

    inline void setEnable(bool enabled) { m_enabled = enabled; }

    void handle(const sf::Event::KeyEvent& key);

    void update();

    Command::CommandType accept(Command& cmd);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool m_enabled{true};
    bool m_dirty{false};
    sf::Font m_editorFont{};
    sf::Text m_editorCaret{};
    sf::Text m_editorPrompt{};
    sf::Text m_editorText{};
    std::string m_editorString{};
    Command::CommandType m_cmdType{Command::None};
    Command m_cmd{};
};

#endif // V5C2_INPUTS_H
