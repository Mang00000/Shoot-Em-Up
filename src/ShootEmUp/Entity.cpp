#include "Entity.h"
#include "GameScene.h"
#include "GameManager.h"
#include "Utils.h"
#include <cmath>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Collider.h"
#include "ColliderManager.h"


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
	
	mCollider = new CircleCollider(this, radius);
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

	mCollider = new RectangleCollider(this, mWidth, mHeight);

}

void Entity::Initialize(int width, int height, float angle, const sf::Color& color)
{
	mDirection = sf::Vector2f(0.0f, 0.0f);
	mSpeed = 0.0f;
	mToDestroy = false;
	mTag = -1;
	mTarget.isSet = false;

	if (angle == 0) { //RECTANGLE CASE
		std::cout << "rectangle case" << std::endl;
		mWidth = width;
		mHeight = height;

		sf::RectangleShape* rectangle = new sf::RectangleShape();

		rectangle->setOrigin(0, 0);
		rectangle->setFillColor(color);
		rectangle->setSize(sf::Vector2f(mWidth, mHeight));

		pDrawable = rectangle;
		pTransformable = rectangle;

		mCollider = new RectangleCollider(this, mWidth, mHeight);
	}
	else { //OOBB CASE
		std::cout << "OOBB case" << std::endl;
		mWidth = width;
		mHeight = height;
		mAngle = angle;
		mCenter = sf::Vector2f(mWidth / 2, mHeight / 2);

		mRatioX = 0.5f;
		mRatioY = 0.5f;

		sf::RectangleShape* rectangle = new sf::RectangleShape();

		rectangle->setSize(sf::Vector2f(mWidth, mHeight));
		rectangle->setOrigin(mWidth * mRatioX, mHeight * mRatioY);
		rectangle->setFillColor(color);
		rectangle->setRotation(mAngle);

		pDrawable = rectangle;
		pTransformable = rectangle;

		mCollider = new OOBBCollider(this, mWidth, mHeight, sf::Vector2f(mWidth / 2, mHeight / 2), mAngle);
	}

}

bool Entity::IsColliding(Entity* other) const
{
	return ColliderManager::ResolveCollision(this->mCollider, other->mCollider);
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
	x -= mWidth * (ratioX - mRatioX);
	y -= mHeight * (ratioY - mRatioY);

	pTransformable->setPosition(x, y);
}

sf::Vector2f Entity::GetPosition(float ratioX, float ratioY) const
{
	sf::Vector2f position = pTransformable->getPosition();

	position.x += (mRatioX - ratioX);
	position.y += (mRatioY - ratioY);

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
void Entity::RotateDirection(float angleDegrees)
{
	float angleRadians = angleDegrees * (3.14159 / 180.0f);

	float newX = mDirection.x * cos(angleRadians) - mDirection.y * sin(angleRadians);
	float newY = mDirection.x * sin(angleRadians) + mDirection.y * cos(angleRadians);

	mDirection = sf::Vector2f(newX, newY);
}