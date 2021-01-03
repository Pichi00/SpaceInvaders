#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>
#include <windows.h>

/*Klasy*/
#include "Player.h"
#include "PlayerBullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Button.h"

enum STATES { MAIN_MENU = 1, GAMEPLAY, WAVE_SCREEN, GAME_OVER, HOW_TO_PLAY, BEST_SCORES, AUTHOR };
char GAME_STATE = STATES::MAIN_MENU;

/*Wymiary okna*/
const unsigned int WindowWidth = 1024;
const unsigned int WindowHeight = 567;

const unsigned char enemiesAmountX = 12;
const unsigned char enemiesAmountY = 5;
unsigned char enemiesType2=1;
unsigned char enemiesType1=0;
unsigned char enemiesAlive{};

unsigned int wave = 0;


unsigned int player_points{};

sf::Text pointsLabel;

/*Funkcje związane z kolizjami*/
template <class T1, class T2> bool isIntersecting(T1& a, T2& b) {
    return  a.right() >= b.left() && a.left() <= b.right() &&
        a.bottom() >= b.top() && a.top() <= b.bottom();
}
bool colisionTest(PlayerBullet& pb, Enemy& e);
bool colisionTest(EnemyBullet& eb, Player& p);
bool colisionTest(Enemy& e, Player& p);
void isEnemyOffScreen(Enemy& e);
/*----------------------------*/


void setEnemiesWave(Enemy enemies[enemiesAmountX][enemiesAmountY],unsigned int type2=0, unsigned int type1=0);

void gameOver();
void newGame();


int main()
{
    /*GENERAL SETUP*/
    srand(time(NULL));
    sf::RenderWindow window{ sf::VideoMode(WindowWidth,WindowHeight), "Space Invaders", sf::Style::Titlebar | sf::Style::Close };
    window.setFramerateLimit(60);
        
        /*Ponits label*/
        sf::Font font;
        font.loadFromFile("Fonts/dogica.ttf");
        pointsLabel.setFont(font);
        pointsLabel.setCharacterSize(16);
        pointsLabel.setFillColor(sf::Color::White);
        pointsLabel.setString("0");
        pointsLabel.setPosition({20,20 });
        player_points = 0;

        /*HP texture*/
        sf::Sprite heart;
        sf::Texture heartTexture;
        float heartWidth = 16;
        float heartHeight = 13;
        float heartScale = 2;
        heartTexture.loadFromFile("Textures/heart.png");
        heartTexture.setRepeated(true);
        heart.setOrigin(heartWidth/2, heartHeight/2);
        heart.setScale(heartScale, heartScale);
        heart.setPosition(heartWidth, 23);
        heart.setPosition(25, WindowHeight - 25);
        heart.setTexture(heartTexture);

        sf::Text waveNumberText;
        waveNumberText.setCharacterSize(60);
        waveNumberText.setFont(font);
        waveNumberText.setFillColor(sf::Color::White);
        waveNumberText.setOrigin({170,20});
        waveNumberText.setPosition({ WindowWidth / 2, WindowHeight / 2 });


    /*MAIN MENU SETUP*/
    sf::Sprite MainMenu;
    sf::Texture MainMenuBackground;

    Button startGameButton(187, 173);
    startGameButton.setTextTexture("Textures/grajtxt.png");
    Button exitGameButton(187, 253);
    exitGameButton.setTextTexture("Textures/wyjdztxt.png");

    if (!MainMenuBackground.loadFromFile("Textures/mainmenu.png")) {
        std::cout << "Blad wczytywania tekstury" << std::endl;
    }
    MainMenu.setTexture(MainMenuBackground);



    /*GAMEPLAY SETUP*/
    Player player(WindowWidth /2, WindowHeight * 7 / 8);
    PlayerBullet bullet(WindowWidth / 2, WindowHeight * 7 / 8);
    Enemy enemies[enemiesAmountX][enemiesAmountY];
    EnemyBullet ebullet(0,0);
    //setEnemiesWave(enemies, enemiesType2, enemiesType1);

   
    /*GAME OVER SETUP*/
    sf::Sprite GameOver;
    sf::Texture GameOverBackground;
    sf::Text Result;
    //std::string PlayerInput;

    Result.setCharacterSize(20);
    Result.setFillColor({ 86, 27, 174 });
    Result.setPosition({WindowWidth/3, WindowHeight/2});
    Result.setFont(font);
    if (!GameOverBackground.loadFromFile("Textures/gameover.png")) {
        std::cout << "Blad wczytywania tekstury" << std::endl;
    }
    GameOver.setTexture(GameOverBackground);

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
            /*-----MAIN MENU-----*/
           
            if (startGameButton.isPressed(window)) {
                GAME_STATE = STATES::GAMEPLAY;
            }
            else if (exitGameButton.isPressed(window)) {
                window.close();
            }

            window.draw(MainMenu);
            window.draw(startGameButton);
            window.draw(exitGameButton);
            /*----/MAIN MENU-----*/
            break;
        case GAMEPLAY:
            /*-----GAMEPLAY-----*/
            if (enemiesAlive == 0) {
                ebullet.destroy();
                bullet.destroy();
                player.setPosition({ WindowWidth / 2, WindowHeight * 7 / 8 });
                wave++;
                enemiesType1++;
                setEnemiesWave(enemies, enemiesType2, enemiesType1);
                window.clear(sf::Color::Black);
                waveNumberText.setString("Wave " + std::to_string(wave));
                window.draw(waveNumberText);
                GAME_STATE = STATES::WAVE_SCREEN;
                
            }
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

            if (ebullet.destroyed) {
                float ebulletX{};
                float ebulletY{};
                bool shot = false;
                
                do {
                    int randX = rand() % enemiesAmountX;
                    for (int i = enemiesAmountY - 1; i >= 0; i--) {
                        if (!enemies[randX][i].isDestroyed()) {
                            ebulletX = enemies[randX][i].getPosition().x;
                            ebulletY = enemies[randX][i].getPosition().y;
                            shot = true;
                            break;
                        }
                    }
                } while (shot != true );
                
                ebullet.create();
                ebullet.setPosition({ ebulletX, ebulletY });
            }
            else if (!ebullet.destroyed) {
                ebullet.update();
                window.draw(ebullet);
            }

            if (ebullet.top() > WindowHeight) {
                ebullet.destroy();
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
                        colisionTest(enemies[i][j], player);
                        isEnemyOffScreen(enemies[i][j]);
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

            heart.setTextureRect({ 0,0,16 * player.getHP(),13 });

            player.update();
            colisionTest(ebullet, player);
            window.draw(player);
            window.draw(pointsLabel);
            window.draw(heart);
            /*-----/GAMEPLAY-----*/
            break;
            /*-----WAVE SCREEN-----*/
        case WAVE_SCREEN:
            ebullet.destroy();
            bullet.destroy();
            
            Sleep(2000);
            GAME_STATE = STATES::GAMEPLAY;
            break;
            /*-----/WAVE SCREEN-----*/
        case GAME_OVER:
            /*-----GAME OVER-----*/
            window.draw(GameOver);
           /* if (event.type == sf::Event::TextEntered)
            {
                PlayerInput += event.text.unicode;
                PlayerNickName.setString(PlayerInput);
                std::cout << PlayerInput << std::endl;
            }*/
            Result.setString("Twoj wynik: " + std::to_string(player_points));
            window.draw(Result);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                GAME_STATE = STATES::MAIN_MENU;
                window.close();
                
                return main();
            }

            /*-----/GAME OVER-----*/
            break;
        }
        window.display();
    }
    return 0;
}

