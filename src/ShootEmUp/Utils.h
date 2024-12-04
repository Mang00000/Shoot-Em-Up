#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>

namespace Utils
{
	bool Normalize(sf::Vector2f& vector);
	float GetDistance(int x1, int y1, int x2, int y2);
	template <typename T>
	bool Contains(std::vector<T> container, T value) {
		for (T element : container) {
			if (element == value)
				return true;
		}
		return false;
	}
}