#include "SFML/Graphics.hpp"
#include "box2d\box2D.h"

#include "Level.h"
#include "CLevel.h"

#include <iostream>

int main()
{
    const double SCALE = 30.0;
    //window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Irate Orbitals!");
    window.setFramerateLimit(60);

    CLevel* pLevel = new CLevel(SCALE);

    bool bGameLost = false;
    bool bLevelWon = false;

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
                bGameLost = pLevel->MouseButtonPressed(window, SCALE);
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                if (!(bGameLost || bLevelWon))
                {
                    pLevel->MouseButtonReleased(SCALE);
                }
                break;
            }
            case sf::Event::MouseMoved:
            {
                if (!(bGameLost || bLevelWon))
                {
                    pLevel->MouseMoved(window);
                }
                break;
            }
            }
        }


        bLevelWon = pLevel->Update();
        pLevel->Render(window, SCALE);

        window.display();

        if (bLevelWon)
        {
            switch (pLevel->GetCurrentLevel())
            {
            case 2:
                std::cout << std::endl;
                std::cout << "Level 1 Won - Proceeding to next level" << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
                pLevel->UnloadLevel();
                pLevel->LoadLevel2(SCALE);

                break;

            case 3:
                std::cout << std::endl;
                std::cout << "Level 2 Won - Proceeding to next level" << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
                pLevel->UnloadLevel();
                pLevel->LoadLevel3(SCALE);

                break;

            default:
                std::cout << std::endl;
                std::cout << "Game Won - Restarting" << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;

                pLevel->UnloadLevel();
                pLevel->SetCurrentLevel(1);
                pLevel->LoadLevel1(SCALE);
                break;
            }

            bLevelWon = false;
        }

        if (bGameLost)
        {
            std::cout << std::endl;
            std::cout << "Game Lost - Restarting" << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;

            pLevel->UnloadLevel();
            pLevel->SetCurrentLevel(1);
            pLevel->LoadLevel1(SCALE);

            bGameLost = false;
        }
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