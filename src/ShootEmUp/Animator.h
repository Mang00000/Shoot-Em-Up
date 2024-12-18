#ifndef ANIMATOR_H__
#define ANIMATOR_H__

#include "SFML/Graphics.hpp"
#include "ResourceManager.h"


class Animator {
	sf::Texture* mTexture;
	sf::IntRect sourceRect;
	float mDuration;
	unsigned int nbImages;
	unsigned int currentImage = 0;
	sf::Vector2f mSize;

	sf::Sprite* mSprite;
	float frameProgress;
	float frameDuration;
public:
	Animator(const std::string& path, sf::Vector2f size, sf::Sprite* sprite);
	Animator(sf::Texture* texture, sf::Vector2f size, sf::Sprite* sprite);
	void SetAnimation(unsigned int numImages, float duration, sf::Vector2f size);
	void Update(float deltatime);

	sf::IntRect GetSourceRect() { return sourceRect; }
	sf::Vector2f GetSize() { return mSize; }

};

#endif // !ANIMATOR_H__
