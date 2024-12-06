#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

namespace sf 
{
	class Shape;
    class Color;
}

class Scene;

class Entity
{
    struct Target 
    {
		sf::Vector2i position;
        float distance;
		bool isSet;
    };

protected:
    sf::CircleShape mShape;
    sf::Vector2f mDirection;
    sf::Texture* mTexture;
    sf::Sprite mSprite;
	Target mTarget;
    float mSpeed;
    bool mToDestroy;
    int mTag;

public:
	bool GoToDirection(int x, int y, float speed = -1.f);
    bool GoToPosition(int x, int y, float speed = -1.f);
    void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f);
	void SetDirection(float x, float y, float speed = -1.f);
	void SetSpeed(float speed) { mSpeed = speed; }
    void SetTexture(sf::Texture* pTexture) { mTexture = pTexture; }
	void SetTag(int tag) { mTag = tag; }
	float GetRadius() const { return mShape.getRadius(); }

    sf::Vector2f GetPosition(float ratioX = 0.5f, float ratioY = 0.5f) const;
	sf::Shape* GetShape() { return &mShape; }

	bool IsTag(int tag) const { return mTag == tag; }
    bool IsColliding(Entity* other) const;
	bool IsInside(float x, float y) const;

	void Destroy() { mToDestroy = true; }
	bool ToDestroy() const { return mToDestroy; }
	
	template<typename T>
	T* GetScene() const;

    Scene* GetScene() const;
	float GetDeltaTime() const;

    template<typename T>
    T* CreateEntity(float radius, const sf::Color& color);

    template<typename U>
    U* CreateEntity(sf::Texture* pTexture);

protected:
    Entity() = default;
    ~Entity() = default;

    virtual void OnUpdate() {};
    virtual void OnCollision(Entity* collidedWith) {};
	virtual void OnInitialize() {};
	
private:
    void Update();
	void Initialize(float radius, const sf::Color& color);
    void Initialize(sf::Texture* pTexture);

    friend class GameManager;
    friend Scene;
};

#include "Entity.inl"