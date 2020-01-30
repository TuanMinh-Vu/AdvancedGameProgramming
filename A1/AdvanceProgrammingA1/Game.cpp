#include "Game.h"

Game::Game() : mWindow(sf::VideoMode(640, 480), "GAME3011_A1")
{
	map = new Map();
}

Game::Game(float width, float height, const std::string& tile): mWindow(sf::VideoMode(width, height), tile)
{
	map = new Map(16, 16, 6, 3);
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
			for (int i = 0; i < map->GetTiles().size(); i++)
			{
				map->GetTiles()[i]->OnMouseClicked(mWindow);
			}
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

}

void Game::Render()
{
	mWindow.clear();
	
	for (Tile*& tile : map->GetTiles())
	{
		mWindow.draw(*tile->GetShape());
	}
	mWindow.display();
}

void Game::KeyboardInput(sf::Keyboard::Key keyCode, bool isPressed)
{
	switch (keyCode)
	{
	case sf::Keyboard::A:
		break;

	default:
		break;
	}
}
