#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const std::string enemyTexturePath = "Textures/enemy.png";

Enemy::Enemy(float t_X, float t_Y) {
	enemySprite.setPosition(0, 0);
	enemySprite.setOrigin(enemyWidth / 2 , enemyHeight / 2);
	enemySprite.setScale(enemyScale, enemyScale);
	enemySprite.setPosition(t_X, t_Y);

	if (!enemyTexture.loadFromFile(enemyTexturePath)) {
		std::cout << "Blad ladowania tekstury. Upewnij sie, ze posiadasz plik \"" << enemyTexturePath << "\"" << std::endl;
	}
	enemySprite.setTexture(enemyTexture);
	
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->enemySprite);
}

float Enemy::left() {
	return this->enemySprite.getPosition().x - this->enemyWidth / 2 * enemyScale;
}
float Enemy::right() {
	return this->enemySprite.getPosition().x + this->enemyWidth / 2 * enemyScale;
}
float Enemy::top() {
	return this->enemySprite.getPosition().y - this->enemyHeight / 2 * enemyScale;
}
float Enemy::bottom() {
	return this->enemySprite.getPosition().y + this->enemyHeight / 2 * enemyScale;
}

void Enemy::update() {
	this->enemySprite.move(velocity);
}

void Enemy::changeDirection() {
	velocity.x = -velocity.x;
}