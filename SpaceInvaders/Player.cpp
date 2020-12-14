#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const std::string playerTexturePath = "Textures/player.png";

/*Konstruktor*/
Player::Player() {
	if (!playerTexture.loadFromFile(playerTexturePath)) {
		std::cout << "Blad ladowania tekstury gracza. Upewnij sie, ze posiadasz plik \"" << playerTexturePath<<"\"" <<std::endl;
	}
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(3.f, 3.f);
}

/*Nadpisana funkcja draw()*/
void Player::draw(sf::RenderTarget &target, sf::RenderStates state) const {
	target.draw(this->playerSprite, state);
}