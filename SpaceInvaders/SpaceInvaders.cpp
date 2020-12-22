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
    sf::RenderWindow window{ sf::VideoMode(WindowWidth,WindowHeight), "Space Invaders"};
    window.setFramerateLimit(60);
    //Player player(0,0);
    Player player(WindowWidth /2, WindowHeight * 7 / 8);
    PlayerBullet bullet(WindowWidth / 2, WindowHeight * 7 / 8);
    /*sf::CircleShape dot(2.f);
    dot.setPosition(WindowWidth / 2, WindowHeight * 7 / 8);
    dot.setFillColor(sf::Color::Red);*/

       while (window.isOpen()) {
        sf::Event event;
        
        window.pollEvent(event);
        if (event.type == sf::Event::Closed) window.close();
        window.clear(sf::Color::Black);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            bullet.isOnScreen = true;
            bullet.setPosition(player.getPosition());

        }

        if (bullet.isOnScreen) {
            bullet.update();
            window.draw(bullet);
        }

        player.update();        
        window.draw(player);
        window.display();
    }
    return 0;
}