bool colisionTest(PlayerBullet& pb, Enemy& e) {
    if (!isIntersecting(pb, e)) return false;
    else {
        pb.destroy();
        player_points += e.getPoints();
        e.hit();        
        pointsLabel.setString(std::to_string(player_points));
        if (e.isDestroyed()) {
            enemiesAlive--;

        }
        
    }
}

bool colisionTest(EnemyBullet& eb, Player& p) {
    if (!isIntersecting(eb, p)) return false;
    else {
        eb.destroy();
        p.takeDamage();
        if (!p.isAlive()) gameOver();

    }
}
bool colisionTest(Enemy& e, Player& p) {
    if (!isIntersecting(e, p)) return false;
    else {
        gameOver();
    }
}

void isEnemyOffScreen(Enemy& e) {
    if (e.bottom() > static_cast<float>(WindowHeight)) gameOver();
}

void setEnemiesWave(Enemy enemies[enemiesAmountX][enemiesAmountY], unsigned int type2, unsigned int type1) {
    for (int i = 1; i <= enemiesAmountX; i++) {
        for (int j = 1; j <= enemiesAmountY; j++) {
            if (j >= 1 && j< 1+type2) {
                Enemy enemy(10 + i * 55 * 10 / 9, 10 + j * 35 * 10 / 8, 2);
                enemies[i - 1][j - 1] = enemy;
            }
            else if (j >= 1+type2 && j < 1 + type2 + type1) {
                Enemy enemy(10 + i * 55 * 10 / 9, 10 + j * 35 * 10 / 8,1);
                enemies[i - 1][j - 1] = enemy;
            }
            else {
                Enemy enemy(10 + i * 55 * 10 / 9, 10 + j * 35 * 10 / 8);
                enemies[i - 1][j - 1] = enemy;
            }
            enemies[i - 1][j - 1].setTexture();
            enemiesAlive++;
        }
    }
}

void gameOver() {
    GAME_STATE = STATES::GAME_OVER;
    
}

void newGame(){
    std::cout << "new game" << std::endl;
}