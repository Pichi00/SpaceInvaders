#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const std::string playerTexturePath = "Textures/player.png";

/*Konstruktor*/
Player::Player(float t_X, float t_Y) {
	playerSprite.setPosition(0,0);
	playerSprite.setOrigin(playerWidth/2 , playerHeight/2 );
	playerSprite.setPosition(t_X, t_Y);
	if (!playerTexture.loadFromFile(playerTexturePath)) {
		std::cout << "Blad ladowania tekstury gracza. Upewnij sie, ze posiadasz plik \"" << playerTexturePath<<"\"" <<std::endl;
	}
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(playerScale, playerScale);
	
}

/*Nadpisana funkcja draw()*/
void Player::draw(sf::RenderTarget &target, sf::RenderStates state) const {
	target.draw(this->playerSprite, state);
}

void Player::update() {
	this->playerSprite.move(this->velocity);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && this->left() > 0) {
		velocity.x = -playerSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && this->right() < 1024) {
		velocity.x = playerSpeed;
	}
	else velocity.x = 0.f;
}

float Player::left() {
	return this->playerSprite.getPosition().x - (playerWidth/2 * playerScale) - playerScale;
}
float Player::right() {
	return this->playerSprite.getPosition().x + (playerWidth/2 * playerScale) + playerScale;
}
float Player::top() {
	return this->playerSprite.getPosition().y - playerHeight/2 * playerScale;
}
float Player::bottom() {
	return this->playerSprite.getPosition().y + playerHeight/2 * playerScale;
}

sf::Vector2f Player::getPosition() {
	return this->playerSprite.getPosition();
}

unsigned char Player::getHP() {
	return this->playerHP;
}

void Player::takeDamage() {
	playerHP--;
}

bool Player::isAlive() {
	if (playerHP > 0)	return true;
	else				return false;
}

void Player::setPosition(sf::Vector2f pos) {
	this->playerSprite.setPosition(pos);
}