#pragma once

#include <list>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

class Entity;
class Scene;
class Debug;

namespace sf 
{
	class RenderWindow;
	class Event;
}

class GameManager
{
	std::list<Entity*> mAllEntities;

	std::vector<std::list<Entity*>> mEntities;
	std::list<Entity*> mEntitiesToDestroy;
	std::list<Entity*> mEntitiesToAdd;

	sf::RenderWindow* mpWindow;
	sf::Font mFont;

	Scene* mpScene;

	float mDeltaTime;

	int mWindowWidth;
	int mWindowHeight;

private:
	bool isPaused = false;
	GameManager();

	void Run();
	
	void HandleInput();
	void Update();
	void Draw();

	void SetDeltaTime(float deltaTime) { mDeltaTime = deltaTime; }

	

public:
	~GameManager();
	static GameManager* Get();

	void CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit = 60);

	template<typename T>
	void LaunchScene();

	void Pause() {
		isPaused = !isPaused;
	}

	float GetDeltaTime(); const
	Scene* GetScene() const { return mpScene; }
	sf::Font& GetFont() { return mFont; };

	sf::RenderWindow* GetWindow() const { return mpWindow; };

	friend Debug;
	friend Scene;
};

#include "GameManager.inl"