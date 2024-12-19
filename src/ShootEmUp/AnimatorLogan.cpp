#include "AnimatorLogan.h"
#include "Animation.h"
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"

AnimatorLogan::AnimatorLogan()
{
}

Animation* AnimatorLogan::CreateAnimation(std::string Numpath, int NumberofFrames, std::vector<float> FrameDelay, sf::Sprite* pSprite)
{
    size_t Size = Numpath.length();
    std::string Pathend = Numpath.substr(Size - 4, Size - 1);

    size_t SizeEnd = Pathend.length();

    std::vector<sf::Texture*> textures;
    for (int i = 0; i < NumberofFrames; i++) {

        for (int j = Size; j > Size - 5 - (1 * int((i - 1) / 10)); j--)
            Numpath.pop_back();
        Numpath += std::to_string(i) + Pathend;
        textures.push_back(ResourceManager::Get()->GetTexture(Numpath));
    }
    Animation* anim = new Animation(textures, FrameDelay, pSprite);
    return anim;
}
