#include "Block.h"
#include<SFML/Graphics.hpp>


const std::string enemyTexturePath = "Textures/enemy.png";


Block::Block(int t_X, int t_Y) {
	enemySprite.setOrigin(enemyWidth / 2, enemyHeight / 2);
	enemySprite.setPosition(static_cast<float> (t_X), static_cast<float>(t_Y));
	/*if (!enemyTexture.loadFromFile(enemyTexturePath)) {
		std::cout << "Blad ladowania tekstury. Upewnij sie, ze posiadasz plik \"" << enemyTexturePath << "\"" << std::endl;
	}*/
	//enemySprite.setTexture(enemyTexture);
	enemySprite.setScale(enemyScale, enemyScale);
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
	this->enemyTexture.loadFromFile("Textures/enemy.png");
	this->enemySprite.setTexture(this->enemyTexture);
}

void Block::changeDirection() {
	this->velocity.x = - this->velocity.x;
}