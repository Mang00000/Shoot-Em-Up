#include "SampleScene.h"
#include "DummyEntity.h"
#include "Debug.h"
#include <iostream>
#include "ResourceManager.h"
#include "Collider.h"
#include "Animator.h"
#include "LevelManager.h"


void SampleScene::OnInitialize()
{
	pEntity1 = CreateEntity<DummyEntity>(100, sf::Color::Red, EntityType::Player, 1);
	pEntity1->SetPosition(500, 400);

	pEntity2 = CreateEntity<DummyEntity>("../../../res/Anim/test0.png", 250, 100,4,1, EntityType::Enemy, 0);
	pEntity2->SetPosition(100, 200);

	pEntity3 = CreateEntity<DummyEntity>("../../../res/Anim/test0.png", 250, 100, EntityType::Enemy, 2);
	pEntity3->SetPosition(500, 400);




	//pEntity1 = CreateEntity<DummyEntity>(100, 60, 50, sf::Color::White);
	//pEntity1->SetPosition(100, 100);

	//pEntity3 = CreateEntity<DummyEntity>(100, 60, 20, sf::Color::White);
	//pEntity3->SetPosition(500, 500);

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
		TrySetSelectedEntity(pEntity3, event.mouseButton.x, event.mouseButton.y);
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

		if (pEntitySelected->GetCollider()->mType == Collider::ColliderType::Circle) {
			CircleCollider* Test = (CircleCollider*)pEntitySelected->GetCollider();
			//Debug::DrawCircle(Test->mParentEntity->GetPosition().x, Test->mParentEntity->GetPosition().y, Test->mRadius, sf::Color::White);
		}
		else if (pEntitySelected->GetCollider()->mType == Collider::ColliderType::AABB) {
			RectangleCollider* Test = (RectangleCollider*)pEntitySelected->GetCollider();
			Debug::DrawRectangle(Test->mParentEntity->GetPosition(0, 0).x, Test->mParentEntity->GetPosition(0, 0).y, Test->mWidth, Test->mHeight, sf::Color::White);
			//Debug::DrawFilledRectangle(Test->mParentEntity->GetPosition(0, 0).x, Test->mParentEntity->GetPosition(0, 0).y, Test->mWidth, Test->mHeight, sf::Color::White);
		}
		else if (pEntitySelected->GetCollider()->mType == Collider::ColliderType::OOBB) {
			OOBBCollider* Test = (OOBBCollider*)pEntitySelected->GetCollider();
			//Debug::DrawOrientendRectangle(Test->mParentEntity->GetPosition(0.5f, 0.5f).x, Test->mParentEntity->GetPosition(0.5f, 0.5f).y, Test->mWidth, Test->mHeight, Test->mAngle, sf::Color::White);
			Debug::DrawCircle(Test->mParentEntity->GetPosition(0.5, 0.5).x, Test->mParentEntity->GetPosition(0.5, 0.5).y, 5, sf::Color::Red);

			Debug::DrawInfiniteLine(Test->mPoints[0].x + Test->mTrueWidth.x + Test->mTrueHeight.x, Test->mPoints[0].y + Test->mTrueWidth.y + Test->mTrueHeight.y, Test->mNormals[0], sf::Color::Yellow);
			//Debug::DrawInfiniteLine(100, 100, Test->mNormals[0], sf::Color::Yellow);
		}

	}
}