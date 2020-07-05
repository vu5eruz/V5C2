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


#include "Board.h"
#include "Inputs.h"
#include "Main.h"

#include <SFML/Graphics.hpp>

#ifdef V5C2_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <tchar.h>
#include <wchar.h>
#include <windows.h>
#endif // V5C2_PLATFORM_WINDOWS


#include <cstddef>
#include <exception>
#include <iostream>
#include <stdexcept>


namespace
{
    void emitError(const char* message)
    {
#ifdef V5C2_PLATFORM_WINDOWS
        ::AllocConsole();

        FILE* dummy{};
        freopen_s(&dummy, "CONIN$", "r", stdin);
        freopen_s(&dummy, "CONOUT$", "w", stdout);
        freopen_s(&dummy, "CONOUT$", "w", stderr);

        std::cin.clear();
        std::cout.clear();
        std::cerr.clear();
        std::clog.clear();
#endif

        std::cerr <<
            "\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
            "\n\t" << message << "\n"
            "\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
        << std::endl;

#ifdef V5C2_PLATFORM_WINDOWS
        std::system("pause");

        ::FreeConsole();
#endif
    }


    template <typename T>
    void setOriginAtCenter(T& obj)
    {
        auto objBounds{obj.getLocalBounds()};

        obj.setOrigin(objBounds.width / 2, objBounds.height / 2);
    }
}


class Game : public sf::Drawable
{
    enum class State
    {
        IntroFadeIn,
        IntroHold,
        IntroFadeOut,
        EditorFadeIn,
        Editor
    };

public:

    Game()
    {
        const sf::VideoMode videoMode{800, 600};
        const sf::String title{"V5C2 " V5C2_VERSION};
        const sf::Uint32 style{sf::Style::Titlebar | sf::Style::Close};
        const sf::ContextSettings context{0, 0, 1, 2, 1};

        m_window.create(videoMode, title, style, context);
        m_window.setFramerateLimit(60);
        m_window.setVerticalSyncEnabled(true);

        if (!m_logoTexture.loadFromFile("images/V5c2Logo.png"))
        {
            throw std::runtime_error("Could not open file images/V5c2Logo.png");
        }

        m_logoTexture.setSmooth(true);

        m_logo.setTexture(m_logoTexture);
        setOriginAtCenter(m_logo);
        m_logo.setPosition(400.0f, 300.0f);
        m_logo.setScale(64.0f / 512.0f, 64.0f / 512.0f);
    }

    void run()
    {
        while (m_window.isOpen())
        {
            for (sf::Event event{}; m_window.pollEvent(event); )
            {
                handleEvent(event);
            }

            handleUpdate(sf::milliseconds(1000 / 60));

            m_window.draw(*this);
            m_window.display();
        }
    }

private:

    void handleEvent(const sf::Event& event)
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                m_window.close();
                break;

            case sf::Event::KeyPressed:
                m_inputs.handle(event.key);
                break;

            default:
                break;
        }
    }

    void handleUpdate(sf::Time dt)
    {
        m_timer += dt;

        switch (m_state)
        {
            case State::IntroFadeIn:
            {
                if (m_timer >= sf::milliseconds(800))
                {
                    m_timer = sf::Time::Zero;
                    m_state = State::IntroHold;
                    break;
                }

                auto alpha{m_timer.asMilliseconds() * 255 / 800};
                m_logo.setColor(sf::Color(0xFFFFFF00 | alpha));
                break;
            }

            case State::IntroHold:
            {
                if (m_timer >= sf::milliseconds(500))
                {
                    m_timer = sf::Time::Zero;
                    m_state = State::IntroFadeOut;
                }

                m_logo.setColor(sf::Color::White);
                break;
            }

            case State::IntroFadeOut:
            {
                if (m_timer >= sf::milliseconds(800))
                {
                    m_timer = sf::Time::Zero;
                    m_state = State::EditorFadeIn;
                    break;
                }

                auto alpha{ m_timer.asMilliseconds() * 255 / 800 };
                m_logo.setColor(sf::Color(0xFFFFFFFF - alpha));
                break;
            }

            case State::EditorFadeIn:
            {
                if (m_timer >= sf::milliseconds(1200))
                {
                    m_timer = sf::Time::Zero;
                    m_state = State::Editor;
                    m_inputs.setEnable(true);
                    break;
                }

                auto component{ static_cast<sf::Uint8>(m_timer.asMilliseconds() * (47 - 12) / 1200) };
                m_backgroundColor = sf::Color(12 + component, 12 + component, 12 + component);
                break;
            }

            case State::Editor:
            {
                m_inputs.update();

                switch (Command cmd{}; m_inputs.accept(cmd))
                {
                    case Command::MovePiece:
                        m_board.movePiece(cmd.movePiece.src, cmd.movePiece.dst);
                        break;

                    case Command::NewPiece:
                        m_board.newPiece(cmd.newPiece.at, cmd.newPiece.color, cmd.newPiece.type);
                        break;

                    case Command::RemovePiece:
                        m_board.removePiece(cmd.removePiece.at);
                        break;

                    default:
                        break;
                }
                break;
            }
        }
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.clear(m_backgroundColor);

        switch (m_state)
        {
            case State::IntroFadeIn:
            case State::IntroHold:
            case State::IntroFadeOut:
            {
                target.draw(m_logo, states);
                break;
            }

            case State::EditorFadeIn:
            case State::Editor:
            {
                auto boardStates{ states };
                boardStates.transform.translate(32.0f, 96.0f);
                target.draw(m_board, boardStates);

                auto inputsStates{ states };
                inputsStates.transform.translate(512.0f - 16.0f, 8.0f);
                target.draw(m_inputs, inputsStates);
                break;
            }
        }
    }

    State m_state{};
    sf::RenderWindow m_window{};
    sf::Time m_timer{};
    sf::Color m_backgroundColor{12, 12, 12};
    sf::Texture m_logoTexture{};
    sf::Sprite m_logo{};
    Board m_board{};
    Inputs m_inputs{};
};


int main()
{
    int status{EXIT_SUCCESS};

    try
    {
        Game game{};
        game.run();
    }
    catch (const std::exception& exc)
    {
        status = EXIT_FAILURE;

        emitError(exc.what());
    }

    return status;
}
