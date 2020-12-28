#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

/*Klasy*/
#include "Player.h"
#include "PlayerBullet.h"
#include "Block.h"
#include "Button.h"

enum STATES { MAIN_MENU = 1, GAMEPLAY, HOW_TO_PLAY, BEST_SCORES, AUTHOR };
char GAME_STATE = STATES::MAIN_MENU;

/*Wymiary okna*/
const float WindowWidth = 1024;
const float WindowHeight = 567;

const int enemiesAmountX = 11;
const int enemiesAmountY = 5;

unsigned char player_points{};

template <class T1, class T2> bool isIntersecting(T1& a, T2& b) {
    return  a.right() >= b.left() && a.left() <= b.right() &&
        a.bottom() >= b.top() && a.top() <= b.bottom();
}

bool colisionTest(PlayerBullet& p, Block& e);

int main()
{
    /*GENERAL SETUP*/
    sf::RenderWindow window{ sf::VideoMode(WindowWidth,WindowHeight), "Space Invaders", sf::Style::Titlebar | sf::Style::Close };
    window.setFramerateLimit(60);
    
    /*MAIN MENU SETUP*/
    sf::Sprite MainMenu;
    sf::Texture MainMenuBackground;

    Button startGameButton(187, 173);
    startGameButton.setTextTexture("Textures/grajtxt.png");
    Button exitGameButton(187, 373);
    exitGameButton.setTextTexture("Textures/wyjdztxt.png");

    if (!MainMenuBackground.loadFromFile("Textures/mainmenu.png")) {
        std::cout << "Blad wczytywania tekstury" << std::endl;
    }
    MainMenu.setTexture(MainMenuBackground);



    /*GAMEPLAY SETUP*/
    Player player(WindowWidth /2, WindowHeight * 7 / 8);
    PlayerBullet bullet(WindowWidth / 2, WindowHeight * 7 / 8);
    Block enemies[enemiesAmountX][enemiesAmountY];
    
    for (int i = 1; i <= enemiesAmountX; i++) {
        for (int j = 1; j <= enemiesAmountY; j++) {
            if (j == 1) {
                Block enemy(10 + i * 55 * 10 / 9, 10 + j * 35 * 10 / 8, 1);
                enemies[i - 1][j - 1] = enemy;
            }
            else {
                Block enemy(10 + i * 55 * 10 / 9, 10 + j * 35 * 10 / 8);
                enemies[i - 1][j - 1] = enemy;
            }
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

        switch(GAME_STATE){
        case MAIN_MENU:
            /*-----MAIN MANU-----*/
           
            if (startGameButton.isPressed(window)) {
                GAME_STATE = STATES::GAMEPLAY;
            }
            else if (exitGameButton.isPressed(window)) {
                window.close();
            }

            window.draw(MainMenu);
            window.draw(startGameButton);
            window.draw(exitGameButton);
            /*----/MAIN MANU-----*/
            break;
        case GAMEPLAY:
            /*-----GAMEPLAY-----*/
            /*Warunek sprawdzający kiedy zacząć wyświetlanie pocisku gracza*/
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && bullet.destroyed) {
                bullet.create();
                bullet.setPosition(player.getPosition());
            }
            /*Warunek sprawdzający czy wyświetlać pocisk gracza*/
            if (!bullet.destroyed) {
                bullet.update();
                window.draw(bullet);
            }
            /*Warunek sprawdzający czy pocisk znajduje się nadal na ekranie*/
            if (bullet.bottom() < 0) {
                bullet.destroy();
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

            for (int i = 0; i < enemiesAmountX; i++) {
                for (int j = 0; j < enemiesAmountY; j++) {
                    if (!enemies[i][j].isDestroyed()) {
                        colisionTest(bullet, enemies[i][j]);
                    }
                    if (enemies[enemiesAmountX - 1][j].right() >= WindowWidth || enemies[0][j].left() <= 0) {
                        enemies[i][j].changeDirection();
                        
                    }
                }
            }
            for (int i = 0; i < enemiesAmountX; i++) {
                for (int j = 0; j < enemiesAmountY; j++) {
                    enemies[i][j].update();
                    if (!enemies[i][j].isDestroyed()) {
                        window.draw(enemies[i][j]);
                    }

                }
            }
            player.update();
            window.draw(player);
            /*-----/GAMEPLAY-----*/
            break;
        }
        window.display();
    }
    return 0;
}

bool colisionTest(PlayerBullet& pb, Block& e) {
    if (!isIntersecting(pb, e)) return false;
    else {
        pb.destroy();
        e.destroy();
    }
}