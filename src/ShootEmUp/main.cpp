
#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameManager.h"
#include "GameScene.h"
#include "SampleScene.h"

#include <cstdlib>
#include <crtdbg.h>

#include <iostream>
#include <filesystem>
#include "ResourceManager.h"

int main() 
{
  GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1280, 720, "SampleScene", 240);
	
	pInstance->LaunchScene<SampleScene>();


	return 0;
}