#include "GameScene.h"

#include "Camion.h"
#include "Projectile.h"
#include "Player.h"
#include "GoFast.h"

#include "Debug.h"

#include <iostream>

#include <stdlib.h>

#include "Utils.h" 

void GameScene::OnInitialize()
{

	pEntity2 = CreateEntity<Player>(50, sf::Color::Green);
	pEntity2->SetPosition(500, 500);
    pEntity2->SetTag(1);

    camion = CreateEntity<Camion>(20, sf::Color::Blue);
    camion->SetPosition(200, 580);

    camion2 = CreateEntity<Camion>(20, sf::Color::Blue);
    camion2->SetPosition(500, 20);

    f = CreateEntity<GoFast>(60, sf::Color::Yellow);
    f->SetPosition(500, 250);

	pEntitySelected = nullptr;
}

void GameScene::OnEvent(const sf::Event& event)
{
    if (event.type == sf::Event::EventType::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Right) {
        TrySetSelectedEntity(pEntity2, event.mouseButton.x, event.mouseButton.y);
    }

    else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
        bool isMovingUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        bool isMovingDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        bool isMovingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        bool isMovingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        bool isSlowed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

        if (pEntitySelected != nullptr) {
            float speed = isSlowed ? 400.0f / 3.0f : 400.0f;
            float deltaTime = GetDeltaTime();

            float moveX = 0.0f;
            float moveY = 0.0f;
            float radius = 0;

            if (isMovingUp)    moveY -= 1.0f;
            if (isMovingDown)  moveY += 1.0f;
            if (isMovingLeft)  moveX -= 1.0f;
            if (isMovingRight) moveX += 1.0f;


            if (moveX != 0.0f || moveY != 0.0f ) {
                sf::Vector2f direction(moveX, moveY);
                if (Utils::Normalize(direction)) {
                    pEntitySelected->SetDirection(direction.x, direction.y, speed); // Mouvement
                }
                
            }
            else {
                pEntitySelected->SetSpeed(0); pEntitySelected->SetDirection(0, 0); // Stopper le mouvement
            }
            system("cls"); std::cout << "Up: " << isMovingUp << "\nDown: " << isMovingDown << "\nRight: " << isMovingRight << "\nLeft: " << isMovingLeft <<"\n" << moveY <<"\n" << moveX << std::endl; // Debug
        }
        
    }
}





void GameScene::TrySetSelectedEntity(Player* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void GameScene::OnUpdate()
{
	if (pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
}

Player* GameScene::GetPlayer()
{
    return pEntity2;
}
