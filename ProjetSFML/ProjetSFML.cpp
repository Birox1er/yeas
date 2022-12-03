// ProjetSFML.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#define NOMINMAX 
#include <windows.h>
#include <math.h>
#include "Game.h"
#include "Enemy.h"
int main()
{
    std::srand(time(nullptr));
    sf::RenderWindow window(sf::VideoMode(1000, 800), "UwU : Ultra Warn Universe");
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
        while (window.pollEvent(event)) {
            // Process any input event here
            
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    std::cout << "aya";
                    PressedSpace(game, deltaTime);
                }
            }
        }
        GameUpdate(game, deltaTime);
        window.clear();
        // Whatever I want to draw goes here
        
        //window.draw(bg);
        GameDraw(game, window);
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
