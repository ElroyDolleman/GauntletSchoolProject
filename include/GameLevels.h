#pragma once

#include <vector>
#include <Tile.h>
#include <Enemy.h>
#include <Player.h>

class MapData
{
public:

	static void SetMap(int level, Player &player, std::vector<Tile*>& map, std::vector<Enemy*>& enemies);
	static void ClearMap(std::vector<Tile*>& map, std::vector<Enemy*>& enemies);

	static int GetGridWidth();
	static int GetGridHeight();
	static int GetMapWidth();
	static int GetMapHeight();
	static int GetTileIndex(int x, int y);

	static glm::vec2 GetPlayerStartingPosition();

private:

	static bool IsWallTile(int number);
	static bool IsDoorTile(int number);
	static bool IsStairsTile(int number);
	static bool IsAnEnemy(int number);
};