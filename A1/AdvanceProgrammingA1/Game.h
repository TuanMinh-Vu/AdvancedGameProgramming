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
	bool isScanning = true;
	sf::Font font;
	Button switchingBtn;
	sf::Text message;
};

