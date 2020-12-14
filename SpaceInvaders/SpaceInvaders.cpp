#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

/*Wymiary okna*/
const int WindowWidth = 1024;
const int WindowHeight = 567;

int main()
{
    sf::RenderWindow window{ sf::VideoMode(WindowWidth,WindowHeight), "TEST"};

       while (window.isOpen()) {
        sf::Event event;
        window.pollEvent(event);
        if (event.type == sf::Event::Closed) window.close();
        window.clear();
        window.display();
    }
    return 0;
}

