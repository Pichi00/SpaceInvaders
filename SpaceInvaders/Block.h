#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>

class Block : public sf::Drawable
{
public:
	Block() = default;
	Block(int t_X, int t_Y, char type = 0);
	~Block() = default;

	unsigned int enemyType{};

	void update();

	float left();
	float right();
	float top();
	float bottom();

	bool isDestroyed();
	void destroy();

	sf::Vector2f getSize();
	sf::Vector2f getPosition();

	void changeDirection();

	void setTexture();
private:
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	sf::Sprite enemySprite;
	sf::Texture enemyTexture;
	unsigned int points = 10;
	float enemyWidth = 14;
	float enemyHeight = 14;
	float enemyScale = 2.0f;
	float enemySpeed = 1.5f;
	sf::Vector2f velocity{ enemySpeed,0 };
	bool destroyed{ false };
};

