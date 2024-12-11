#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>

namespace Utils
{
	bool Normalize(sf::Vector2f& vector);
	float GetDistance(int x1, int y1, int x2, int y2);
	float AngleBetween(const sf::Vector2f& v1, const sf::Vector2f& v2);
  sf::Vector2f RotateVector(const sf::Vector2f& vector, float angle);

	template <typename T>
	bool Contains(std::vector<T> container, T value) {
		for (T element : container) {
			if (element == value)
				return true;
		}
		return false;
	}

}