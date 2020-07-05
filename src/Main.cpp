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


#include "Main.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <cstdlib>


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    sf::Texture texture;
    if (!texture.loadFromFile("images/V5c2Logo.png"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);
    
    sf::Font font;
    if (!font.loadFromFile("fonts/DejaVuSans.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
 
        window.clear();
        window.draw(sprite);
        window.draw(text);
        window.display();
    }

    return EXIT_SUCCESS;
}
