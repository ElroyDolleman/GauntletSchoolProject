#include "Rectangle.h"
#include <cmath>
#include <iostream>

Rectangle::Rectangle(int x, int y, int width, int height)
	: x(x), y(y), width(width), height(height)
{ }


// Static Methods //

Rectangle Rectangle::Empty() {
	return Rectangle();
}

Rectangle Rectangle::Intersect(Rectangle r1, Rectangle r2)
{
	int left = (int)std::fmax(r1.GetLeft(), r2.GetLeft());
	int right = (int)std::fmin(r1.GetRight(), r2.GetRight());
	int bottom = (int)std::fmax(r1.GetBottom(), r2.GetBottom());
	int top = (int)std::fmin(r1.GetTop(), r2.GetTop());

	return Create(left, bottom, right, top);
}

Rectangle Rectangle::Union(Rectangle r1, Rectangle r2)
{
	int left = (int)std::fmin(r1.GetLeft(), r2.GetLeft());
	int right = (int)std::fmax(r1.GetRight(), r2.GetRight());
	int bottom = (int)std::fmin(r1.GetBottom(), r2.GetBottom());
	int top = (int)std::fmax(r1.GetTop(), r2.GetTop());

	return Create(left, bottom, right, top);
}

Rectangle Rectangle::Create(glm::vec2 bottomLeft, glm::vec2 topRight) {
	return Create((int)bottomLeft.x, (int)bottomLeft.y, (int)topRight.x, (int)topRight.y);
}
Rectangle Rectangle::Create(int left, int bottom, int right, int top) {
	return{ left, bottom, right - left, top - bottom };
}

glm::vec4 Rectangle::SourceRectToUVCoords(Rectangle source, int texWidth, int texHeight) {
	return{ (float)source.x / (float)texWidth, (float)source.y / (float)texHeight, (float)source.GetRight() / (float)texWidth, (float)source.GetTop() / (float)texHeight };
}


// Get Set Methods

int Rectangle::GetTop() const { return y + height; }
int Rectangle::GetBottom() const { return y; }
int Rectangle::GetLeft() const { return x; }
int Rectangle::GetRight() const { return x + width; }

glm::vec2 Rectangle::GetTopRightCorner() const {
	return{ x + width, y + height };
}

glm::vec2 Rectangle::GetCenter() const {
	return glm::vec2(x + width / 2, y + height / 2);
}

glm::vec2 Rectangle::GetLocation() const {
	return glm::vec2(x, y);
}
void Rectangle::SetLocation(glm::vec2 location) {
	x = (int)location.x;
	y = (int)location.y;
}


// Checks

bool Rectangle::Contains(int x, int y) const
{
	return x > GetLeft() && x < GetRight() && y > GetBottom() && y < GetTop();
}
bool Rectangle::Contains(glm::vec2 position) const {
	return Contains((int)position.x, (int)position.y);
}

bool Rectangle::Intersects(Rectangle rect) const
{
	return rect.GetRight() > this->GetLeft() && rect.GetLeft() < this->GetRight() &&
		rect.GetTop() > this->GetBottom() && rect.GetBottom() < this->GetTop();
}

bool Rectangle::CollidesOnLeftOf(Rectangle collider, float velocity)
{
	return this->GetRight() >= collider.GetLeft() &&
		this->GetRight() <= collider.GetLeft() + std::ceil(velocity) &&
		this->GetBottom() < collider.GetTop() &&
		this->GetTop() > collider.GetBottom();
}

bool Rectangle::CollidesOnRightOf(Rectangle collider, float velocity)
{
	return this->GetLeft() <= collider.GetRight() &&
		this->GetLeft() >= collider.GetRight() - std::ceil(velocity) &&
		this->GetBottom() < collider.GetTop() &&
		this->GetTop() > collider.GetBottom();
}

bool Rectangle::CollidesOnTopOf(Rectangle collider, float velocity)
{
	return this->GetBottom() <= collider.GetTop() &&
		this->GetBottom() >= collider.GetTop() - std::ceil(velocity) &&
		this->GetRight() > collider.GetLeft() &&
		this->GetLeft() < collider.GetRight();
}

bool Rectangle::CollidesOnBottomOf(Rectangle collider, float velocity)
{
	return this->GetTop() >= collider.GetBottom() &&
		this->GetTop() <= collider.GetBottom() + std::ceil(velocity) &&
		this->GetRight() > collider.GetLeft() &&
		this->GetLeft() < collider.GetRight();
}


// Operator Overloading

bool Rectangle::operator==(Rectangle rect) {
	return this->x == rect.x && this->y == rect.y && rect.width == this->width && rect.height == this->height;
}
bool Rectangle::operator!=(Rectangle rect) {
	return !(rect == *this);
}

