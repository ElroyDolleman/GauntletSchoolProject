#pragma once

#include "Player.h"

class Enemy : public Entity
{
public:

	Enemy(Player& player);

	virtual void Update(float deltaTime);
	void MoveTowards(float posX, float posY, float deltaTime);
	void MoveTowards(glm::vec2 position, float deltaTime);
	virtual void Attacked(float power);

	float GetHealth() const;
	float GetMaxHealth() const;
	float GetPower() const;
	int GetPoints() const;
	float GetSpeed() const;
	virtual bool IsInteractable() const;

	virtual void SetPosition(glm::vec2 position);
	virtual void HitPlayer();

protected:

	float resistance;
	float health;
	float power;
	float speed;
	int points;

	Animation animation;
	glm::vec2 direction;

	int GetStartFrame(glm::vec2 direction) const;
	Player& GetPlayer() const;

	void SetHealth(float maxHealth);
	float DistanceTo(glm::vec2 pos) const;

private:

	float maxHealth;

	Player* player;
};