#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <numbers>

namespace Utils
{
	bool Normalize(sf::Vector2f& vector);
	float GetDistance(int x1, int y1, int x2, int y2);
	float AngleBetween(const sf::Vector2f& v1, const sf::Vector2f& v2);
	float Dot(const sf::Vector2f& v1, const sf::Vector2f& v2);
	sf::Vector2f RotateVector(const sf::Vector2f& vector, float angle);

	bool IsBetweenOrdered(float value, float lowerbound, float upperbound);
	bool Overlaps(float min1, float max1, float min2, float max2);
	sf::Vector2f GetNormalTo(const sf::Vector2f& point1, const sf::Vector2f& point2);

	sf::Vector2f Normalize2(sf::Vector2f vec);

	void SATTest(const sf::Vector2f& axis, const std::vector<sf::Vector2f>& points, float& minAlong, float& maxAlong);

	//float ConvertRadians(float angle) { return angle * std::numbers::pi / 180; } //DOESNT COMPILE FOR NO REASON TF U MEAN DEJA DEFINI AAAAAAAH

	template <typename T>
	bool Contains(std::vector<T> container, T value) {
		for (T element : container) {
			if (element == value)
				return true;
		}
		return false;
	}


}