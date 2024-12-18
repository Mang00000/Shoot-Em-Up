#pragma once



class GameManager;
enum class EntityType;

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
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
    T* CreateEntity(float radius, const sf::Color& color, EntityType type, int layer = 0);

    template<typename T>
    T* CreateEntity(int width, int height, float angle, const sf::Color& color, EntityType type, int layer = 0);

    template<typename T>
    T* CreateEntity(std::string _Path, int Width, int Height, int nbImage, float duration, EntityType type, int layer = 0);

    template<typename U>
    U* CreateEntity(std::string _Path, int Width, int Height, EntityType type, int layer = 0);

    float GetDeltaTime() const;


    int GetWindowWidth() const;
    int GetWindowHeight() const;
    sf::RenderWindow* GetRenderWindow() const;

    friend GameManager;
};

#include "Scene.inl"
