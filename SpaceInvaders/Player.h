#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Player: public sf::Drawable
{
public:
	/*Publiczne zmienne*/

	/*Publiczne metody*/
	Player() = delete;
	Player(float t_X, float t_Y);
	~Player() = default;
	void update();

	float right();
	float left();
	float top();
	float bottom();
	sf::Vector2f getPosition();
	unsigned char getHP();
	void takeDamage();
	bool isAlive();
private:
	/*Prywatne zmienne*/
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	float playerSpeed{ 8.0f };
	sf::Vector2f velocity{ playerSpeed, 0.f};
	const float playerWidth = 15.0;
	const float playerHeight = 15.0;
	const float playerScale = 3.0;
	unsigned char playerHP = 3;
	bool alive = true;
	/*Prywatne metody*/
	void draw(sf::RenderTarget &target, sf::RenderStates state) const override;
};

