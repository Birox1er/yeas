// ProjetSFML.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#define NOMINMAX 
#include <windows.h>
#include <math.h>
#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "GEO");
    // Initialise everything below
    //player.triangle = sf::CircleShape (30,3);
    sf::Clock mainClock;
    float deltaTime;
   
    #pragma region Initialisation
    Game game;
    InitGame(game, { window.getSize().x * 0.5f,window.getSize().y * 0.5f }, (sf::Vector2f)window.getSize());
    
    #pragma endregion


    ///FOREGROUND CATHODIC TV
    sf::Texture bgtext;
    bgtext.loadFromFile("../Sprites/Effects.png");
    sf::Sprite bg;
    bg.setTexture(bgtext);


    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        deltaTime = mainClock.restart().asSeconds();

        #pragma region Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            //printf("Rotate Right \n");
            game.player.sprite.setRotation(game.player.sprite.getRotation() - game.player.rotateSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            //printf("Rotate left \n");
            game.player.sprite.setRotation(game.player.sprite.getRotation() + game.player.rotateSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            //printf("Move Forward \n");
            game.player.wasS = false;
            game.player.wasZ = true;
            RecalculateAngles(game.player);
            sf::Vector2f pos = game.player.sprite.getPosition();

            game.player.speed += game.player.AccSpeed;

            if (game.player.speed > game.player.MaxSpeed) {
                game.player.speed = game.player.MaxSpeed;
            }
            std::cout << game.player.speed << std::endl;
            game.player.sprite.setPosition(pos.x + game.player.dir.x * game.player.speed * deltaTime, pos.y + game.player.dir.y * game.player.speed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            //printf("Move Backward \n");
            game.player.wasZ = false;
            game.player.wasS = true;
            RecalculateAngles(game.player);

            game.player.speed -= game.player.AccSpeed;

            //if (game.player.speed > game.player.MaxSpeed/3) {
            //    game.player.speed -= game.player.AccSpeed;
            //}else if (game.player.speed <= game.player.MaxSpeed/3) {
            //    game.player.speed += game.player.AccSpeed;
            //}

            if (game.player.speed < 0) {
                game.player.speed = 0;
            }
            std::cout << game.player.speed << std::endl;
            game.player.sprite.move(game.player.dir.x * -game.player.speed * deltaTime *1.5, game.player.dir.y * -game.player.speed * deltaTime * 1.5);
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::S))) {
            if (game.player.speed > 0) {
                game.player.speed -= game.player.friction;
                if (game.player.wasZ) {
                    game.player.sprite.move(game.player.dir.x * game.player.speed * deltaTime, game.player.dir.y * game.player.speed * deltaTime);
                }
                else if (game.player.wasS) {
                    game.player.sprite.move(game.player.dir.x * -game.player.speed * deltaTime, game.player.dir.y * -game.player.speed * deltaTime);
                }
                std::cout << game.player.speed << std::endl;
            }
            else if (game.player.speed < 0) {
                game.player.speed = 0;
                std::cout << game.player.speed << std::endl;

            }
        }
        #pragma endregion

        while (window.pollEvent(event)) {
            // Process any input event here
            
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        // Whatever I want to draw goes here
        
        window.draw(bg);
        window.draw(game.player.sprite);

        window.display();
    }

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
