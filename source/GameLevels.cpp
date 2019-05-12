#include "GameLevels.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Ghost.h>
#include <Spawner.h>
#include <Shadow.h>

using namespace std;

int wallTiles[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 16, 17, 18, 19, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 46, 47, 48, 49, 51, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 72, 73, 74, 75, 76, 77, 80 };
int doorTiles[] = { 44, 45, 52, 53 };
int enemyTiles[] = { 82, 83, 84 };
const int stairTile = 20;

const int GRID_WIDTH = 64;
const int GRID_HEIGHT = 64;

const int tilesetWidth = 512;
const int tilesetHeight = 640;

const int itemSheetWidth = 880;
const int itemSheetHeight = 540;

int mapWidth;
int mapHeight;

glm::vec2 playerStartingPosition;

void MapData::SetMap(int level, Player &player, std::vector<Tile*>& map, std::vector<Enemy*>& enemies)
{
	ifstream mapfile("../resources/maps/GauntletDungeon" + to_string(level) + ".txt");

	if (mapfile.good())
	{
		ClearMap(map, enemies);

		string line;

		while (getline(mapfile, line))
		{
			// Set MapWidth and MapHeight //
			if (line == "[header]")
			{
				for (int i = 0; i < 2; i++)
				{
					getline(mapfile, line);
					string number = "";

					for (int c = 6+i; c < line.size(); c++)
						number += line[c];

					if (i == 0) mapWidth = atoi(number.c_str());
					else mapHeight = atoi(number.c_str());
				}
			}

			// Set Tiles and Objects in Map //
			else if (line == "[layer]")
			{
				map.reserve(mapWidth * mapHeight);
				getline(mapfile, line);

				// Tile Layer
				if (line.back() == '1')
				{
					getline(mapfile, line);

					for (int y = 0; y < mapHeight; y++)
					{
						getline(mapfile, line);
						string numberString = "";

						int x = 0;
						for (int c = 0; c < line.size(); c++)
						{
							if (line[c] != ',')
								numberString += line[c];

							// When a Number is Found
							if (line[c] == ',' || c == line.size() - 1)
							{
								int tileNumber = atoi(numberString.c_str());
								numberString = "";

								// SourceRectangle
								int cel = (int)std::floor((tileNumber - 1) * GRID_WIDTH % tilesetWidth);
								int row = (int)std::floor((tilesetHeight - GRID_HEIGHT) - ((tileNumber - 1) * GRID_WIDTH / tilesetWidth * GRID_HEIGHT));
								Rectangle source = { cel, row, GRID_WIDTH, GRID_HEIGHT };

								// Position
								glm::vec2 position = { x * GRID_WIDTH, (mapHeight - 1 - y) * GRID_HEIGHT };

								// Add Tile To Map
								map.push_back(new Tile(position, source, tilesetWidth, tilesetHeight));
								map[0]->SetTileType(Tile::TileType::Floor);

								// Set The Correct Tile Type
								if (IsWallTile(tileNumber))
									map.back()->SetTileType(Tile::TileType::Wall);

								else if (IsDoorTile(tileNumber))
									map.back()->SetTileType(Tile::TileType::Door);

								else if (IsStairsTile(tileNumber))
									map.back()->SetTileType(Tile::TileType::Stairs);
								x++;
							}
						}
					}
				}

				// Object Layer
				if (line.back() == '2')
				{
					getline(mapfile, line);

					for (int y = mapHeight-1; y >= 0; y--)
					{
						getline(mapfile, line);
						string numberString = "";

						int x = -1;
						for (int c = 0; c < line.size(); c++)
						{
							if (line[c] != ',')
								numberString += line[c];

							// When a Number is Found
							if (line[c] == ',' || c == line.size() - 1)
							{
								x++;

								int objectNumber = atoi(numberString.c_str());
								numberString = "";

								switch (objectNumber)
								{
								default: continue;
								case 81:
									playerStartingPosition = { x * GRID_WIDTH, y * GRID_HEIGHT };
									break;
								case 82:
									enemies.push_back(new Ghost(player));
									break;
								case 83:
									enemies.push_back(new Spawner(Spawner::GhostEnemy, player, map, enemies));
									break;
								case 84:
									enemies.push_back(new Shadow(player));
									break;
								case 86:
									{
										PickUp banana = PickUp(PickUp::Food, 30);
										glm::vec4 UVCoords = Rectangle::SourceRectToUVCoords({ 816, 136, 64, 64 }, itemSheetWidth, itemSheetHeight);

										banana.sprite.m_MinUV = UVCoords.xy;
										banana.sprite.m_MaxUV = UVCoords.zw;

										map[GetTileIndex(x, y)]->SetPickUp(banana);
										break;
									}
								case 87:
									{
										PickUp hamburger = PickUp(PickUp::Food, 50);
										glm::vec4 UVCoords = Rectangle::SourceRectToUVCoords({ 816, 68, 64, 64 }, itemSheetWidth, itemSheetHeight);

										hamburger.sprite.m_MinUV = UVCoords.xy;
										hamburger.sprite.m_MaxUV = UVCoords.zw;

										map[GetTileIndex(x, y)]->SetPickUp(hamburger);
										break;
									}
								case 88:
									{
										PickUp chest = PickUp(PickUp::Treasure, 100);
										glm::vec4 UVCoords = Rectangle::SourceRectToUVCoords({ 816, 0, 64, 64 }, itemSheetWidth, itemSheetHeight);

										chest.sprite.m_MinUV = UVCoords.xy;
										chest.sprite.m_MaxUV = UVCoords.zw;

										map[GetTileIndex(x, y)]->SetPickUp(chest);
										break;
									}
								case 89:
									{
										PickUp key = PickUp(PickUp::Key, 1);
										glm::vec4 UVCoords = Rectangle::SourceRectToUVCoords({ 816, 204, 64, 64 }, itemSheetWidth, itemSheetHeight);

										key.sprite.m_MinUV = UVCoords.xy;
										key.sprite.m_MaxUV = UVCoords.zw;

										map[GetTileIndex(x, y)]->SetPickUp(key);
										break;
									}
								}

								if (IsAnEnemy(objectNumber))
									enemies.back()->SetPosition( { x * GRID_WIDTH, y * GRID_HEIGHT } );
							}
						}
					}
				}
			}
		}
	}
}

