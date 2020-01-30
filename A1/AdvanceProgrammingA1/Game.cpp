#include "Game.h"

Game::Game() : mWindow(sf::VideoMode(640, 480), "GAME3011_A1")
{
	map = new Map();
}

Game::Game(float width, float height, const std::string& tile): mWindow(sf::VideoMode(width, height), tile)
{
	map = new Map(16, 16, 6, 3);
	mode = "SCAN";

	if (!font.loadFromFile("../Font/LemonMilk.otf"))
		std::runtime_error("Font not found");

#pragma region InGame
	switchingBtn = Button("Switch Mode", sf::Vector2f(200.0f, 100.0f), 20, sf::Color::Green, sf::Color::Blue, sf::Color::Black);
	switchingBtn.SetFont(font);
	switchingBtn.SetPosition(sf::Vector2f(1000, 700));

	message.setFont(font);
	message.setFillColor(sf::Color::Magenta);
	message.setCharacterSize(30);
	message.setPosition(sf::Vector2f(1000, 400));
	message.setString(mode + " MODE\n\n\n" + "Number Of Scan: " + std::to_string(numOfScan) + "\n" + "Number Of Extract: " + std::to_string(numOfExtract) + "\n" + "Gold: " + std::to_string(resources));

#pragma endregion

#pragma region Game Over
	restartBtn = Button("Restart", sf::Vector2f(200.0f, 100.0f), 20, sf::Color::Green, sf::Color::Blue, sf::Color::Black);
	restartBtn.SetFont(font);
	restartBtn.SetPosition(sf::Vector2f(100000, 700)); // set the restart butto out of screen at the beginning

	gameResult.setFont(font);
	gameResult.setFillColor(sf::Color::Red);
	gameResult.setCharacterSize(30);
	gameResult.setPosition(sf::Vector2f(900, 450));
#pragma endregion

#pragma region Explanations
	for (int i = 0; i < 4; i++)
	{
		tileSamples.push_back(sf::RectangleShape(sf::Vector2f(50, 50)));
		explanationTexts.push_back(sf::Text("", font, 20));

		tileSamples[i].setPosition(sf::Vector2f(1200, 60 * (i + 1)));
		explanationTexts[i].setPosition(sf::Vector2f(1000, 65 * (i + 1)));
		
	}

	tileSamples[0].setFillColor(sf::Color::Red);
	tileSamples[1].setFillColor(sf::Color::Yellow);
	tileSamples[2].setFillColor(sf::Color::Green);
	tileSamples[3].setFillColor(sf::Color::Cyan);

	explanationTexts[0].setString("2000 gold");
	explanationTexts[0].setFillColor(sf::Color::Red);
	explanationTexts[1].setString("1000 gold");
	explanationTexts[1].setFillColor(sf::Color::Yellow);
	explanationTexts[2].setString("500 gold");
	explanationTexts[2].setFillColor(sf::Color::Green);
	explanationTexts[3].setString("250 gold");
	explanationTexts[3].setFillColor(sf::Color::Cyan);
	
#pragma endregion

}

Game::~Game()
{
	delete map;
}

void Game::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastFrame;
	
	while (mWindow.isOpen())
	{
		timeSinceLastFrame += clock.restart();
		while (timeSinceLastFrame > FPS)
		{
			timeSinceLastFrame -= FPS;
			ProcessEvent();
			Update(FPS);
		}
		Render();
	}
}

void Game::Restart()
{
	map->GetTiles().clear();
	map = new Map(16, 16, 6, 3);
	numOfScan = 6;
	numOfExtract = 3;
	resources = 0;
	isScanning = true;
	mode = "SCAN";
	gameOver = false;
	restartBtn.SetPosition(sf::Vector2f(100000, 700));
}

void Game::ProcessEvent()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{

		case sf::Event::Closed:
			mWindow.close();
			break;

		case sf::Event::KeyPressed:
			KeyboardInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			KeyboardInput(event.key.code, false);
			break;

		case sf::Event::MouseButtonPressed:
			
#pragma region Extract Mode
			if (!isScanning && numOfExtract > 0)
			{
				for (int i = 0; i < map->GetTiles().size(); i++)
				{
					if (map->GetTiles()[i]->IsMouseHover(mWindow))
					{
						numOfExtract--;
						resources += map->GetTiles()[i]->GetCurrentResource();
						map->GetTiles()[i]->Extract();
					}
				}
			}
#pragma endregion

			
#pragma region Scan Mode
			if (isScanning && numOfScan > 0 && numOfExtract > 0)
			{

				for (int i = 0; i < map->GetTiles().size(); i++)
				{
					if (map->GetTiles()[i]->OnMouseClicked(mWindow)) numOfScan--;
				}
			}
#pragma endregion

			
#pragma region Switching Button
			if (switchingBtn.IsMouseHover(mWindow))
			{
				isScanning = !isScanning;
				mode = isScanning ? "SCAN" : "EXTRACT";

				if (switchingBtn.GetBackgroundColor() == sf::Color::Green)
				{
					switchingBtn.SetBackgroudColor(sf::Color::White);
				}
				else
				{
					switchingBtn.SetBackgroudColor(sf::Color::Green);
				}
			}
#pragma endregion

#pragma region Restart Button
			if (restartBtn.IsMouseHover(mWindow))
			{
				Restart();
			}
#pragma endregion

			break;

		default:
			break;
		}
		
	}
}

void Game::Update(sf::Time deltaTime)
{
	if (numOfExtract == 0)
	{
		restartBtn.SetPosition(sf::Vector2f(1000, 700));
		gameResult.setString("Game Over\n\n You collected " + std::to_string(resources) + " gold");
		gameOver = true;
	}

	
	for (int i = 0; i < map->GetTiles().size(); i++)
	{
		map->GetTiles()[i]->Update();
	}
	
	message.setString(mode + " MODE\n\n" + "Number Of Scan: " + std::to_string(numOfScan) + "\n" + "Number Of Extract: " + std::to_string(numOfExtract) + "\n" + "Gold: " + std::to_string(resources));
}

void Game::Render()
{
	mWindow.clear();
	
	for (Tile*& tile : map->GetTiles())
	{
		mWindow.draw(*tile->GetShape());
	}

	if (!gameOver)
	{
		mWindow.draw(message);
		switchingBtn.DrawTo(mWindow);
	}
	else
	{
		mWindow.draw(gameResult);
		restartBtn.DrawTo(mWindow);
	}

	for (int i = 0; i < tileSamples.size(); i++)
	{
		mWindow.draw(tileSamples[i]);
		mWindow.draw(explanationTexts[i]);
	}
	
	mWindow.display();
}

void Game::KeyboardInput(sf::Keyboard::Key keyCode, bool isPressed)
{
	switch (keyCode)
	{
	case sf::Keyboard::Space:
		if (isPressed)
		{
			mode = isScanning ? "SCAN" : "EXTRACT";
			isScanning = !isScanning;
		}
		break;

	default:
		break;
	}
}
