#include "Entity.h"
#include "GameScene.h"
#include "GameManager.h"
#include "Utils.h"
#include <cmath>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Collider.h"
#include "ColliderManager.h"
#include "Animator.h"
#include "AnimatorLogan.h"
#include "Animation.h"


void Entity::Initialize(float radius, const sf::Color& color, EntityType type, int layer)
{
	OnInitialize(type, layer);


	mWidth = radius * 2;
	mHeight = radius * 2;

	mBaseHeight = mHeight;
	mBaseWidth = mWidth;

	sf::CircleShape* circle = new sf::CircleShape();

	circle->setOrigin(0.5f * mWidth, 0.5f * mHeight);
	circle->setRadius(radius);
	circle->setFillColor(color);



	pDrawable = circle;
	pTransformable = circle;

	
	mCollider = new CircleCollider(this, radius);
}

void Entity::Initialize(sf::Texture* pTexture, int Width, int Height, EntityType type, int layer)
{
	OnInitialize(type, layer);

	sf::Sprite* pSprite = new sf::Sprite();


	float RatioScaleX = pTexture->getSize().x / (float)Width;
	float RatioScaleY = pTexture->getSize().y / (float)Height;

	float FinalRatio = 1 / std::max(RatioScaleX, RatioScaleY);
	pSprite->scale(sf::Vector2f(FinalRatio, FinalRatio));

	mWidth = pTexture->getSize().x * FinalRatio;
	mHeight = pTexture->getSize().y * FinalRatio;

	mBaseHeight = mHeight;
	mBaseWidth = mWidth;



	sf::Vector2f test = Utils::Normalize2(sf::Vector2f(RatioScaleX, RatioScaleY));

	mScaleX = test.x;
	mScaleY = test.y;

	pSprite->setOrigin((0.5f * mWidth) / FinalRatio, (0.5f * mHeight)/FinalRatio);
	pSprite->setTexture(*pTexture);
	


	pDrawable = pSprite;
	pTransformable = pSprite;

	

	mCollider = new RectangleCollider(this, mWidth, mHeight);
}

void Entity::Initialize(std::string path, int Width, int Height, int nbImage, float duration, EntityType type, int layer)
{
	OnInitialize(type, layer);
	sf::Texture* pTexture = ResourceManager::Get()->GetTexture(path);

	std::vector<float> AnimationFrameDelay = {};
	for (int i = 0; i < nbImage; i++) {
		AnimationFrameDelay.push_back((float)(duration / nbImage));
	}

	sf::Sprite* pSprite = new sf::Sprite();

	float RatioScaleX = pTexture->getSize().x / (float)Width;
	float RatioScaleY = pTexture->getSize().y / (float)Height;

	float FinalRatio = 1 / std::max(RatioScaleX, RatioScaleY);
	pSprite->scale(sf::Vector2f(FinalRatio, FinalRatio));

	mWidth = pTexture->getSize().x * FinalRatio;
	mHeight = pTexture->getSize().y * FinalRatio;

	sf::Vector2f test = Utils::Normalize2(sf::Vector2f(RatioScaleX, RatioScaleY));

	mScaleX = test.x;
	mScaleY = test.y;

	mBaseHeight = mHeight;
	mBaseWidth = mWidth;

	pSprite->setOrigin((0.5f * mWidth) / FinalRatio, (0.5f * mHeight) / FinalRatio);

	mAnimation = AnimatorLogan::CreateAnimation(path, nbImage, AnimationFrameDelay,pSprite);


	pDrawable = pSprite;
	pTransformable = pSprite;

	mCollider = new RectangleCollider(this, mWidth, mHeight);


	/*
	* 
	* VERSION SI ON A DES SPRITESHEETS MAIS VU QUE ON EN A PAS JAI DU TOUT REWORK, IMPECCABLE LE GC
	* 
	mAnimator = new Animator(pTexture, sf::Vector2f(Width / nbImage, Height / nbImage), pSprite);

	mAnimator->SetAnimation(nbImage, duration, sf::Vector2f(pTexture->getSize().x / nbImage, pTexture->getSize().y / nbImage));
	*/

}

void Entity::Initialize(int width, int height, float angle, const sf::Color& color, EntityType type, int layer)
{
	OnInitialize(type, layer);

	if (angle == 0) { //RECTANGLE CASE
		mWidth = width;
		mHeight = height;

		mBaseHeight = mHeight;
		mBaseWidth = mWidth;

		sf::RectangleShape* rectangle = new sf::RectangleShape();

		rectangle->setFillColor(color);
		rectangle->setSize(sf::Vector2f(mWidth, mHeight));
		rectangle->setOrigin(0.5f * mWidth, 0.5f * mHeight);

		pDrawable = rectangle;
		pTransformable = rectangle;

		mCollider = new RectangleCollider(this, mWidth, mHeight);
	}
	else { //OOBB CASE
		mWidth = width;
		mHeight = height;
		mAngle = angle;

		mBaseHeight = mHeight;
		mBaseWidth = mWidth;

		mCenter = sf::Vector2f(mWidth / 2, mHeight / 2);

		sf::RectangleShape* rectangle = new sf::RectangleShape();

		rectangle->setSize(sf::Vector2f(mWidth, mHeight));
		rectangle->setOrigin(0.5f * mWidth, 0.5f * mHeight);
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
	x += (mWidth * 0.5f) - (mWidth * ratioX);
	y += (mHeight * 0.5f) - (mHeight * ratioY);

	pTransformable->setPosition(x, y);
}

sf::Vector2f Entity::GetPosition(float ratioX, float ratioY) const
{
	sf::Vector2f position = pTransformable->getPosition();

	position.x -= (mWidth * 0.5f) - (mWidth * ratioX);
	position.y -= (mHeight * 0.5f) - (mHeight * ratioY);

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

void Entity::Rescale(float scaleX, float scaleY)
{
	//DOES NOT WORK
	mWidth = mBaseWidth * scaleX;
	mHeight = mBaseHeight * scaleY;
	mScaleX = scaleX;
	mScaleY = scaleY;
	pTransformable->setScale(scaleX, scaleY);

	if (mCollider->mType == Collider::ColliderType::AABB) {
		RectangleCollider* Rect = (RectangleCollider*)mCollider;
		Rect->SetWidth(Rect->GetWidth() * scaleX);
		Rect->SetHeight(Rect->GetHeight() * scaleY);
	}
	else if(mCollider->mType == Collider::ColliderType::Circle){
		CircleCollider* Circle = (CircleCollider*)mCollider;
		Circle->SetRadius(Circle->GetRadius() * scaleX);
	}
}

void Entity::OnInitialize(EntityType type, int layer)
{
	mDirection = sf::Vector2f(0.0f, 0.0f);
	mSpeed = 0.0f;
	mToDestroy = false;
	mType = type;
	mTarget.isSet = false;
	mLayer = layer;
}

void Entity::Update()
{
	float dt = GetDeltaTime();
	float distance = dt * mSpeed;
	sf::Vector2f translation = distance * mDirection;
	pTransformable->move(translation);
	if (mAnimator != nullptr) {
		mAnimator->Update(dt);
	}

	if (mAnimation != nullptr) {
		mAnimation->AnimationUpdate(dt);
	}

	//float WHeight = GetScene()->GetWindowHeight();

	//float Scale = (this->GetPosition().y + (WHeight / 4) * abs(this->GetPosition().y / WHeight - 1)) / WHeight;


	//if (mScaleX == Scale) {
	//	Rescale(mScaleX, mScaleY);
	//}
	//else {
	//	Rescale(mScaleX + Scale, mScaleY + Scale);
	//}

	//


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