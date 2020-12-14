#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Player: public sf::Drawable
{
public:
	/*Publiczne zmienne*/

	/*Publiczne metody*/
	Player();
	~Player() = default;
private:
	/*Prywatne zmienne*/

	/*Prywatne metody*/
	void draw(sf::RenderTarget &target, sf::RenderStates state) const override;
};
