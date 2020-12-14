#include "Player.h"
#include <SFML/Graphics.hpp>

/*Konstruktor*/
Player::Player() {
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	
	if (!playerTexture.loadFromFile("player.png")) std::cout << "Loading file error (Player's texture)" << std::endl;
	playerSprite.setTexture(playerTexture);
}

/*Nadpisana funkcja draw()*/
void Player::draw(sf::RenderTarget &target, sf::RenderStates state) const {
	this->draw(target, state);
}