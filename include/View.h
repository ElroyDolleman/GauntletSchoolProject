#pragma once

#include <Rectangle.h>

class View
{
public:

	View(Rectangle map, Rectangle screen);

	Rectangle GetScreenArea() const;
	Rectangle GetMapArea() const;
	glm::vec2 GetScreenPosition() const;
	glm::vec2 GetScreenCenter() const;
	
	void SetPosition(glm::vec2 position);
	void SetCenterPosition(glm::vec2 center);
	void Move(glm::vec2 translation);
	void Move(int x, int y);

	glm::vec2 InScreenPosition(glm::vec2 worldPosition) const;

private:

	Rectangle screenArea;
	Rectangle mapArea;
};