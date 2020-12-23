#pragma once
#include<SFML/Graphics.hpp>
class Enemy:public sf::Drawable
{
public:
	Enemy() = delete;
	Enemy(float t_X, float t_Y);
	~Enemy() = default;

	float left();
	float right();
	float top();
	float bottom();

	void update();
	void changeDirection();
private:
	sf::Sprite enemySprite;
	sf::Texture enemyTexture;
	const float enemyWidth = 14.0f;
	const float enemyHeight = 11.0f;
	const float enemyScale = 3.0f;
	const float enemySpeed = 4.0f;
	sf::Vector2f velocity{ enemySpeed, 0.f };

	void draw(sf::RenderTarget &target, sf::RenderStates state) const override;
};

