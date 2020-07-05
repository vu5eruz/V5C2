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


#include "Inputs.h"

#include <cstdio>
#include <string>
#include <string_view>
#include <vector>


namespace
{
    std::string promptForNewCommand(const std::string_view& str, bool& commandValid, PieceColor& color, PieceType& type)
    {
        std::string prompt{};
        const char* colorStr = "<color>";
        const char* typeStr = "<piece>";
        char c1{ '#' }, c2{ '#' };

        switch (str.length())
        {
            case 5:
                if ((str[4] < '1') || (str[4] > '8'))
                {
                    return "<invalid rank>";
                }
                c2 = str[4];
                [[fallthrough]];

            case 4:
                if ((str[3] < 'a') || (str[3] > 'h'))
                {
                    return "<invalid file>";
                }
                c1 = str[3];
                [[fallthrough]];

            case 3:
                switch (str[2])
                {
                    case 'k':
                        typeStr = "king";
                        type = PieceType::King;
                        break;

                    case 'q':
                        typeStr = "queen";
                        type = PieceType::Queen;
                        break;

                    case 'r':
                        typeStr = "rook";
                        type = PieceType::Rook;
                        break;

                    case 'b':
                        typeStr = "bishop";
                        type = PieceType::Bishop;
                        break;

                    case 'n':
                        typeStr = "knight";
                        type = PieceType::Knight;
                        break;

                    case 'p':
                        typeStr = "Pawn";
                        type = PieceType::Pawn;
                        break;

                    default:
                        return "<invalid piece>";
                }
                [[fallthrough]];

            case 2:
                switch (str[1])
                {
                    case 'w':
                        colorStr = "white";
                        color = PieceColor::White;
                        break;

                    case 'b':
                        colorStr = "black";
                        color = PieceColor::Black;
                        break;

                    default:
                        return "<invalid color>";
                }
                break;
        }

        prompt.resize(64);
        int ret{ std::snprintf(prompt.data(), prompt.size(), "create new %s %s at %c%c", colorStr, typeStr, c1, c2) };
        prompt.erase(ret, std::string::npos);
        commandValid = str.length() == 5;
        return prompt;
    }

    std::string promptForMoveCommand(const std::string_view& str, bool& commandValid)
    {
        std::string prompt{};
        char c1{'#'}, c2{ '#' }, c3{ '#' }, c4{ '#' };

        switch (str.length())
        {
            case 5:
                if ((str[4] < '1') || (str[4] > '8'))
                {
                    return "<invalid rank>";
                }
                c4 = str[4];
                [[fallthrough]];

            case 4:
                if ((str[3] < 'a') || (str[3] > 'h'))
                {
                    return "<invalid file>";
                }
                c3 = str[3];
                [[fallthrough]];

            case 3:
                if ((str[2] < '1') || (str[2] > '8'))
                {
                    return "<invalid rank>";
                }
                c2 = str[2];
                [[fallthrough]];

            case 2:
                if ((str[1] < 'a') || (str[1] > 'h'))
                {
                    return "<invalid file>";
                }
                c1 = str[1];
                break;
        }

        prompt.resize(64);
        int ret{ std::snprintf(prompt.data(), prompt.size(), "move piece from %c%c to %c%c", c1, c2, c3, c4) };
        prompt.erase(ret, std::string::npos);
        commandValid = str.length() == 5;
        return prompt;
    }

    std::string promptForRemoveCommand(const std::string_view& str, bool& commandValid)
    {
        std::string prompt{};
        char c1{ '#' }, c2{ '#' };


        switch (str.length())
        {
            case 3:
                if ((str[2] < '1') || (str[2] > '8'))
                {
                    return "<invalid rank>";
                }
                c2 = str[2];
                [[fallthrough]];

            case 2:
                if ((str[1] < 'a') || (str[1] > 'h'))
                {
                    return "<invalid file>";
                }
                c1 = str[1];
                break;
        }

        prompt.resize(64);
        int ret{ std::snprintf(prompt.data(), prompt.size(), "remove piece at %c%c", c1, c2) };
        prompt.erase(ret, std::string::npos);
        commandValid = str.length() == 3;
        return prompt;
    }
}


