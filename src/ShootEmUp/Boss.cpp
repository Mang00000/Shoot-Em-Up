#include "Camion.h"
#include "Projectile.h"
#include "GameScene.h"
#include <iostream>
#include "Player.h"
#include "Utils.h"
#include "Scene.h"
#include "Boss.h"

void Boss::OnCollision(Entity* other)
{
    if (other->IsTag(1)) {
        mToDestroy = true;
        other->Destroy();
    }
}

void Boss::OnUpdate()
{

}
