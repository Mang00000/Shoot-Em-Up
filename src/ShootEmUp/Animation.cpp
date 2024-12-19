#include "Animation.h"

Animation::Animation(std::vector<sf::Texture*> AnimationFrames, std::vector<float> frameDelay, sf::Sprite* pSprite)
{
    mAnimationFrames = AnimationFrames;
    mframeDelay = frameDelay;
    mframeSize = mAnimationFrames.size();
    AnimationInit();
    mSprite = pSprite;
}

void Animation::AnimationInit()
{
    mtimer = 0.f;
    mcurrentframe = 0;
}

void Animation::AnimationUpdate(float deltaTime)
{
    mtimer += deltaTime;

    if (mcurrentframe >= mframeSize - 1)
        mcurrentframe = 0;

    if (mtimer >= mframeDelay[mcurrentframe]) {
        mtimer = 0;
        mcurrentframe++;

        mSprite->setTexture(*(mAnimationFrames[mcurrentframe]), false); 
    }
}
