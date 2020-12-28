#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(float t_X, float t_Y) {
	shape.setSize({ this->bulletWidth,  this->bulletHeight });
	shape.setFillColor(sf::Color::White);
	shape.setOrigin({ bulletWidth/2,bulletHeight/2 });
	shape.setPosition(t_X, t_Y);
}

void PlayerBullet::update() {
	this->shape.move(velocity);
}

void PlayerBullet::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->shape);
}

void PlayerBullet::setPosition(sf::Vector2f pos) {
	this->shape.setPosition(pos);
}

float PlayerBullet::left() {
	return this->shape.getPosition().x - bulletWidth / 2;
}
float PlayerBullet::right() {
	return this->shape.getPosition().x + bulletWidth / 2;
}
float PlayerBullet::top() {
	return this->shape.getPosition().y - bulletHeight / 2;
}
float PlayerBullet::bottom() {
	return this->shape.getPosition().y + bulletHeight / 2;
}

void PlayerBullet::create() {
	this->destroyed = false;
}

void PlayerBullet::destroy() {
	this->destroyed = true;
	this->shape.setPosition(0, 0);
}