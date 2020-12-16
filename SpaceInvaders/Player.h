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
private:
	/*Prywatne zmienne*/
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	float playerVelocity{ 8.0f };
	sf::Vector2f velocity{playerVelocity, 0.f};
	const float playerWidth = 15;
	const float playerHeight = 15;

	/*Prywatne metody*/
	void draw(sf::RenderTarget &target, sf::RenderStates state) const override;
};

