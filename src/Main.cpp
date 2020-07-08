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

#include <SFML/Graphics.hpp>


namespace v5c2
{
    
    void Main()
    {
        sf::RenderWindow window{sf::VideoMode(800, 600), "V5C2"};

        sf::Texture logoTexture{};
        if (!logoTexture.loadFromFile("images/V5c2Logo.png"))
        {
            return;
        }
        
        sf::Sprite logo{logoTexture};
        
        while (window.isOpen())
        {
            sf::Event event{};
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    
                    default:
                        break;
                }
            }
            
            window.clear();
            window.draw(logo);
            window.display();
        }
    }
    
}


int main()
{
    v5c2::Main();
    
    return 0;
}
