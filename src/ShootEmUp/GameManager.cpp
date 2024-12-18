#include "GameManager.h"

#include "Entity.h"
#include "Debug.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include "ResourceManager.h"

GameManager::GameManager()
{
	mpWindow = nullptr;
	mDeltaTime = 0.0f;
	mpScene = nullptr;
	mWindowWidth = -1;
	mWindowHeight = -1;

	mEntities.resize(5);
}

GameManager* GameManager::Get()
{
	static GameManager mInstance;

	return &mInstance;
}

GameManager::~GameManager()
{
	delete mpWindow;
	delete mpScene;

	for (auto& list : mEntities)
	{
		for (auto it = list.begin(); it != list.end(); ++it) {

			delete *it;
		}

		list.clear();
	}

	mEntities.clear();
}

void GameManager::CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit)
{
	_ASSERT(mpWindow == nullptr);

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	mpWindow = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Default, settings);
	mpWindow->setFramerateLimit(fpsLimit);

	mWindowWidth = width;
	mWindowHeight = height;
}


void GameManager::Run()
{
	if (mpWindow == nullptr) 
	{
		std::cout << "Window not created, creating default window" << std::endl;
		CreateWindow(1280, 720, "Default window");
	}

	//#TODO : Load somewhere else
	bool fontLoaded = mFont.loadFromFile("../../../res/Hack-Regular.ttf");
	_ASSERT(fontLoaded);

	_ASSERT(mpScene != nullptr);

	sf::Clock clock;
	while (mpWindow->isOpen())
	{
		SetDeltaTime(clock.restart().asSeconds());

		HandleInput();

		Update();
		
		Draw();
	}
}

void GameManager::HandleInput()
{
	sf::Event event;
	while (mpWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mpWindow->close();
		}

		mpScene->OnEvent(event);
	}
}

void GameManager::Update()
{
	mpScene->OnUpdate();

	//Update
	for (auto& list : mEntities)
	{
		for (auto it = list.begin(); it != list.end(); )
		{
			Entity* entity = *it;

			entity->Update();

			if (entity->ToDestroy() == false)
			{
				++it;
				continue;
			}

			mEntitiesToDestroy.push_back(entity);
			it = list.erase(it);
		}
	}

    

    //Collision
	for (auto& list : mEntities)
	{
		for (auto it1 = list.begin(); it1 != list.end(); ++it1)
		{
			auto it2 = it1;
			++it2;
			for (; it2 != list.end(); ++it2)
			{
				Entity* entity = *it1;
				Entity* otherEntity = *it2;

				if (entity->IsColliding(otherEntity))
				{
					entity->OnCollision(otherEntity);
					otherEntity->OnCollision(entity);
				}
			}
		}
	}
   

	for (auto it = mEntitiesToDestroy.begin(); it != mEntitiesToDestroy.end(); ++it) 
	{
		delete *it;
	}

    mEntitiesToDestroy.clear();

	for (auto it = mEntitiesToAdd.begin(); it != mEntitiesToAdd.end(); ++it)
	{
		Entity* EntityToAdd = *it;
		int layer = EntityToAdd->GetLayer();

		mEntities[layer].push_back(*it);
	}

	mEntitiesToAdd.clear();
}

void GameManager::Draw()
{
	mpWindow->clear();


	for (auto& list : mEntities)
	{
		for (Entity* entity : list)
		{
			mpWindow->draw(*entity->pDrawable);
		}
	}
	
	
	Debug::Get()->Draw(mpWindow);

	mpWindow->display();
}