Inputs::Inputs()
{
    if (!m_editorFont.loadFromFile("fonts/DejaVuSansCondensed.ttf"))
    {
        throw std::runtime_error("Could not open file fonts/DejaVuSansCondensed.ttf");
    }

    m_editorCaret.setFont(m_editorFont);
    m_editorCaret.setCharacterSize(16);
    m_editorCaret.setString(">");

    m_editorPrompt.setFont(m_editorFont);
    m_editorPrompt.setCharacterSize(16);
    m_editorPrompt.setFillColor(sf::Color(248, 248, 248));

    m_editorText.setFont(m_editorFont);
    m_editorText.setCharacterSize(16);
    m_editorText.setString("");
}


void Inputs::handle(const sf::Event::KeyEvent& key)
{
    bool doCommand{false};
    bool commandValid{false};

    if ((key.code == sf::Keyboard::Backspace) && !m_editorString.empty())
    {
        m_editorString.pop_back();
        m_dirty = true;
    }
    else if ((key.code >= sf::Keyboard::A) && (key.code <= sf::Keyboard::Z))
    {
        m_editorString += char(int(key.code) - int(sf::Keyboard::A) + 'a');
        m_dirty = true;
    }
    else if ((key.code >= sf::Keyboard::Num0) && (key.code <= sf::Keyboard::Num9))
    {
        m_editorString += char(int(key.code) - int(sf::Keyboard::Num0) + '0');
        m_dirty = true;
    }
    else if (key.code == sf::Keyboard::Enter)
    {
        doCommand = true;
        m_dirty = true;
    }

    if (m_editorString.empty())
    {
        m_editorPrompt.setString("");
        return;
    }

    std::string prompt{};
    switch (m_editorString[0])
    {
        case 'c':
        {
            PieceColor color{};
            PieceType type{};
            prompt = promptForNewCommand(m_editorString, commandValid, color, type);
            if (doCommand && commandValid)
            {
                m_cmdType = Command::NewPiece;
                m_cmd.newPiece.at.x = m_editorString[3] - 'a';
                m_cmd.newPiece.at.y = 7 - (m_editorString[4] - '1');
                m_cmd.newPiece.color = color;
                m_cmd.newPiece.type = type;
                prompt = "";
                m_editorString = "";
            }
            break;
        }

        case 'm':
            prompt = promptForMoveCommand(m_editorString, commandValid);
            if (doCommand && commandValid)
            {
                m_cmdType = Command::MovePiece;
                m_cmd.movePiece.src.x = m_editorString[1] - 'a';
                m_cmd.movePiece.src.y = 7 - (m_editorString[2] - '1');
                m_cmd.movePiece.dst.x = m_editorString[3] - 'a';
                m_cmd.movePiece.dst.y = 7 - (m_editorString[4] - '1');
                prompt = "";
                m_editorString = "";
            }
            break;

        case 'r':
            prompt = promptForRemoveCommand(m_editorString, commandValid);
            if (doCommand && commandValid)
            {
                m_cmdType = Command::RemovePiece;
                m_cmd.removePiece.at.x = m_editorString[1] - 'a';
                m_cmd.removePiece.at.y = 7 - (m_editorString[2] - '1');
                prompt = "";
                m_editorString = "";
            }
            break;

        default:
            prompt = "<invalid command>";
            break;
    }

    m_editorPrompt.setString(prompt);
}


void Inputs::update()
{
    if (m_dirty)
    {
        m_editorText.setString(m_editorString);
        m_dirty = false;
    }
}


Command::CommandType Inputs::accept(Command& cmd)
{
    if (m_cmdType == Command::None)
    {
        return Command::None;
    }

    auto cmdType{m_cmdType};
    m_cmdType = Command::None;

    cmd = m_cmd;
    return cmdType;
}


void Inputs::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(m_editorCaret, states);

    states.transform.translate(16.0f, 0.0f);
    target.draw(m_editorText, states);

    states.transform.translate(0.0f, 20.0f);
    target.draw(m_editorPrompt, states);
}
