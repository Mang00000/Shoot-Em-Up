#include "Menu.h"
#include "Debug.h"

Menu::Menu(sf::RenderWindow* window)
{
    // Taille de l'écran
    float windowWidth = static_cast<float>(window->getSize().x);
    float windowHeight = static_cast<float>(window->getSize().y);

    // Dessiner le conteneur
    Debug::DrawFilledRectangle(0, 0, windowWidth, windowHeight, sf::Color(255, 255, 255, 255));
    Debug::DrawText(windowWidth/2-150, windowHeight/2,"Press space to start", sf::Color::Black);
}

void Menu::Vmenu(sf::RenderWindow* window)
{
    float windowWidth = static_cast<float>(window->getSize().x);
    float windowHeight = static_cast<float>(window->getSize().y);

    float containerWidth = windowWidth / 2.f;
    float containerHeight = windowHeight / 4.f;

    float containerX = (windowWidth - containerWidth) / 2.f;
    float containerY = (windowHeight - containerHeight) / 2.f;

    Debug::DrawFilledRectangle(containerX, containerY, containerWidth, containerHeight, sf::Color(255, 255, 255, 255));
    Debug::DrawText(windowWidth / 2 - 50, windowHeight / 2, "Victory", sf::Color::Black);
}

void Menu::Dmenu(sf::RenderWindow* window)
{
    float windowWidth = static_cast<float>(window->getSize().x);
    float windowHeight = static_cast<float>(window->getSize().y);

    float containerWidth = windowWidth / 2.f;
    float containerHeight = windowHeight / 4.f;

    float containerX = (windowWidth - containerWidth) / 2.f;
    float containerY = (windowHeight - containerHeight) / 2.f;

    Debug::DrawFilledRectangle(containerX, containerY, containerWidth, containerHeight, sf::Color(255, 255, 255, 255));
    Debug::DrawText(windowWidth / 2 - 75, windowHeight / 2, "Game Over", sf::Color::Black);
}


Menu::~Menu()
{

}



void Menu::update()
{


}