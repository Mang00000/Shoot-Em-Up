#include "Entity.h"

#include "GameManager.h"
#include "Utils.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>

void Entity::Initialize(float radius, const sf::Color& color)
{
	mDirection = sf::Vector2f(0.0f, 0.0f);
	mSpeed = 0.0f;
	mToDestroy = false;
	mTag = -1;


	mWidth = radius * 2;
	mHeight = radius * 2;

	sf::CircleShape* circle = new sf::CircleShape();

	circle->setOrigin(0.f, 0.f);
	circle->setRadius(radius);
	circle->setFillColor(color);


	pDrawable = circle;
	pTransformable = circle;
	
	mTarget.isSet = false;
}

void Entity::Initialize(sf::Texture* pTexture, int Width, int Height)
{
	mDirection = sf::Vector2f(0.0f, 0.0f);
	mSpeed = 0.0f;
	mToDestroy = false;
	mTag = -1;
	mTarget.isSet = false;

	sf::Sprite* pSprite = new sf::Sprite();	

	pSprite->setTexture(*pTexture);
	pSprite->setOrigin(0.f, 0.f);

	float RatioScaleX = pTexture->getSize().x / (float) Width;
	float RatioScaleY = pTexture->getSize().y / (float) Height;

	float FinalRatio =  1 / std::max(RatioScaleX, RatioScaleY);
	pSprite->scale(sf::Vector2f(FinalRatio, FinalRatio));

	mWidth = pTexture->getSize().x * FinalRatio;
	mHeight = pTexture->getSize().y * FinalRatio;

	pDrawable = pSprite;
	pTransformable = pSprite;

}

bool Entity::IsColliding(Entity* other) const
{
	sf::Vector2f distance = GetPosition(0.5f, 0.5f) - other->GetPosition(0.5f, 0.5f);

	float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);

	float radius1 = mWidth / 2.f;
	float radius2 = other->mWidth / 2.f;

	float sqrRadius = (radius1 + radius2) * (radius1 + radius2);

	return sqrLength < sqrRadius;
}

bool Entity::IsInside(float x, float y) const
{
	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	float dx = x - position.x;
	float dy = y - position.y;

	float radius = mWidth / 2.f;

	return (dx * dx + dy * dy) < (radius * radius);
}

void Entity::SetPosition(float x, float y, float ratioX, float ratioY)
{
	x -= mWidth * ratioX;
	y -= mHeight * ratioY;

	pTransformable->setPosition(x, y);
}

sf::Vector2f Entity::GetPosition(float ratioX, float ratioY) const
{
	sf::Vector2f position = pTransformable->getPosition();

	position.x += mWidth * ratioX;
	position.y += mHeight * ratioY;

	return position;
}

bool Entity::GoToDirection(int x, int y, float speed)
{
	if(speed > 0)
		mSpeed = speed;

	sf::Vector2f position = GetPosition(0.5f, 0.5f);
	sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);
	
	bool success = Utils::Normalize(direction);
	if (success == false)
		return false;

	mDirection = direction;

	return true;
}

bool Entity::GoToPosition(int x, int y, float speed)
{
	if (GoToDirection(x, y, speed) == false)
		return false;

	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	mTarget.position = { x, y };
	mTarget.distance = Utils::GetDistance(position.x, position.y, x, y);
	mTarget.isSet = true;

	return true;
}

void Entity::SetDirection(float x, float y, float speed)
{
	if (speed > 0)
		mSpeed = speed;

	mDirection = sf::Vector2f(x, y);

	mTarget.isSet = false;
}

void Entity::Update()
{
	float dt = GetDeltaTime();
	float distance = dt * mSpeed;
	sf::Vector2f translation = distance * mDirection;
	pTransformable->move(translation);

	if (mTarget.isSet) 
	{
		mTarget.distance -= distance;

		if (mTarget.distance <= 0.f)
		{
			SetPosition(mTarget.position.x, mTarget.position.y, 0.5f, 0.5f);
			mDirection = sf::Vector2f(0.f, 0.f);
			mTarget.isSet = false;
		}
	}

	OnUpdate();
}

Scene* Entity::GetScene() const
{
	return GameManager::Get()->GetScene();
}

float Entity::GetDeltaTime() const
{
	return GameManager::Get()->GetDeltaTime();
}