	#pragma once

#include "Scene.h"
#include "GameManager.h"
#include "Entity.h"
#include "ResourceManager.h"

template<typename T>
T* Scene::CreateEntity(float radius, const sf::Color& color)
{
	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T();

	Entity* entity = newEntity;
	entity->Initialize(radius, color);
	
	mpGameManager->mEntitiesToAdd.push_back(newEntity);

	return newEntity;
}

template<typename U>
U* Scene::CreateEntity(std::string _Path)
{
	static_assert(std::is_base_of<Entity, U>::value, "U must be derived from Entity");

	U* newEntity = new U();

	Entity* entity = newEntity;

	//if (ResourceManager::Get()->GetTexture(_Path) == ResourceManager::Get()->GetInvalidTexturePath()) {
	//	ResourceManager::LoadTexture(_Path);
	//}

	entity->Initialize(ResourceManager::Get()->GetTexture(_Path));

	mpGameManager->mEntitiesToAdd.push_back(newEntity);

	return newEntity;
}