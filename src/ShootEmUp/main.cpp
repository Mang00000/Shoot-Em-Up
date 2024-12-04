
#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameManager.h"
#include "SampleScene.h"

#include <cstdlib>
#include <crtdbg.h>
/*
#define SFML

#ifdef SFML
class LEText : sf::Text 
{
#else

class LEText : GC::Text
{
#endif


}*/;

#include <iostream>
#include <filesystem>
#include "ResourceManager.h"

int main() 
{
  /*  GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1280, 720, "SampleScene");
	
	pInstance->LaunchScene<SampleScene>();*/


	ResourceManager::Get()->LoadAllTextures("../../../res");

	std::cout << ResourceManager::Get()->GetNumberOfTextures() << std::endl;

	ResourceManager::Get()->ClearTextures();

	std::cout << ResourceManager::Get()->GetNumberOfTextures() << std::endl;

	return 0;
}