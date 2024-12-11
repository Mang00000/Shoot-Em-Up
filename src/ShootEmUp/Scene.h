#pragma once

class GameManager;

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

class Scene
{
private:
	GameManager* mpGameManager;

private:
	void SetGameManager(GameManager* pGameManager) { mpGameManager = pGameManager; }
	
protected:
	Scene() = default;

	virtual void OnInitialize() = 0;
	virtual void OnEvent(const sf::Event& event) = 0;
	virtual void OnUpdate() = 0;

public:
	template<typename T>
	T* CreateEntity(float radius, const sf::Color& color);

	template<typename U>
	U* CreateEntity(std::string _Path, int Width, int Height);



	float GetDeltaTime() const;

	int GetWindowWidth() const;
	int GetWindowHeight() const;

	friend GameManager;
};

#include "Scene.inl"