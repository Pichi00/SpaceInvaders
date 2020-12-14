#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

/*Wymiary okna*/
const int WindowWidth = 1024;
const int WindowHeight = 567;

int main()
{
    RenderWindow window{ VideoMode(WindowWidth,WindowHeight), "TEST"};

       while (window.isOpen()) {
        Event event;
        window.pollEvent(event);
        if (event.type == Event::Closed) window.close();
        window.clear();
        window.display();
    }
    return 0;
}

