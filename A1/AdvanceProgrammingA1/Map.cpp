#include "Map.h"
#include <iostream>

Map::Map()
{
	row = 16;
	column = 16;
	numOfResourceTiles = 3;
	numOfRingPerResouceTiles = 3;
	Initialize();
	MakeFullMap();
	MakeResourceTiles();
	RemoveOverlapTiles();
	FindAdjecentTiles();
	
}

Map::Map(int row, int column, int resources, int ring) : row(row), column(column), numOfResourceTiles(resources), numOfRingPerResouceTiles(ring)
{
	Initialize();
	MakeFullMap();
	MakeResourceTiles();
	RemoveOverlapTiles();
	FindAdjecentTiles();
	
}

Map::~Map()
{
	for (int i = 0; i < row; i++)
	{
		delete amountResourceGrid[i];
	}
	delete amountResourceGrid;

	for (auto t : tiles)
	{
		delete t;
	}
	tiles.clear();
}

void Map::Initialize()
{
	amountResourceGrid = new int* [row];
	for (int i = 0; i < row; ++i)
	{
		amountResourceGrid[i] = new int[column];
	}
}

void Map::MakeFullMap()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			Tile* tile = new Tile(Tile::States::Minimum, maximumResourcesPerTile, sf::Vector2f(50.0f, 50.0f), 2.0f);
			tile->SetPosition(sf::Vector2f(tile->GetSize().x * i, tile->GetSize().y * j));
			tiles.push_back(tile);
			amountResourceGrid[i][j] = tile->GetCurrentResource();
		}
	}
}

void Map::MakeResourceTiles()
{
	for (int i = 0; i < numOfResourceTiles; i++)
	{
		// pick random tile of the grid
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> randomRow(0, this->row - 1);
		std::uniform_int_distribution<int> randomColumn(0, this->column - 1);
		sf::Vector2i centerPosition = sf::Vector2i(randomRow(mt), randomColumn(mt));

		// spawn center tile
		Tile* tile = new Tile(Tile::States::Maximum, maximumResourcesPerTile, sf::Vector2f(50.0f, 50.0f), 2.0f);
		tile->SetPosition(sf::Vector2f(tile->GetSize().x * centerPosition.x, tile->GetSize().y * centerPosition.y));
		amountResourceGrid[centerPosition.x][centerPosition.y] = tile->GetCurrentResource();
		tiles.push_back(tile);

		// rings
		MakeTilesRings(tile, centerPosition);
	}
	
}

void Map::MakeTilesRings(Tile* centerTile, sf::Vector2i center)
{
	for (int i = 1; i < numOfRingPerResouceTiles; i++)
	{
		for (int row = -1 * i; row <= 1 * i; row++)
		{
			for (int col = -1 * i; col <= 1 * i; col++)
			{
				int nextRow = center.x + row;
				int nextColumn = center.y + col;

				if (nextColumn < this->column && nextRow < this->row && nextColumn >= 0 && nextRow >= 0) // is the next tile still inside the map?
				{
					// is the current tile empty or has the resource than the new one?
					if (amountResourceGrid[nextRow][nextColumn] == NULL || amountResourceGrid[nextRow][nextColumn] < maximumResourcesPerTile / (2 * i))
					{
						Tile* tile = new Tile(static_cast<Tile::States>(Tile::States::Maximum + i), maximumResourcesPerTile, sf::Vector2f(50.0f, 50.0f), 2.0f);
						tile->SetPosition(sf::Vector2f(tile->GetSize().x * nextRow, tile->GetSize().y * nextColumn));
						amountResourceGrid[nextRow][nextColumn] = tile->GetCurrentResource();
						tiles.push_back(tile);
					}

				}
				
			}
		}
	}
}

void Map::FindAdjecentTiles()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles.size(); j++)
		{
			// optimize this later
			if (   (tiles[j]->GetPosition().x == tiles[i]->GetPosition().x && tiles[j]->GetPosition().y == tiles[i]->GetPosition().y + tiles[i]->GetSize().y)
				|| (tiles[j]->GetPosition().x == tiles[i]->GetPosition().x && tiles[j]->GetPosition().y == tiles[i]->GetPosition().y - tiles[i]->GetSize().y)
				|| (tiles[j]->GetPosition().y == tiles[i]->GetPosition().y && tiles[j]->GetPosition().x == tiles[i]->GetPosition().x + tiles[i]->GetSize().x)
				|| (tiles[j]->GetPosition().y == tiles[i]->GetPosition().y && tiles[j]->GetPosition().x == tiles[i]->GetPosition().x - tiles[i]->GetSize().x)
				|| (tiles[j]->GetPosition().y == tiles[i]->GetPosition().y + tiles[i]->GetSize().y && tiles[j]->GetPosition().x == tiles[i]->GetPosition().x + tiles[i]->GetSize().x)
				|| (tiles[j]->GetPosition().y == tiles[i]->GetPosition().y + tiles[i]->GetSize().y && tiles[j]->GetPosition().x == tiles[i]->GetPosition().x - tiles[i]->GetSize().x)
				|| (tiles[j]->GetPosition().y == tiles[i]->GetPosition().y - tiles[i]->GetSize().y && tiles[j]->GetPosition().x == tiles[i]->GetPosition().x + tiles[i]->GetSize().x)
				|| (tiles[j]->GetPosition().y == tiles[i]->GetPosition().y - tiles[i]->GetSize().y && tiles[j]->GetPosition().x == tiles[i]->GetPosition().x - tiles[i]->GetSize().x))
			{
				tiles[i]->AddAdjacentTiles(tiles[j]);
			}

		}
	}

}

void Map::RemoveOverlapTiles()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles.size(); j++)
		{
			if (tiles[i]->GetPosition() == tiles[j]->GetPosition() && i != j)
			{
				if (tiles[i]->GetCurrentResource() > tiles[j]->GetCurrentResource()) tiles.erase(tiles.begin() + j);
				else
				{
					tiles.erase(tiles.begin() + i);
					//break;
				};
			}

		}
	}
}

std::vector<Tile*> Map::GetTiles()
{
	return tiles;
}
