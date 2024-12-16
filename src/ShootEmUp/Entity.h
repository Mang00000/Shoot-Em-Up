#pragma once

#include <SFML/System/Vector2.hpp>
#include "GameScene.h"
#include <SFML/Graphics.hpp>

namespace sf 
{
	class Shape;
    class Color;
}

class Scene;
class EntityDesign;
class Collider;


class Entity
{
    struct Target 
    {
		sf::Vector2i position;
        float distance;
		bool isSet;
    };

protected:
    sf::Vector2f mDirection;
	Target mTarget;
    float mSpeed;
    bool mToDestroy;
    std::string mTag;

    int mWidth;
    int mHeight;

    sf::Drawable* pDrawable;
    sf::Transformable* pTransformable;

    Collider* mCollider;
public:
	bool GoToDirection(int x, int y, float speed = -1.0f);
    bool GoToPosition(int x, int y, float speed = -1.0f);
    void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f);
	void SetDirection(float x, float y, float speed = -1.0f);
	void SetSpeed(float speed) { mSpeed = speed; }
	void SetTag(std::string tag) { mTag = tag; }

    sf::Drawable* GetDrawable() { return pDrawable; }
    sf::Transformable* GetTransformable() { return pTransformable; }

    int GetWidth() { return mWidth; }
    int GetHeight() { return mHeight; }
    Collider* GetCollider() { return mCollider; }
    

    sf::Vector2f GetPosition(float ratioX = 0.5f, float ratioY = 0.5f) const;

    sf::Vector2f GetCenter() { return GetPosition(0.5, 0.5); }
    sf::Vector2f GetTopLeft() { return GetPosition(0, 0); }

	bool IsTag(std::string tag) const { return mTag == tag; }
    bool IsColliding(Entity* other) const;
	bool IsInside(float x, float y) const;

	void Destroy() { mToDestroy = true; }
	bool ToDestroy() const { return mToDestroy; }
	
	template<typename T>
	T* GetScene() const;

    Scene* GetScene() const;
	float GetDeltaTime() const;
    sf::Vector2f GetDirection() const
    {
        return mDirection;
    }


    template<typename T>
    T* CreateEntity(float radius, const sf::Color& color);

    template<typename U>
    U* CreateEntity(sf::Texture* pTexture);

    void RotateDirection(float angleDegrees);

protected:
    Entity() = default;
    ~Entity() = default;

    virtual void OnUpdate() {};
    virtual void OnCollision(Entity* collidedWith) {};
	virtual void OnInitialize() {};
	
private:
    void Update();
	void Initialize(float radius, const sf::Color& color);
    void Initialize(sf::Texture* pTexture, int Width, int Height);

    friend class GameManager;
    friend Scene;

};

#include "Entity.inl"