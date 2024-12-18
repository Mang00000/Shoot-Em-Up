#include "PauseMenu.h"
#include "Debug.h"
#include <SFML/Graphics.hpp>

PauseMenu::PauseMenu(sf::RenderWindow* window)
{
    // Taille de l'écran
    float windowWidth = static_cast<float>(window->getSize().x);
    float windowHeight = static_cast<float>(window->getSize().y);
    
    float containerWidth = windowWidth / 4.f;
    float containerHeight = windowHeight / 2.f;
    
    float containerX = (windowWidth - containerWidth) / 2.f;
    float containerY = (windowHeight - containerHeight) / 2.f;

    // Dessiner le conteneur
    Debug::DrawFilledRectangle(containerX, containerY,containerWidth, containerHeight,sf::Color(255, 255, 255, 255)); 

    // Créer un bouton (rectangle)
    sf::RectangleShape button(sf::Vector2f(100, 50)); // Taille du bouton
    button.setPosition(350, 275);                    // Position dans la fenêtre
    button.setFillColor(sf::Color::Blue);            // Couleur du bouton

    // Détecter un clic sur le bouton
    /*if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) { // Clic gauche
            sf::Vector2i mousePos = sf::Mouse::getPosition(window); // Position de la souris
            if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                // Basculer le son
                if (sound.getStatus() == sf::Sound::Playing) {
                    sound.pause(); // Arrête le son
                }
                else {
                    sound.play(); // Relance le son
                }
            }
        }
    }*/
}


PauseMenu::~PauseMenu()
{

}



void PauseMenu::update()
{
   

}


	

