#include "PauseMenu.h"
#include "Debug.h"

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
}


PauseMenu::~PauseMenu()
{

}



void PauseMenu::update()
{


}


	

