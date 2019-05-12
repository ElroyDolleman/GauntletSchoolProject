#include "Entity.h"
#include <iostream>

Entity::Entity()
{
}

Entity::Entity(glm::vec2 position)
	: position(position)
{
}

Entity::Entity(glm::vec2 position, Rectangle hitbox)
	: position(position), hitbox(hitbox)
{
}

Entity::~Entity()
{
}

void Entity::Update(float deltaTime)
{
}

void Entity::Draw()
{
}

Rectangle Entity::GetHitbox() const {
	return { (int)std::round(position.x) + hitbox.x, (int)std::round(position.y) + hitbox.y, hitbox.width, hitbox.height };
}
void Entity::SetHitbox(Rectangle hitbox) {
	this->hitbox = hitbox;
}
void Entity::SetHitbox(int width, int height)
{
	hitbox.width = width;
	hitbox.height = height;
}
void Entity::SetHitbox(int x, int y, int width, int height) {
	hitbox = { x, y, width, height };
}

void Entity::MoveInDirection(float direction, float speed)
{
	position.x += (float)std::cos(direction) * speed;
	position.y += (float)std::sin(direction) * speed;
}

void Entity::CheckCollision(Rectangle collider, float velocity)
{
	Rectangle overlap = Rectangle::Intersect(GetHitbox(), collider);

	float widht = 1 / hitbox.width * overlap.width;
	float height = 1 / hitbox.height * overlap.height;

	if (height > widht)
	{
		HorizontalCollision(collider, velocity);
		VerticalCollision(collider, velocity);
	}
	else
	{
		VerticalCollision(collider, velocity);
		HorizontalCollision(collider, velocity);
	}
}

void Entity::HorizontalCollision(Rectangle collider, float velocity)
{
	if (GetHitbox().CollidesOnLeftOf(collider, velocity))
		position.x = collider.GetLeft() - hitbox.width;
	if (GetHitbox().CollidesOnRightOf(collider, velocity))
		position.x = collider.GetRight();
}

void Entity::VerticalCollision(Rectangle collider, float velocity)
{
	if (GetHitbox().CollidesOnBottomOf(collider, velocity))
		position.y = collider.GetBottom() - hitbox.height;
	if (GetHitbox().CollidesOnTopOf(collider, velocity))
		position.y = collider.GetTop();
}
