#include "SampleScene.h"

#include "DummyEntity.h"

#include "Debug.h"

#include <iostream>
#include "ResourceManager.h"

void SampleScene::OnInitialize()
{
	pEntity1 = CreateEntity<DummyEntity>(100, sf::Color::Red);
	pEntity1->SetPosition(100, 100);

	pEntity3 = CreateEntity<DummyEntity>("../../../res/blursed-sitting-tiger-v0-pp4thbxfjz6d1.jpg");
	pEntity3->SetPosition(500, 500);
	

	pEntitySelected = nullptr;
}

void SampleScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		TrySetSelectedEntity(pEntity1, event.mouseButton.x, event.mouseButton.y);
		TrySetSelectedEntity(pEntity2, event.mouseButton.x, event.mouseButton.y);
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (pEntitySelected != nullptr) 
		{
			pEntitySelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
		}
	}
}

void SampleScene::TrySetSelectedEntity(DummyEntity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void SampleScene::OnUpdate()
{
	if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}

}