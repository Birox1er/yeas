// ProjetSFML.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#define NOMINMAX 
#include <windows.h>
#include <iostream>
#include "Player.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1111, 811), "GEO");
    // Initialise everything below
    Player player;
    player.triangle = sf::CircleShape (30,3);
    sf::Clock mainClock;
    float deltaTime;
        

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        deltaTime = mainClock.restart().asSeconds();

        //origin = radius du circle
        player.triangle.setOrigin(30,30);
        player.triangle.scale(1, 1);

        #pragma region Movement /// TAke ANGLES OUT BEFORE MOVEMENT
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            printf("Rotate left \n");
            player.triangle.setRotation(player.triangle.getRotation() - player.rotateSpeed * deltaTime);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            printf("Rotate left \n");
            player.triangle.setRotation(player.triangle.getRotation() + player.rotateSpeed * deltaTime);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            printf("Move Forward \n");
            #pragma region RecalculateAngles
                player.dir.x = 10 * sin(player.triangle.getRotation() * (3.141592653589793 / 180));
                player.dir.y = 10 * -cos(player.triangle.getRotation() * (3.141592653589793 / 180));
                //std::cout << player.dir.x << ", " << player.dir.y << std::endl;
            #pragma endregion

            sf::Vector2f pos = player.triangle.getPosition();
            player.triangle.setPosition(pos.x + player.dir.x * 10 * deltaTime, pos.y + player.dir.y * 10 * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            printf("Move Backward \n");
            #pragma region RecalculateAngles
                player.dir.x = -10 * sin(player.triangle.getRotation() * (3.141592653589793 / 180));
                player.dir.y = -10 * -cos(player.triangle.getRotation() * (3.141592653589793 / 180));
                std::cout << player.dir.x << ", " << player.dir.y << std::endl;
            #pragma endregion
            sf::Vector2f pos = player.triangle.getPosition();
            player.triangle.setPosition(pos.x + player.dir.x * 10 * deltaTime, pos.y + player.dir.y * 10 * deltaTime);
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
        
        window.draw(player.triangle);

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
