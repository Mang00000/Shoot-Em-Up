#include "Debug.h"
#include "GameManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include "Utils.h"

Debug* Debug::Get()
{
    static Debug mInstance;
    return &mInstance;
}

void Debug::Draw(sf::RenderWindow* pRenderWindow)
{



    for (sf::RectangleShape& rect : mRectangles)
    {
        pRenderWindow->draw(rect);
    }
    mRectangles.clear();

    for (Line& line : mLines)
    {
        pRenderWindow->draw(&line.start, 2, sf::Lines);
    }
    mLines.clear();

    for (sf::Text& text : mTexts)
    {
        pRenderWindow->draw(text);
    }
    mTexts.clear();
    for (sf::CircleShape& circle : mCircles)
    {
        pRenderWindow->draw(circle);
    }
    mCircles.clear();
}

void Debug::DrawLine(float x1, float y1, float x2, float y2, const sf::Color& color)
{
    Line line;
    line.start = sf::Vertex(sf::Vector2f(x1, y1));
    line.start.color = color;
    line.end = sf::Vertex(sf::Vector2f(x2, y2));
    line.end.color = color;
    Debug::Get()->mLines.push_back(line);
}

void Debug::DrawInfiniteLine(float x, float y, sf::Vector2f direction, const sf::Color& color)
{
    DrawLine(x + direction.x * 10000, y + direction.y * 10000, x - direction.x * 10000, y - direction.y * 10000, color);
}

void Debug::DrawRectangle(float x, float y, float width, float height, const sf::Color& color)
{
    DrawLine(x, y, x + width, y, color);
    DrawLine(x + width, y, x + width, y + height, color);
    DrawLine(x + width, y + height, x, y + height, color);
    DrawLine(x, y + height, x, y, color);
}

void Debug::DrawCircle(float x, float y, float radius, const sf::Color& color)
{
    sf::CircleShape circle;
    circle.setRadius(radius);
    circle.setFillColor(color);
    circle.setPosition(x - radius, y - radius);
    Debug::Get()->mCircles.push_back(circle);
}

void Debug::DrawFilledRectangle(float x, float y, float width, float height, const sf::Color& color)
{
    sf::RectangleShape rect(sf::Vector2f(width, height));
    rect.setFillColor(color);
    rect.setPosition(x, y);
    Debug::Get()->mRectangles.push_back(rect);
}

void Debug::DrawOrientendRectangle(float x, float y, float width, float height, float angle, const sf::Color& color)
{
    float AngleRad = angle * (std::numbers::pi / 180);


    sf::Vector2f Width2 = sf::Vector2f(cos(AngleRad) * width, sin(AngleRad) * width);
    sf::Vector2f Height2 = sf::Vector2f(-sin(AngleRad) * height, cos(AngleRad) * height);


    sf::Vector2f FirstPoint = sf::Vector2f(x - Width2.x /2 - Height2.x /2, y - Width2.y /2 - Height2.y /2);
    float FirstPointX = FirstPoint.x;
    float FirstPointY = FirstPoint.y;

    DrawLine(FirstPointX, FirstPointY, FirstPointX + Width2.x, FirstPointY + Width2.y, sf::Color::White);

    DrawLine(FirstPointX + Width2.x, FirstPointY + Width2.y,
        FirstPointX + Width2.x + Height2.x,
        FirstPointY + Width2.y + Height2.y, color);

    DrawLine(FirstPointX + Width2.x + Height2.x, FirstPointY + Width2.y + Height2.y, FirstPointX + Height2.x, FirstPointY + Height2.y, color);

    DrawLine(FirstPointX +Height2.x, FirstPointY + Height2.y, FirstPointX, FirstPointY, color);
}

void Debug::DrawText(float x, float y, const std::string& text, const sf::Color& color)
{
    DrawText(x, y, text, 0.f, 0.f, color);
}

void Debug::DrawText(float x, float y, const std::string& text, float ratioX, float ratioY, const sf::Color& color)
{
    _ASSERT(ratioX >= 0.f && ratioX <= 1.f);
    _ASSERT(ratioY >= 0.f && ratioY <= 1.f);

    sf::Text sfText;
    sfText.setFont(GameManager::Get()->GetFont());
    sfText.setString(text);
    sfText.setCharacterSize(20);
    sfText.setFillColor(color);
    sfText.setPosition(x, y);

    const sf::FloatRect& bounds = sfText.getLocalBounds();
    sfText.setOrigin(bounds.width * ratioX, bounds.height * ratioY);

    Debug::Get()->mTexts.push_back(sfText);
}