#pragma once
#include "Tile.h"
#include <random>

class Map
{
public:
	Map();
	Map(int row, int  column, int resources, int ring);
	~Map();

	std::vector<Tile*> GetTiles();

private:

#pragma region Private Variables
	int row;
	int column;
	int numOfResourceTiles;
	int numOfRingPerResouceTiles;
	int** amountResourceGrid;
	static const int maximumResourcesPerTile = 2000;
	std::vector<Tile*> tiles;
	
#pragma endregion

#pragma region Private Methods
	void Initialize();
	void MakeFullMap();
	void MakeResourceTiles();
	void MakeTilesRings(Tile* centerTile, sf::Vector2i center);
	void FindAdjecentTiles();
#pragma endregion

};

