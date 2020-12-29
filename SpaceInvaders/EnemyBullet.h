#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
class EnemyBullet: public sf::Drawable
{
public:
	EnemyBullet() = default;
	EnemyBullet(float t_X, float t_Y);
	bool destroyed{ true };

	void update();
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
	const float bulletSpeed = 4.5f;
	sf::Vector2f velocity = { 0 , bulletSpeed };

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

