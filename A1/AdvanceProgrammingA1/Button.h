#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Button 
{
public:
	Button();
	Button(std::string btnText, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color hoverColor, sf::Color textColor);

	void SetText(std::string text);

	void SetFont(sf::Font& fonts);

	void SetBackgroudColor(sf::Color color);

	void SetTextColor(sf::Color color);

	void SetPosition(sf::Vector2f point);

	sf::Color GetBackgroundColor() const;

	void DrawTo(sf::RenderWindow& window);

	bool IsMouseHover(sf::RenderWindow& window);

private:

	sf::RectangleShape button;
	sf::Text text;
	sf::Vector2f size;
	int fontSize;
	sf::Color normalColor;
	sf::Color hoverColor;
	sf::Color textColor;
	int btnWidth;
	int btnHeight;
};
