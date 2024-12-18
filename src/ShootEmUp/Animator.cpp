#include "Animator.h"

Animator::Animator(const std::string& path, sf::Vector2f size, sf::Sprite* sprite)
{
	mTexture = ResourceManager::Get()->GetTexture(path);

	mSprite = sprite;

	sourceRect.top = 0;
	sourceRect.left = 0;
	sourceRect.width = mTexture->getSize().x;
	sourceRect.height = mTexture->getSize().y;

	nbImages = 1;
	frameProgress = 0;
	frameDuration = 1000;

	mSprite->setTexture(*mTexture);
	mSprite->setTextureRect(sourceRect);

	mSize = size;

	mSprite->setScale(
		size.x / sourceRect.width,
		size.y / sourceRect.height
	);
}

Animator::Animator(sf::Texture* texture, sf::Vector2f size, sf::Sprite* sprite)
{
	mTexture = texture;

	sourceRect.top = 0;
	sourceRect.left = 0;
	sourceRect.width = mTexture->getSize().x;
	sourceRect.height = mTexture->getSize().y;

	mSprite = sprite;

	mDuration = 0;
	nbImages = 1;
	frameProgress = 0;
	frameDuration = 1000;

	mSprite->setTexture(*mTexture);
	mSprite->setTextureRect(sourceRect);

	mSize = size;

	mSprite->setScale(
		size.x / sourceRect.width,
		size.y / sourceRect.height
	);
}

void Animator::SetAnimation(unsigned int numImages, float duration, sf::Vector2f size)
{
	nbImages = numImages;
	mDuration = duration;

	sourceRect.width = size.x;
	sourceRect.height = size.y;
	mSprite->setTextureRect(sourceRect);
	mSprite->setScale(
		mSize.x / sourceRect.width,
		mSize.y / sourceRect.height
	);
	frameDuration = mDuration / nbImages;
}


void Animator::Update(float deltatime)
{
	frameProgress += deltatime;

	if (frameProgress > frameDuration)
	{
		sourceRect.left += sourceRect.width;
		currentImage++;
		if (currentImage >= nbImages) {
			sourceRect.left = 0;
			currentImage = 0;
		}
		mSprite->setTextureRect(sourceRect);
		frameProgress -= frameDuration;
	}
}
