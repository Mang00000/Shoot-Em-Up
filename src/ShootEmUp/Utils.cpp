#include <SFML/System/Vector2.hpp>

#include <cmath>
#include "Utils.h"

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

    float Dot(const sf::Vector2f& v1, const sf::Vector2f& v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    sf::Vector2f RotateVector(const sf::Vector2f& vector, float angle) {
        float cosA = std::cos(angle);
        float sinA = std::sin(angle);
        return sf::Vector2f(
            vector.x * cosA - vector.y * sinA,
            vector.x * sinA + vector.y * cosA
        );
    }
    bool IsBetweenOrdered(float value, float lowerBound, float upperBound)
    {
        return lowerBound <= value && value <= upperBound;
    }

    bool Overlaps(float min1, float max1, float min2, float max2)
    {
        return IsBetweenOrdered(min2, min1, max1) || IsBetweenOrdered(min1, min2, max2);
    }

    sf::Vector2f GetNormalTo(const sf::Vector2f& point1, const sf::Vector2f& point2)
    {
        float dx = point2.x - point1.x;
        float dy = point2.y - point1.y;

        sf::Vector2f Normals = sf::Vector2f(-dy,dx);

        return Normals;
    }

    sf::Vector2f Normalize2(sf::Vector2f vec)
    {
        float magnitude = std::sqrt(vec.x * vec.x + vec.y * vec.y);

        vec.x /= magnitude;
        vec.y /= magnitude;

        return vec;
    }
    void SATTest(const sf::Vector2f& axis, const std::vector<sf::Vector2f>& points, float& minAlong, float& maxAlong)
    {
        minAlong = 10000;
        maxAlong = -10000;
        for (int i = 0; i < points.size(); i++) {
            float dotVal = Utils::Dot(points[i], axis);
            if (dotVal < minAlong)  minAlong = dotVal;
            if (dotVal > maxAlong)  maxAlong = dotVal;
        }
    }
}
