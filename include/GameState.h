#pragma once

#include <Tile.h>
#include <State.h>
#include <player.h>
#include <Enemy.h>
#include <view.h>
#include <GameUI.h>

class GameState : public State
{
public:

	GameState();
	~GameState();

	void Update(float deltaTime);
	void Draw();

	static void SetPlayableCharacter(Player::Character);

private:

	void Initialize();

	std::vector<Tile*> map;
	std::vector<Enemy*> enemies;

	Player* player;
	View* view;

	NHTV::SpriteBatch* playerBatch;
	NHTV::SpriteBatch* enemyBatch;
	NHTV::SpriteBatch* tilesBatch;
	NHTV::SpriteBatch* gameUIBatch;

	GameUI* gameUI;
	int currentLevel;
	bool levelComplete;

	// Update Methods
	void UpdateCollisionCheck(float deltaTime);
	void UpdateView();
	void UpdateEnemies(float deltaTime);

	// Get Methods
	glm::vec2 ToGridLocation(glm::vec2 position);

	Tile& GetTile(int x, int y);
	Tile& GetTile(glm::vec2 position);
	Tile& GetPlayerTile();
	Tile& GetEnemyTile(const Enemy& enemy);

	void TileCoordsInRectangle(glm::vec2 &beginPos, glm::vec2 &endPos, Rectangle rect);
	Rectangle GetCollider(Rectangle collider, Rectangle hitbox);

	// Check Methods
	bool BulletCollidesWith(Rectangle collider);
};