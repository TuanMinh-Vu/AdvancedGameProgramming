#include "Tile.h"

Tile::Tile(States startState, int maxResource, sf::Vector2f s, float o) : isFacingUp(true), currentState(startState)
   , maximumResources(maxResource), size(s), outline(o)
{
	Initialize();
}

Tile::~Tile()
{
	/*for (auto t : adjacentTiles)
	{
		delete t;
	}*/
		
   // adjacentTiles.clear();

	delete shape;
}


sf::RectangleShape* Tile::GetShape() const
{
	return shape;
}

int Tile::GetCurrentResource() const
{
	return currentResources;
}

void Tile::SetPosition(sf::Vector2f p)
{
	shape->setPosition(p);
}

sf::Vector2f Tile::GetSize() const
{
	return shape->getSize();
}

void Tile::Update()
{
	UpdateState();
	UpdateResources();
	UpdateColor();
}

void Tile::Initialize()
{
	shape = new sf::RectangleShape(sf::Vector2f(size.x, size.y));
	shape->setOutlineThickness(-outline); // make sure the outline is rendered inside the tile, so it won't overlap other tiles
	shape->setOutlineColor(sf::Color::Black);
	UpdateState();
	UpdateResources();
	UpdateColor();
}

void Tile::UpdateState()
{

}

void Tile::UpdateResources()
{
	switch (currentState)
	{
	case Maximum:
		currentResources = maximumResources;
		break;

	case Half:
		currentResources = maximumResources / 2;
		break;

	case Quarter:
		currentResources = maximumResources / 4;
		break;

	case Minimum:
		currentResources = maximumResources /8;
		break;

	case Empty:
		currentResources = 0;
		break;

	default:
		break;
	}
}

void Tile::UpdateColor()
{
	if (!isFacingUp) shape->setFillColor(sf::Color::White);
	else
	{
		switch (currentState)
		{
		case Maximum:
			currentColor = sf::Color::Red;
			break;

		case Half:
			currentColor = sf::Color::Yellow;
			break;

		case Quarter:
			currentColor = sf::Color::Green;
			break;

		case Minimum:
			currentColor = sf::Color::Cyan;
			break;

		case Empty:
			currentColor = sf::Color::Blue;
			break;

		default:
			break;
		}
		shape->setFillColor(currentColor);
	}
}

int Tile::GetResourceAtState(States s) const
{
	switch (s)
	{
	case Maximum:
		return maximumResources;
		break;

	case Half:
		return maximumResources / 2;
		break;

	case Quarter:
		return maximumResources / 4;
		break;

	case Minimum:
		return maximumResources / 8;
		break;

	case Empty:
		return 0;
		break;

	default:
		break;
		return 0;
	}

}

void Tile::AddAdjacentTiles(Tile* t)
{
	adjacentTiles.push_back(t);
}

void Tile::OnMouseClicked(sf::Vector2f mousePosition)
{

}