#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

/*Klasy*/
#include "Player.h"
#include "PlayerBullet.h"
#include "Block.h"

/*Wymiary okna*/
const float WindowWidth = 1024;
const float WindowHeight = 567;

const int enemiesAmountX = 11;
const int enemiesAmountY = 5;

int main()
{
    sf::RenderWindow window{ sf::VideoMode(WindowWidth,WindowHeight), "Space Invaders"};
    window.setFramerateLimit(60);
    //Player player(0,0);
    Player player(WindowWidth /2, WindowHeight * 7 / 8);
    PlayerBullet bullet(WindowWidth / 2, WindowHeight * 7 / 8);
 
    Block enemies[enemiesAmountX][enemiesAmountY];
    for (int i = 1; i <= enemiesAmountX; i++) {
        for (int j = 1; j <= enemiesAmountY; j++) {
            Block enemy(10 + i * 55 * 10 / 9, 10 + j * 35 * 10 / 8);
            enemies[i - 1][j - 1] = enemy;
            enemies[i - 1][j - 1].setTexture();
        }
    }

   /* sf::CircleShape dot(2.f);
    dot.setPosition(WindowWidth / 2, WindowHeight * 7 / 8);
    dot.setPosition(enemy.right(), enemy.top());
    dot.setFillColor(sf::Color::Red);*/

       while (window.isOpen()) {
        sf::Event event;
        
        window.pollEvent(event);
        /*Warunek sprawdzający kiedy zamknąć okno*/
        if (event.type == sf::Event::Closed) window.close();
        window.clear(sf::Color::Black);

        /*Warunek sprawdzający kiedy zacząć wyświetlanie pocisku gracza*/
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !bullet.isOnScreen) {
            bullet.isOnScreen = true;
            bullet.setPosition(player.getPosition());
        }
        /*Warunek sprawdzający czy wyświetlać pocisk gracza*/
        if (bullet.isOnScreen) {
            bullet.update();
            window.draw(bullet);
        }
        /*Warunek sprawdzający czy pocisk znajduje się nadal na ekranie*/
        if (bullet.bottom() < 0) {
            bullet.isOnScreen = false;
        }
        /*
        if (enemy.right() >= WindowWidth || enemy.left() <=0 ) {
            enemy.changeDirection();
        }*/

        /*for (int i = 0; i < enemiesAmountX; i++) {
            for (int j = 0; j < enemiesAmountY; j++) {
                if (!blocks[i][j].isDestroyed()) {
                    window.draw(blocks[i][j]);
                }
            }
        }*/

        for (int i = 1; i <= enemiesAmountX; i++) {
            for (int j = 1; j <= enemiesAmountY; j++) {
                window.draw(enemies[i-1][j-1]);
            }
        }

        player.update();  
       // enemy.update();
        window.draw(player);
       // window.draw(enemy);
       // window.draw(dot);
        
        window.display();
    }
    return 0;
}

