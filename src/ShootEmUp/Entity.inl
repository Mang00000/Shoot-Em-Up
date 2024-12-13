#include "Entity.h"

#include "GameManager.h"

template<typename T>
T* Entity::GetScene() const
{
	T* pScene = dynamic_cast<T*>(GetScene());

	_ASSERT(pScene != nullptr);

	return pScene;
}


template<typename T>
T* Entity::CreateEntity(float radius, const sf::Color& color)
{
	return GetScene()->CreateEntity<T>(radius, color);
}

template<typename T>
inline T* Entity::CreateEntity(float x, float y, int width, int height, float angle, const sf::Color& color)
{
	return GetScene()->CreateEntity<T>(x, y, width, height, angle, color);
}

template<typename U>
inline U* Entity::CreateEntity(sf::Texture* pTexture)
{
	return GetScene()->CreateEntity<U>(pTexture);
}
