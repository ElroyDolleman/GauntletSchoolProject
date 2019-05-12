#pragma once
#include <glm/glm.hpp>

struct Rectangle
{
public:

	// Constructor
	Rectangle(int x = 0, int y = 0, int width = 0, int height = 0);

	// Fields
	int x, y;
	int width, height;

	// Static Methods
	static Rectangle Empty();
	static Rectangle Intersect(Rectangle r1, Rectangle r2);
	static Rectangle Union(Rectangle r1, Rectangle r2);
	static Rectangle Create(glm::vec2 bottomLeft, glm::vec2 topRight);
	static Rectangle Create(int left, int bottom, int right, int top);
	static glm::vec4 SourceRectToUVCoords(Rectangle source, int texWidth, int texHeight);

	// Get Set Methods
	int GetTop() const;
	int GetBottom() const;
	int GetLeft() const;
	int GetRight() const;
	glm::vec2 GetCenter() const;
	glm::vec2 GetLocation() const;
	glm::vec2 GetTopRightCorner() const;
	void SetLocation(glm::vec2 location);

	// Checks
	bool Contains(int x, int y) const;
	bool Contains(glm::vec2 position) const;
	bool Intersects(Rectangle rect) const;

	bool CollidesOnLeftOf(Rectangle collider, float velocity);
	bool CollidesOnRightOf(Rectangle collider, float velocity);
	bool CollidesOnTopOf(Rectangle collider, float velocity);
	bool CollidesOnBottomOf(Rectangle collider, float velocity);

	// Operator Overloading
	bool operator== (Rectangle rect);
	bool operator!= (Rectangle rect);
};