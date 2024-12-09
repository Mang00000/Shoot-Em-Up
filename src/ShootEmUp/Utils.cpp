#include <SFML/System/Vector2.hpp>

#include <cmath>

namespace Utils 
{
    bool Normalize(sf::Vector2f& vector)
    {
        float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);

		if (magnitude != 0)
		{
			vector.x /= magnitude;
			vector.y /= magnitude;
		
			return true;
		}

		return false;
    }

	float GetDistance(int x1, int y1, int x2, int y2)
	{
		int x = x2 - x1;
		int y = y2 - y1;

		return std::sqrt(x * x + y * y);
	}
    float AngleBetween(const sf::Vector2f& v1, const sf::Vector2f& v2) {
        float dot = v1.x * v2.x + v1.y * v2.y;
        float det = v1.x * v2.y - v1.y * v2.x;
        return std::atan2(det, dot);
    }

    sf::Vector2f RotateVector(const sf::Vector2f& vector, float angle) {
        float cosA = std::cos(angle);
        float sinA = std::sin(angle);
        return sf::Vector2f(
            vector.x * cosA - vector.y * sinA,
            vector.x * sinA + vector.y * cosA
        );
    }
}
