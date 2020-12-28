#include "Button.h"

Button::Button(float t_X, float t_Y) {
	this->hoverCursor.loadFromSystem(sf::Cursor::Hand);
	this->defaultCursor.loadFromSystem(sf::Cursor::Arrow);
	sf::Color color(86, 27, 174);
	shape.setOrigin({ buttonWidth / 2, buttonHeight / 2 });
	shape.setPosition(t_X, t_Y);
	shape.setSize({ buttonWidth, buttonHeight });
	shape.setFillColor(color);
}

float Button::left() {
	return shape.getPosition().x - buttonWidth/2;
}
float Button::right() {
	return shape.getPosition().x + buttonWidth / 2;
}
float Button::top() {
	return shape.getPosition().y - buttonHeight / 2;
}
float Button::bottom() {
	return shape.getPosition().y + buttonHeight / 2;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(shape);
}

bool Button::isPressed(sf::RenderWindow& w) {
	if (isHovered(w) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		return true;
	}
	else {
		return false;
	}
	
}
bool Button::isHovered(sf::RenderWindow& w) {
	if (sf::Mouse::getPosition(w).x > left() &&
		sf::Mouse::getPosition(w).x < right() &&
		sf::Mouse::getPosition(w).y > top() &&
		sf::Mouse::getPosition(w).y < bottom()) {

		shape.setFillColor({ 53, 15, 109 });
		return true;
	}

	else {
		shape.setFillColor({ 86, 27, 174 });
		return false;
	}
}