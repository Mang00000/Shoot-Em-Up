#ifndef ANIMATORLOGAN_H__
#define ANIMATORLOGAN_H__

#include <vector>
#include <string>

class Animation;

#include "SFML/Graphics.hpp"

namespace sf {
    class RenderWindow;
    class Texture;
}


class AnimatorLogan {
public:
    AnimatorLogan();
    static Animation* CreateAnimation(std::string Numpath, int NumberofFrames, std::vector<float> FrameDelay, sf::Sprite* pSprite);
};
#endif // !ANIMATORLOGAN_H__


