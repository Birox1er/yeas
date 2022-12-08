#define NOMINMAX 
#include <windows.h>
#include <math.h>
#include "Game.h"
#include "Enemy.h"
#include "MainMenu.h"

/*sf::Sprite Fractale(int iterations, sf::RenderWindow& window)
{
    const unsigned numPixel = 800 * 1000;
    sf::Image image;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Uint8 pixels[4 * numPixel];
    for (int i = 0; i < window.getSize().x; i++) {
        for (int j = 0; j < window.getSize().y; j++) {
            float cR = (j * 2.7f) / window.getSize().x - 2.1f;// on définit un cadre dans le quel on va voir notre fonction
            float cI = (i * 2.4f) / window.getSize().y - 1.2f;
            float zR = 0;
            float zI = 0;
            int k = 0;
            do
            {
                double backup = zR;
                zR = (zR * zR) - (zI * zI) + cR;
                zI = 2 * zI * backup + cI;
                k++;
            } while (((zI * zI) + (zR * zR) < 4) && (k < iterations));
                int g = k *255 / iterations;
                int l = i + j * 4;
            if (k == iterations)
            {
                 pixels[l] = 100;
                 pixels[l+1] = 0;
                 pixels[l+2] = 255;
                 pixels[l + 3] = 255;
            }
            else {
                pixels[l] = 0;
                pixels[l + 1] = g;
                pixels[l + 2] = 0;
                pixels[l + 3] = 255;
            }                
        }
    }
    image.create(window.getSize().x, window.getSize().y, pixels);
    texture.loadFromImage(image);
    sprite.setTexture(texture, false);
    return sprite;
}*/

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
    mainMenu.MoveDown();
    while (MENU.isOpen()) {
        sf::Event event;
        while (MENU.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                MENU.close();
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                    mainMenu.MoveUp();
                    std::cout << "Up" << std::endl;
                    break;
                }

                if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                    mainMenu.MoveDown();
                    std::cout << "Down" << std::endl;
                    break;
                }

                if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space) {
                    sf::RenderWindow window(sf::VideoMode(WindowsX, WindowsY), "UwU : Ultra Warn Universe");
                    sf::RenderWindow Options(sf::VideoMode(WindowsX, WindowsY), "Options");

                    int x = mainMenu.MainMenuPressed();
                    if (x == 0) {
                        sf::Clock mainClock;
                        float deltaTime;
                        Game game;
                        int score;
                        InitGame(game, { window.getSize().x * 0.5f,window.getSize().y * 0.5f }, (sf::Vector2f)window.getSize());
                        //sf::Sprite background = Fractale( 100, window);
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
                                    std::cout << "score : " << game.score << std::endl;
                                    window.close();
                                }
                                if (event.type == sf::Event::KeyPressed) {
                                    if (event.key.code == sf::Keyboard::Escape) {
                                        window.close();
                                        std::cout <<"score : "<< game.score << std::endl;
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
                            //window.draw(background);
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
