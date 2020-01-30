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

	switchingBtn = Button("Switch Mode", sf::Vector2f(200.0f, 100.0f), 20, sf::Color::Green, sf::Color::Blue, sf::Color::Black);
	switchingBtn.SetFont(font);
	switchingBtn.SetPosition(sf::Vector2f(1000, 700));

	message.setFont(font);
	message.setFillColor(sf::Color::Red);
	message.setCharacterSize(20);
	message.setPosition(sf::Vector2f(1000, 500));
	message.setString(mode + " MODE\n\n" + "Number Of Scan: " + std::to_string(numOfScan) + "\n" + "Number Of Extract: " + std::to_string(numOfExtract) + "\n" + "Resources: " + std::to_string(resources));

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
		//message.setString(numOfScan);
		Render();
	}
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
					if (map->GetTiles()[i]->OnMouseClicked(mWindow))
					{
						numOfExtract--;
						resources += map->GetTiles()[i]->GetCurrentResource();
						map->GetTiles()[i]->Extract();
					}
				}
			}
#pragma endregion

			
#pragma region Scan Mode
			if (isScanning && numOfScan > 0)
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

			break;

		default:
			break;
		}
		
	}
}

void Game::Update(sf::Time deltaTime)
{
	for (int i = 0; i < map->GetTiles().size(); i++)
	{
		map->GetTiles()[i]->Update();
	}
	
	message.setString(mode + " MODE\n\n" + "Number Of Scan: " + std::to_string(numOfScan) + "\n" + "Number Of Extract: " + std::to_string(numOfExtract) + "\n" + "Resources: " + std::to_string(resources));
}

void Game::Render()
{
	mWindow.clear();
	
	for (Tile*& tile : map->GetTiles())
	{
		mWindow.draw(*tile->GetShape());
	}

	mWindow.draw(message);
	switchingBtn.DrawTo(mWindow);
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
