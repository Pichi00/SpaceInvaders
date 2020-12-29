#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(float t_X, float t_Y) {
	shape.setFillColor(sf::Color::Red);
	shape.setSize({ bulletWidth,bulletHeight });
	this->shape.setPosition(t_X, t_Y);
}

void EnemyBullet::update() {
	this->shape.move(velocity);
}

void EnemyBullet::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->shape);
}

void EnemyBullet::setPosition(sf::Vector2f pos) {
	this->shape.setPosition(pos);
}

float EnemyBullet::left() {
	return this->shape.getPosition().x - bulletWidth / 2;
}
float EnemyBullet::right() {
	return this->shape.getPosition().x + bulletWidth / 2;
}
float EnemyBullet::top() {
	return this->shape.getPosition().y - bulletHeight / 2;
}
float EnemyBullet::bottom() {
	return this->shape.getPosition().y + bulletHeight / 2;
}

void EnemyBullet::create() {
	this->destroyed = false;
}

void EnemyBullet::destroy() {
	this->destroyed = true;
	this->shape.setPosition(0, 0);
}