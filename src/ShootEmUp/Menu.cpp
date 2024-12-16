#include "Menu.h"
#include "Debug.h"

Menu::Menu(sf::RenderWindow* window)
{
    // Taille de l'écran
    float windowWidth = static_cast<float>(window->getSize().x);
    float windowHeight = static_cast<float>(window->getSize().y);

    // Dessiner le conteneur
    Debug::DrawFilledRectangle(0, 0, windowWidth, windowHeight, sf::Color(255, 255, 255, 200));
}


Menu::~Menu()
{

}



void Menu::update()
{


}