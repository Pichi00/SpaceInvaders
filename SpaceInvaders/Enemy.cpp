#include "Enemy.h"
#include<SFML/Graphics.hpp>


const std::string enemyTexturePath = "Textures/enemy.png";


Enemy::Enemy(int t_X, int t_Y, char type) {
	enemySprite.setOrigin(enemyWidth / 2, enemyHeight / 2);
	enemySprite.setPosition(static_cast<float> (t_X), static_cast<float>(t_Y));
	enemySprite.setScale(enemyScale, enemyScale);

	switch (type) {
	case 0:
		points = 10;
		break;
	case 1:
		points = 10;
		hp = 2;
		enemySprite.setColor(sf::Color::Red);
		break;
	case 2:
		points = 10;
		hp = 3;
		enemySprite.setColor({ 152, 31, 222 });
		break;
	}

	
}

void Enemy::update() {
	this->enemySprite.move(velocity);
}

float Enemy::left() {
	return this->enemySprite.getPosition().x - enemyWidth * enemyScale / 2;
}
float Enemy::right() {
	return this->enemySprite.getPosition().x + enemyWidth * enemyScale / 2;
}
float Enemy::top() {
	return this->enemySprite.getPosition().y - enemyHeight / 2;
}
float Enemy::bottom() {
	return this->enemySprite.getPosition().y + enemyHeight / 2;
}

bool Enemy::isDestroyed() {
	return this->destroyed;
}

void Enemy::hit() {
	hp--;
	if (hp == 0) {
		destroy();
	}
	else if (hp == 1) {
		enemySprite.setColor(sf::Color::White);
		points += 10;
	}
	else {
		enemySprite.setColor(sf::Color::Red);
		points += 10;
	}
	
}
void Enemy::destroy() {
	destroyed = true;
}

sf::Vector2f Enemy::getSize() {
	return {this->enemyWidth,this->enemyHeight};
}
sf::Vector2f Enemy::getPosition() {
	return this->enemySprite.getPosition();
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->enemySprite);
}

void Enemy::setTexture() {
	if (enemyType == 0) {
		enemyTexture.loadFromFile("Textures/enemy.png");
	}
	else if (enemyType == 1) {
		enemyTexture.loadFromFile("Textures/enemy.png");
		enemySprite.setColor(sf::Color::Red);
	}
	
	this->enemySprite.setTexture(this->enemyTexture);
}

void Enemy::changeDirection() {
	this->velocity.x = - this->velocity.x;
	if (++bumps == 2) {
		moveDown();
		bumps = 0;
	}
}

void Enemy::moveDown() {
	this->enemySprite.setPosition({ enemySprite.getPosition().x,enemySprite.getPosition().y + enemyHeight*enemyScale + 5 });
}

unsigned int Enemy::getPoints() {
	return points;
}