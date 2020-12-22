#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
class PlayerBullet: public sf::Drawable
{
public:
	bool isOnScreen{ false };

	void update();
	PlayerBullet() = delete;
	PlayerBullet(float t_X, float t_Y);
	~PlayerBullet() = default;
	void setPosition(sf::Vector2f pos);
private:
	sf::RectangleShape shape;
	const float bulletWidth = 3;
	const float bulletHeight = 9;
	const float bulletSpeed = 8.0f;
	sf::Vector2f velocity = { 0 , -bulletSpeed };
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

