// ProjetSFML.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#define NOMINMAX 
#include <windows.h>
#include <iostream>
#include <math.h>
#include "Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "GEO");
    // Initialise everything below
    //player.triangle = sf::CircleShape (30,3);
    sf::Clock mainClock;
    float deltaTime;
   
    #pragma region InitPLAYER
    Player player;
    player.texture.loadFromFile("../Sprites/Player.png");
    if (!player.texture.loadFromFile("../Sprites/Player.png")) {
        std::cout << "failed to load Texture" << std::endl;
        return 0;
    }
    player.sprite.setTexture(player.texture);
    player.sprite.setOrigin(player.texture.getSize().x/2, player.texture.getSize().y / 2);
    
    //Set pos to middle screen
    player.sprite.setPosition(1111 / 2, 811 / 2);
    //oui elle est grande l'image
    player.sprite.setScale(.2f, .2f);
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
            player.sprite.setRotation(player.sprite.getRotation() - player.rotateSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            //printf("Rotate left \n");
            player.sprite.setRotation(player.sprite.getRotation() + player.rotateSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            //printf("Move Forward \n");
            RecalculateAngles(player);
            sf::Vector2f pos = player.sprite.getPosition();
            player.sprite.setPosition(pos.x + player.dir.x * 20 * deltaTime, pos.y + player.dir.y * 20 * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            //printf("Move Backward \n");
            RecalculateAngles(player);
            sf::Vector2f pos = player.sprite.getPosition();
            player.sprite.setPosition(pos.x - player.dir.x * 20 * deltaTime, pos.y - player.dir.y * 20 * deltaTime);
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
        
        window.draw(player.sprite);
        window.draw(bg);

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
