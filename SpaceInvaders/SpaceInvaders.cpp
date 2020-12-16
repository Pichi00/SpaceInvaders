#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

/*Klasy*/
#include "Player.h"

/*Wymiary okna*/
const int WindowWidth = 1024;
const int WindowHeight = 567;

int main()
{
    sf::RenderWindow window{ sf::VideoMode(WindowWidth,WindowHeight), "TEST"};
    window.setFramerateLimit(60);
    Player player(WindowWidth /2, WindowHeight * 7 / 8);
       while (window.isOpen()) {
        sf::Event event;
        
        window.pollEvent(event);
        if (event.type == sf::Event::Closed) window.close();
        window.clear(sf::Color::Cyan);

        player.update();

        window.draw(player);
        window.display();
    }
    return 0;
}

