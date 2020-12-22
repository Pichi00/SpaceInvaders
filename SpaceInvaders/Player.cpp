#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayerBullet.h"

const std::string playerTexturePath = "Textures/player.png";

/*Konstruktor*/
Player::Player(float t_X, float t_Y) {
	playerSprite.setPosition(0,0);
	playerSprite.setOrigin(playerWidth/2, playerHeight/2);
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
		velocity.x = -playerVelocity;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && this->right() < 1024) {
		velocity.x = playerVelocity;
	}
	else velocity.x = 0.f;
	/* //Movement góra-dó³
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && this->top() > 0) {
		velocity.y = -playerVelocity;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && this->bottom() < 567) {
		velocity.y = playerVelocity;
	}
	else velocity.y = 0.f;*/
}

float Player::left() {
	return this->playerSprite.getPosition().x - (playerWidth/2 * playerScale);
}
float Player::right() {
	return this->playerSprite.getPosition().x + (playerWidth/2 * playerScale);
}
float Player::top() {
	return this->playerSprite.getPosition().y - playerHeight/2;
}
float Player::bottom() {
	return this->playerSprite.getPosition().y + playerHeight/2 ;
}

sf::Vector2f Player::getPosition() {
	return this->playerSprite.getPosition();
}