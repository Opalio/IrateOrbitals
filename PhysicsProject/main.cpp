#include "SFML/Graphics.hpp"
#include "box2d\box2D.h"

#include "Level.h"
#include "CLevel.h"

#include <iostream>

int main()
{
    const double SCALE = 30.0;
    //window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Angry Goons!");
    window.setFramerateLimit(60);

    CLevel* level = new CLevel(SCALE);

    while (window.isOpen())
    {
        window.clear(sf::Color(97, 136, 235));


        // Poll Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            switch (event.type)
            {
            case sf::Event::MouseButtonPressed:
            {
                level->MouseButtonPressed(window);
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                level->MouseButtonReleased(SCALE);
                break;
            }
            case sf::Event::MouseMoved:
            {
                level->MouseMoved(window);
                break;
            }
            }
        }


        level->Update();
        level->Render(window, SCALE);

        window.display();
    }

    return 0;
}

//int main()
//{
//    const double SCALE = 30.0;
//    //window
//    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Angry Goons!");
//    window.setFramerateLimit(60);
//
//    Level* level = new Level(SCALE);
//
//    while (window.isOpen())
//    {
//        window.clear(sf::Color(97, 136, 235));
//
//
//        // Poll Events
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//
//            switch (event.type)
//            {
//            case sf::Event::MouseButtonPressed:
//            {
//                level->MouseButtonPressed(window);
//                break;
//            }
//            case sf::Event::MouseButtonReleased:
//            {
//                level->MouseButtonReleased(SCALE);
//                break;
//            }
//            case sf::Event::MouseMoved:
//            {
//                level->MouseMoved(window);
//                break;
//            }
//            }
//        }
//
//
//        level->Update();
//        level->Render(window, SCALE);
//
//        window.display();
//    }
//
//    return 0;
//}