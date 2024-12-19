#ifndef ANIMATION__H_
#define ANIMATION__H_


#include <vector>
#include "SFML/Graphics.hpp"

namespace sf {
    class RenderWindow;
    class Texture;
}

class Animation
{
    std::vector<sf::Texture*> mAnimationFrames;
    size_t mframeSize;
    std::vector<float> mframeDelay;
    float mtimer;
    int mcurrentframe;
    sf::Sprite* mSprite;
public:
    Animation(std::vector<sf::Texture*> AnimationFrames, std::vector<float> frameDelay, sf::Sprite* pSprite);
    void AnimationInit();
    void AnimationUpdate(float deltaTime);
};

#endif // !ANIMATION__H_
