#pragma once
#include "SFML/Graphics.hpp"
#include "Map.h"
#include "Button.h"

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
	const sf::Time FPS = sf::seconds(1.0f / 60.0f);
	sf::Font font;

	bool gameOver = false;

#pragma region InGame Varables
	Map* map;
	int numOfScan = 6;
	int numOfExtract = 3;
	unsigned int resources = 0;
	bool isScanning = true;
	std::string mode;
	Button switchingBtn;
	sf::Text message;

	std::vector<sf::RectangleShape> tileSamples;
	std::vector<sf::Text> explanationTexts;
#pragma endregion

#pragma region Game Over Panel;
	Button restartBtn;
	sf::Text gameResult;
#pragma endregion

};

