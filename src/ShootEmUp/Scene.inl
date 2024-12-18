#pragma once

#include "Scene.h"
#include "GameManager.h"
#include "Entity.h"
#include "ResourceManager.h"

template<typename T>
T* Scene::CreateEntity(float radius, const sf::Color& color, EntityType type)
{
	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T();

	Entity* entity = newEntity;
	entity->Initialize(radius, color, type);
	
	mpGameManager->mEntitiesToAdd.push_back(newEntity);

	return newEntity;
}

template<typename T>
T* Scene::CreateEntity(int width, int height, float angle, const sf::Color& color)
{
	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T();

	Entity* entity = newEntity;
	entity->Initialize(width, height, angle, color);

	mpGameManager->mEntitiesToAdd.push_back(newEntity);

	return newEntity;
}

template<typename T>
inline T* Scene::CreateEntity(std::string _Path, int Width, int Height, int nbImage, float duration)
{
	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T();

	Entity* entity = newEntity;

	entity->Initialize(ResourceManager::Get()->GetTexture(_Path), Width, Height, nbImage, duration);

	mpGameManager->mEntitiesToAdd.push_back(newEntity);

	return newEntity;
}

template<typename U>
U* Scene::CreateEntity(std::string _Path, int Width, int Height)
{
	static_assert(std::is_base_of<Entity, U>::value, "U must be derived from Entity");

	U* newEntity = new U();

	Entity* entity = newEntity;

	entity->Initialize(ResourceManager::Get()->GetTexture(_Path), Width, Height);

	mpGameManager->mEntitiesToAdd.push_back(newEntity);

	return newEntity;
}

