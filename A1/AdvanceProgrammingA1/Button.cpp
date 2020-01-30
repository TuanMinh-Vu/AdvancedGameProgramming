#include "Button.h"


Button::Button()
{
}

Button::Button(std::string btnText, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color hoverColor, sf::Color tColor)
	: size(buttonSize), fontSize(charSize), normalColor(bgColor), hoverColor(hoverColor), textColor(tColor)
{
	button.setSize(size);
	button.setFillColor(normalColor);

	btnWidth = size.x;
	btnHeight = size.y;
	
	text.setString(btnText);
	text.setCharacterSize(fontSize);
	text.setFillColor(textColor);
}

void Button::SetText(std::string t)
{
	text.setString(t);
}

void Button::SetFont(sf::Font& fonts)
{
	text.setFont(fonts);
}

void Button::SetBackgroudColor(sf::Color color)
{
	normalColor = color;
	button.setFillColor(normalColor);
}

void Button::SetTextColor(sf::Color color)
{
	text.setFillColor(color);
}

void Button::SetPosition(sf::Vector2f point)
{
	button.setPosition(point);

	// Center text on button:
	float xPos = (point.x + btnWidth / 2) -(text.getLocalBounds().width / 2);
	float yPos = (point.y + btnHeight / 2.2) -(text.getLocalBounds().height / 2);
	text.setPosition(xPos, yPos);
}

sf::Color Button::GetBackgroundColor() const
{
	return normalColor;
}

void Button::DrawTo(sf::RenderWindow& window)
{
	window.draw(button);
	window.draw(text);
}

// Check if the mouse is within the bounds of the button:
bool Button::IsMouseHover(sf::RenderWindow& window)
{
	int mouseX = sf::Mouse::getPosition(window).x;
	int mouseY = sf::Mouse::getPosition(window).y;

	int btnPosX = button.getPosition().x;
	int btnPosY = button.getPosition().y;

	int btnxPosWidth = button.getPosition().x + btnWidth;
	int btnyPosHeight = button.getPosition().y + btnHeight;

	if (mouseX < btnxPosWidth && mouseX > btnPosX&& mouseY < btnyPosHeight && mouseY > btnPosY) return true;

	return false;
}
