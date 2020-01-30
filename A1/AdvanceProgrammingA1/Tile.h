#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Tile
{
public:

	enum States
	{
		Maximum,
		Half,
		Quarter,
		Minimum,
		Empty,
	};

	Tile(States startState, int maxResource, sf::Vector2f size, float o);
	~Tile();
	sf::RectangleShape* GetShape() const;
	sf::Vector2f GetSize() const;

#pragma region Public Methods
	int GetCurrentResource() const;
	void SetPosition(sf::Vector2f p);
	void Update();
	int GetResourceAtState(States s) const;
	void AddAdjacentTiles(Tile* t);
	void OnMouseClicked(sf::RenderWindow& window);
	bool IsMouseOver(sf::RenderWindow& window);
#pragma endregion

	

private:

#pragma region Private Variables
	const int maximumResources;
	bool isFacingUp;
	int currentResources;
	States currentState;
	sf::Color currentColor;
	sf::RectangleShape* shape;
	sf::Vector2f size;
	float outline;
	std::vector<Tile*> adjacentTiles;
#pragma endregion

	
#pragma region Private Methods
	void Initialize();
	void UpdateState();
	void UpdateResources();
	void UpdateColor();
#pragma endregion


};

