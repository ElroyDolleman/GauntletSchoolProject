#pragma once

#include "Rectangle.h"
#include <SpriteBatch.h>
#include <PickUp.h>
#include <Enemy.h>

class Tile
{
public:

	enum TileType
	{
		Floor,
		Wall,
		Stairs,
		Door
	};

	Tile();
	Tile(glm::vec2 position, Rectangle source, int tilesetWidth, int tilesetHeight);
	~Tile();

	// Set Methods
	void SetPickUp(PickUp pickUp);
	void SetEnemyRef(Enemy& enemy);
	void SetTileType(TileType tileType);

	// Get Methods
	const PickUp GetPickUp() const;
	const Enemy& GetEnemy() const;
	Rectangle GetHitbox() const;
	NHTV::SpriteBatch::Sprite GetSprite() const;
	glm::vec2 GetPosition() const;

	// Delete Methods
	void DeletePickUp();
	void DeleteEnemyRef();

	// Checks Methods
	bool IsSolid() const;
	bool IsStairs() const;
	bool IsDoor() const;
	bool ContainsPickUp() const;
	bool ContainsEnemy() const;
	bool IsEmpty() const;

	// Other Methods
	void CopyTile(const Tile tile);

	NHTV::SpriteBatch::Sprite sprite;

private:

	TileType tileType;

	glm::vec2 position;
	int width, height;

	PickUp* pickUp;
	Enemy* enemy;

	
};