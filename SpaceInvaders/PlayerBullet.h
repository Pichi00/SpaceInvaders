#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
class PlayerBullet: public sf::Drawable
{
public:
	bool destroyed{ true };

	void update();
	PlayerBullet() = delete;
	PlayerBullet(float t_X, float t_Y);
	~PlayerBullet() = default;
	void setPosition(sf::Vector2f pos);

	float left();
	float right();
	float top();
	float bottom();

	void destroy();
	void create();
private:
	sf::RectangleShape shape;
	const float bulletWidth = 4;
	const float bulletHeight = 12;
	const float bulletSpeed = 8.0f;
	sf::Vector2f velocity = { 0 , -bulletSpeed };
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

