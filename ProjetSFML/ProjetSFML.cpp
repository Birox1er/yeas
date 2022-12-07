#define NOMINMAX 
#include <windows.h>
#include <math.h>
#include "Game.h"
#include "Enemy.h"
#include "MainMenu.h"
int main()
{
    int WindowsX = 1000;
    int WindowsY = 800;
#pragma region MENU
    /*start :
    int rep = 0;
    std::cout << "UwU : Ultra Warm Universe !\n\n 1 : Jouer \n 2 : Option \n 3 : Quitter \n\n";
    std::cout << "Reponse : ";
    std::cin >> rep;
    if (rep == 1) {
        std::cout << "START !";
    }
    else if (rep == 2) {
        int rep2 = 0;
        std::cout << "\nOPTION\n\n 1 : Retour \n 2 : Window Size \n";
        std::cin >> rep2;
        if (rep2 == 1) {
            goto start;
        }
        else if (rep2 == 2) {
            std::cout << "Default : 1000x 800y\n";
            std::cout << "Windows X :";
            std::cin >> WindowsX;
            std::cout << "Windows Y :";
            std::cin >> WindowsY;
            goto start;
        }

    }
    else if (rep == 3) {
        return 0;
    }*/
#pragma endregion 
    sf::RenderWindow MENU(sf::VideoMode(WindowsX, WindowsY), "UwU : Ultra Warn Universe - Menu");
    MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);

    while (MENU.isOpen()) {
        sf::Event event;
        while (MENU.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                MENU.close();
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up) {
                    mainMenu.MoveUp();
                    std::cout << "Up" << std::endl;
                    break;
                }

                if (event.key.code == sf::Keyboard::Down) {
                    mainMenu.MoveDown();
                    std::cout << "Down" << std::endl;
                    break;
                }

                if (event.key.code == sf::Keyboard::Enter) {
                    sf::RenderWindow window(sf::VideoMode(WindowsX, WindowsY), "UwU : Ultra Warn Universe");
                    sf::RenderWindow Options(sf::VideoMode(WindowsX, WindowsY), "Options");

                    int x = mainMenu.MainMenuPressed();
                    if (x == 0) {
                        sf::Clock mainClock;
                        float deltaTime;
                        Game game;
                        int score;
                        InitGame(game, { window.getSize().x * 0.5f,window.getSize().y * 0.5f }, (sf::Vector2f)window.getSize());
                        ///FOREGROUND CATHODIC TV
                        sf::Texture bgtext;
                        bgtext.loadFromFile("Sprites/Effects.png");
                        sf::Sprite bg;
                        bg.setTexture(bgtext);
                        while (window.isOpen()) {
                            sf::Event event;
                            deltaTime = mainClock.restart().asSeconds();
                            while (window.pollEvent(event)) {
                                // Process any input event here

                                if (event.type == sf::Event::Closed) {
                                    window.close();
                                }
                                if (event.type == sf::Event::KeyPressed) {
                                    if (event.key.code == sf::Keyboard::Escape) {
                                        window.close();
                                        MENU.display();
                                    }
                                    if (event.key.code == sf::Keyboard::Space) {
                                        //std::cout << "ayayo";
                                        PressedSpace(game, deltaTime);
                                    }
                                    if (event.key.code == sf::Keyboard::E) {
                                        PressedE(game);
                                    }
                                }
                            }

                            Options.close();
                            GameUpdate(game, deltaTime);
                            window.clear();

                            window.draw(bg);
                            GameDraw(game, window);

                            window.display();
                        }
                    }

                    if (x == 1) {
                        while (Options.isOpen()) {
                            sf::Event event2;
                            while (Options.pollEvent(event2)) {
                                if (event2.type == sf::Event::Closed) {
                                    Options.close();
                                }
                                if (event2.type == sf::Event::KeyPressed) {
                                    if (event2.key.code == sf::Keyboard::Escape) {
                                        Options.close();
                                        MENU.display();
                                    }
                                }
                            }
                            window.close();
                            Options.clear();

                            Options.display();
                        }
                    }

                    if (x == 2) {
                        MENU.close();
                    }
                    break;
                }
            }
        
        }
        MENU.clear();
        mainMenu.draw(MENU);
        MENU.display();
    }

//    std::srand(time(nullptr));
//    sf::RenderWindow window(sf::VideoMode(WindowsX, WindowsY), "UwU : Ultra Warn Universe - Game");
//    // Initialise everything below
//    sf::Clock mainClock;
//    float deltaTime;
//    Game game;
//    int score;
//    InitGame(game, { window.getSize().x * 0.5f,window.getSize().y * 0.5f }, (sf::Vector2f)window.getSize());
//    #pragma region MyRegion
//    ///FOREGROUND CATHODIC TV
//    sf::Texture bgtext;
//    bgtext.loadFromFile("Sprites/Effects.png");
//    sf::Sprite bg;
//    bg.setTexture(bgtext);
//#pragma endregion Background
    // Game loop
    //while (window.isOpen()) {
    //    sf::Event event;
    //    deltaTime = mainClock.restart().asSeconds();
    //    while (window.pollEvent(event)) {
    //        // Process any input event here

    //        if (event.type == sf::Event::Closed) {
    //            window.close();
    //        }
    //        if (event.type == sf::Event::KeyPressed) {
    //            if (event.key.code == sf::Keyboard::Space) {
    //                //std::cout << "ayayo";
    //                PressedSpace(game, deltaTime);
    //            }
    //            if (event.key.code == sf::Keyboard::E) {
    //                PressedE(game);
    //            }
    //        }
    //    }
    //    GameUpdate(game, deltaTime);
    //    window.clear();

    //    window.draw(bg);
    //    GameDraw(game, window);

    //    window.display();
    //}
    //goto start;
    //I'll try Save Here 
}
// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
