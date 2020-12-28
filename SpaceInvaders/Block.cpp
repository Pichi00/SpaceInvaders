#include "Block.h"
#include<SFML/Graphics.hpp>


const std::string enemyTexturePath = "Textures/enemy.png";


Block::Block(int t_X, int t_Y, char type) {
	enemySprite.setOrigin(enemyWidth / 2, enemyHeight / 2);
	enemySprite.setPosition(static_cast<float> (t_X), static_cast<float>(t_Y));
	enemySprite.setScale(enemyScale, enemyScale);

	switch (type) {
	case 0:
		points = 10;
		break;
	case 1:
		points = 20;
		enemySprite.setColor(sf::Color::Red);
		break;
	}

	
}

void Block::update() {
	this->enemySprite.move(velocity);
}

float Block::left() {
	return this->enemySprite.getPosition().x - enemyWidth * enemyScale / 2;
}
float Block::right() {
	return this->enemySprite.getPosition().x + enemyWidth * enemyScale / 2;
}
float Block::top() {
	return this->enemySprite.getPosition().y - enemyHeight / 2;
}
float Block::bottom() {
	return this->enemySprite.getPosition().y + enemyHeight / 2;
}

bool Block::isDestroyed() {
	return this->destroyed;
}
void Block::destroy() {
	std::cout << points << std::endl;
	destroyed = true;
}

sf::Vector2f Block::getSize() {
	return {this->enemyWidth,this->enemyHeight};
}
sf::Vector2f Block::getPosition() {
	return this->enemySprite.getPosition();
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->enemySprite);
}

void Block::setTexture() {
	if (enemyType == 0) {
		enemyTexture.loadFromFile("Textures/enemy.png");
	}
	else if (enemyType == 1) {
		enemyTexture.loadFromFile("Textures/enemy.png");
		enemySprite.setColor(sf::Color::Red);
	}
	
	this->enemySprite.setTexture(this->enemyTexture);
}

void Block::changeDirection() {
	this->velocity.x = - this->velocity.x;
	if (++bumps == 2) {
		moveDown();
		bumps = 0;
	}
}

void Block::moveDown() {
	this->enemySprite.setPosition({ enemySprite.getPosition().x,enemySprite.getPosition().y + enemyHeight*enemyScale });
}

unsigned int Block::getPoints() {
	return points;
}