#include "View.h"

View::View(Rectangle map, Rectangle screen)
	: mapArea(map), screenArea(screen)
{

}

Rectangle View::GetScreenArea() const
{
	return screenArea;
}

Rectangle View::GetMapArea() const
{
	return mapArea;
}

glm::vec2 View::GetScreenPosition() const
{
	return { screenArea.x, screenArea.y };
}

glm::vec2 View::GetScreenCenter() const
{
	return screenArea.GetCenter();
}

void View::SetPosition(glm::vec2 position)
{
	if (position.x < mapArea.x) 
		position.x = mapArea.x;
	else if (position.x + screenArea.width > mapArea.GetRight()) 
		position.x = mapArea.GetRight() - screenArea.width;

	if (position.y < mapArea.y)
		position.y = mapArea.y;
	else if (position.y + screenArea.height > mapArea.GetTop())
		position.y = mapArea.GetTop() - screenArea.height;

	screenArea.x = (int)position.x;
	screenArea.y = (int)position.y;
}

void View::SetCenterPosition(glm::vec2 center)
{
	SetPosition({ center.x - screenArea.width * .5f, center.y - screenArea.height * .5f });
}

void View::Move(glm::vec2 translation)
{
	screenArea.x += (int)translation.x;
	screenArea.x += (int)translation.y;
}

void View::Move(int x, int y)
{
	screenArea.x += x;
	screenArea.x += y;
}

glm::vec2 View::InScreenPosition(glm::vec2 worldPosition) const
{
	return{ std::round(worldPosition.x - screenArea.x), std::round(worldPosition.y - screenArea.y) };
}
