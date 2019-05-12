#pragma once
#include <Rectangle.h>
#include <Animation.h>

class Entity
{
public:
	
	Entity();
	Entity(glm::vec2 position);
	Entity(glm::vec2 position, Rectangle hitbox);
	virtual ~Entity();

	virtual void Update(float deltaTime);
	virtual void Draw();

	Rectangle GetHitbox() const;
	void SetHitbox(Rectangle hitbox);
	void SetHitbox(int width, int height);
	void SetHitbox(int x, int y, int width, int height);

	void MoveInDirection(float direction, float speed);
	void CheckCollision(Rectangle collider, float velocity);

	glm::vec2 position;

	NHTV::SpriteBatch::Sprite sprite;

private:

	Rectangle hitbox;

	void HorizontalCollision(Rectangle collider, float velocity);
	void VerticalCollision(Rectangle collider, float velocity);
};