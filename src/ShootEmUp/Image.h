#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>

class Image : public Entity
{
private:
    float mSpeed;

public:
    void OnUpdate() override;
    void SetParallax(float speed) {
        mSpeed = speed;
    }
};
