#pragma once
#include <Enemy.h>
#include <Tile.h>
#include <Player.h>

class Spawner : public Enemy
{
public:

	enum SpawnableEnemies
	{
		GhostEnemy
	};

	Spawner(SpawnableEnemies, Player&, std::vector<Tile*>& map, std::vector<Enemy*>& enemies);
	~Spawner();

	void Update(float deltaTime);
	void Attacked(float power);
	void HitPlayer();
	bool IsInteractable() const;

	void SetPosition(glm::vec2 position);

private:

	float timer;

	std::vector<Tile*>& map;
	std::vector<Enemy*>& enemies;

	float GetSpawnTime();

	void SpawnEnemy(int gridX, int gridY);
	bool IsSpawnablePlace(int gridX, int gridY) const;
}; 