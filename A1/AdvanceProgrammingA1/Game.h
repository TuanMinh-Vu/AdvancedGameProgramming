#pragma once
#include "SFML/Graphics.hpp"
#include "Map.h"
#include "Button.h"
#include <iostream>

class Game
{
public:
	Game();
	Game(float width, float height, const std::string& title);
	~Game();
	void Run();
	void Restart();

private:
	void ProcessEvent();
	void Update(sf::Time deltaTime);
	void Render();
	void KeyboardInput(sf::Keyboard::Key keyCode, bool isPressed);
	sf::RenderWindow mWindow;
	Map* map;
	const sf::Time FPS = sf::seconds(1.0f / 60.0f);
	int numOfScan = 6;
	int numOfExtract = 3;
	unsigned int resources = 0;
	bool isScanning = true;
	bool gameOver = false;
	std::string mode;
	sf::Font font;
	Button switchingBtn;
	sf::Text message;

#pragma region Game Over Panel;
	Button restartBtn;
	sf::Text gameResult;
#pragma endregion

};