void MapData::ClearMap(std::vector<Tile*>& map, std::vector<Enemy*>& enemies)
{
	if (map.size() > 0) map.clear();

	if (enemies.size() > 0)
	{
		for (Enemy* enemy : enemies)
			delete enemy;
		enemies.clear();
	}
}


// Get Methods //

int MapData::GetGridWidth() {
	return GRID_WIDTH;
}
int MapData::GetGridHeight() {
	return GRID_HEIGHT;
}
int MapData::GetMapWidth() {
	return mapWidth;
}
int MapData::GetMapHeight() {
	return mapHeight;
}
int MapData::GetTileIndex(int x, int y) {
	return (mapHeight-1 - y) * mapWidth + x;
}

glm::vec2 MapData::GetPlayerStartingPosition() {
	return playerStartingPosition;
}


// Check Methods //

bool MapData::IsWallTile(int number)
{
	return (std::find(std::begin(wallTiles), std::end(wallTiles), number) != std::end(wallTiles));
}

bool MapData::IsDoorTile(int number)
{
	return (std::find(std::begin(doorTiles), std::end(doorTiles), number) != std::end(doorTiles));
}

bool MapData::IsStairsTile(int number)
{
	return number == stairTile;
}

bool MapData::IsAnEnemy(int number)
{
	return std::find(std::begin(enemyTiles), std::end(enemyTiles), number) != std::end(enemyTiles);
}