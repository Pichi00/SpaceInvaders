#pragma warning(disable : 4996) 
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>
#include <windows.h>
#include <ctime>
#include <iomanip>
#include <string>       /*getline*/
#include <sstream>

/*Klasy*/
#include "Player.h"
#include "PlayerBullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Button.h"

enum STATES { MAIN_MENU = 1, GAMEPLAY, WAVE_SCREEN, GAME_OVER, HOW_TO_PLAY, BEST_SCORES, AUTHOR, PAUSE };
char GAME_STATE = STATES::MAIN_MENU;

/*Wymiary okna*/
const unsigned int WindowWidth = 1024;
const unsigned int WindowHeight = 567;

const unsigned char enemiesAmountX = 12;
const unsigned char enemiesAmountY = 5;
unsigned char enemiesAlive{};
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


void setEnemiesWave(Enemy enemies[enemiesAmountX][enemiesAmountY], unsigned int type2=0, unsigned int type1=0);

void gameOver();
void newGame();

void saveResult(unsigned int points);
void getResults(sf::Text scoresText[]);

void sort(int tab[10], std::string s[10][3]);

int main()
{
    /*GENERAL SETUP*/
    srand(time(NULL));
    sf::RenderWindow window{ sf::VideoMode(WindowWidth,WindowHeight), "Space Invaders", sf::Style::Titlebar | sf::Style::Close };
    window.setFramerateLimit(60);
    unsigned int wave = 0;
    unsigned char enemiesType2 = 1;
    unsigned char enemiesType1 = 0;
    enemiesAlive = 0;
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
    Button bestScoresButton(187, 253);
    bestScoresButton.setTextTexture("Textures/bestscorestxt.png");
    Button howToButton(187, 333);
    howToButton.setTextTexture("Textures/howtotxt.png");
    Button exitGameButton(187, 413);
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
    clock_t bullet_cooldown_Start;
    const float bulletCooldown = 500; //Pocisk gracza odnawia się co 0.5s
    bool shotAvaliable = true;

    clock_t ebullet_cooldown_Start;
    const float ebulletCooldown = 1500; //Pocisk przeciwników odnawia się co 1.5s
    bool eshotAvaliable = true;

    //setEnemiesWave(enemies, enemiesType2, enemiesType1);

   
    /*GAME OVER SETUP*/
    sf::Sprite GameOver;
    sf::Texture GameOverBackground;
    sf::Text Result;
    //std::string PlayerInput;

    Result.setCharacterSize(25);
    Result.setFillColor({ 86, 27, 174 });
    Result.setPosition({WindowWidth/6, WindowHeight/2});
    Result.setFont(font);
    if (!GameOverBackground.loadFromFile("Textures/gameover.png")) {
        std::cout << "Blad wczytywania tekstury" << std::endl;
    }
    GameOver.setTexture(GameOverBackground);

    /*BEST SCORES SETUP*/
    sf::Sprite BestScores;
    sf::Texture BestScoresBackground;
    sf::Text scoresText[10];
    BestScoresBackground.loadFromFile("Textures/bestscores.png");
    BestScores.setTexture(BestScoresBackground);

    /*HOW TO PLAY SETUP*/
    sf::Sprite HowToPlay;
    sf::Texture HowToPlayBackground;
    HowToPlayBackground.loadFromFile("Textures/howtoplay.png");
    HowToPlay.setTexture(HowToPlayBackground);

    /*PAUSE SETUP*/
    sf::Sprite Pause;
    sf::Texture PauseTexture;
    PauseTexture.loadFromFile("Textures/pause.png");
    Pause.setTexture(PauseTexture);

    for (int i = 0; i < 10; i++) {
        scoresText[i].setFont(font);
        scoresText[i].setFillColor({ 86, 27, 174 });
        scoresText[i].setPosition({WindowWidth/5,WindowHeight / 3 + 30 * static_cast<float>(i) });
        scoresText[i].setCharacterSize(16);
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
            /*-----MAIN MENU-----*/
           
            if (startGameButton.isPressed(window)) {
                GAME_STATE = STATES::GAMEPLAY;
            }
            else if (bestScoresButton.isPressed(window)) {
                getResults(scoresText);
                GAME_STATE = STATES::BEST_SCORES;
            }
            else if (howToButton.isPressed(window)) {
                GAME_STATE = STATES::HOW_TO_PLAY;
            }
            else if (exitGameButton.isPressed(window)) {
                window.close();
            }

            window.draw(MainMenu);
            window.draw(startGameButton);
            window.draw(bestScoresButton);
            window.draw(howToButton);
            window.draw(exitGameButton);
            /*----/MAIN MENU-----*/
            break;
        case GAMEPLAY:
            /*-----GAMEPLAY-----*/
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                GAME_STATE = STATES::PAUSE;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                for (int i = 0; i < enemiesAmountX; i++) {
                    for (int j = 0; j < enemiesAmountY; j++) {
                        if (!enemies[i][j].isDestroyed()) {
                            enemies[i][j].destroy();
                            enemiesAlive--;
                        }
                       
                    }
                }
            }
            if (enemiesAlive == 0) {
                ebullet.destroy();
                bullet.destroy();
                player.setPosition({ WindowWidth / 2, WindowHeight * 7 / 8 });
                wave++;
                if (wave < 9) {
                    if (wave % 2 == 1 ) {
                        enemiesType1++;
                    }
                    else {
                        enemiesType2++;
                        if (enemiesType1 > 0) enemiesType1--;
                    }
                }
                
                setEnemiesWave(enemies, enemiesType2, enemiesType1);
                window.clear(sf::Color::Black);
                waveNumberText.setString("Wave " + std::to_string(wave));
                window.draw(waveNumberText);
                GAME_STATE = STATES::WAVE_SCREEN;
                
            }
            /*Warunek sprawdzający kiedy zacząć wyświetlanie pocisku gracza*/
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && bullet.destroyed && shotAvaliable) {
                bullet.create();
                bullet.setPosition(player.getPosition());
                bullet_cooldown_Start = clock();
                shotAvaliable = false;

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

            if (!shotAvaliable) {
                if (clock() - bullet_cooldown_Start > bulletCooldown) shotAvaliable = true;
            }

            if (ebullet.destroyed && eshotAvaliable) {
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
                            ebullet_cooldown_Start = clock();
                            eshotAvaliable = false;
                            break;
                        }
                    }
                } while (shot != true );
                
                ebullet.create();
                ebullet.setPosition({ ebulletX, ebulletY });
            }
            else if(!ebullet.destroyed){
                ebullet.update();
                window.draw(ebullet);
            }

            if (!eshotAvaliable) {
                if (clock() - ebullet_cooldown_Start > ebulletCooldown) {
                    eshotAvaliable = true;
                }
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
          
            Result.setString("You have scored " + std::to_string(player_points) + " points.");
            window.draw(Result);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                GAME_STATE = STATES::MAIN_MENU;
                window.close();
                
                return main();
            }

            /*-----/GAME OVER-----*/
            break;
        case BEST_SCORES:
            /*------BEST SCORES-----*/
            window.draw(BestScores);
            
            for (int i = 0; i < 10; i++) {
                window.draw(scoresText[i]);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                GAME_STATE = STATES::MAIN_MENU;
            }
            /*------/BEST SCORES-----*/
            break;
            /*------HOW TO PLAY-----*/
        case HOW_TO_PLAY:
            window.draw(HowToPlay);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                GAME_STATE = STATES::MAIN_MENU;
            }
            /*------/HOW TO PLAY-----*/
            break;
            /*------PAUSE-----*/
        case PAUSE:
            window.draw(Pause);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                GAME_STATE = STATES::GAMEPLAY;
            }


            /*------/PAUSE-----*/
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

    saveResult(player_points);
}

void newGame(){
    std::cout << "new game" << std::endl;
}

void saveResult(unsigned int points) {
    std::fstream plik;
    std::string scores[10][3];
    int tab[10];
    /*std::string date;
    std::string time;*/
    //bool resultInserted = true;

    plik.open("results.txt", std::ios::in);
    for (int i = 0; i < 10; i++) {
        plik >> scores[i][0] >> scores[i][1] >> scores[i][2];
        try {

            tab[i] = stoi(scores[i][0]);
        }
        catch (std::exception& err) {
            tab[i] = 0;
        }
        //std::cout << scores[i][0] << " " << scores[i][1] << " " << scores[i][2] << std::endl;
    }
    sort(tab, scores);
    /*--- Zapis daty i godziny do stringa --*/
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::stringstream dateStream;
    std::stringstream timeStream;
    dateStream << std::put_time(&tm, "%d-%m-%Y");
    timeStream << std::put_time(&tm, "%H:%M:%S");
    std::string date = dateStream.str();
    std::string time = timeStream.str();
    /*----------------------------*/

    if (points > tab[9]) {
        tab[9] = points;
        scores[9][0] = std::to_string(points);
        scores[9][1] = date;
        scores[9][2] = time;
    }
    sort(tab, scores);
    plik.close();
        
    plik.open("results.txt", std::ios::out);
    for (int i = 0; i < 10; i++) {
        plik << scores[i][0] << " " << scores[i][1] << " " << scores[i][2] << std::endl;
    }
    plik.close();
    
    
}

void sort(int tab[10], std::string s[10][3]) {
    bool sorted = false;
    while (!sorted) {
        for (int i = 0; i < 9; i++) {
            if (tab[i] < tab[i + 1]) {
                std::swap(tab[i], tab[i + 1]);
                std::swap(s[i][0], s[i + 1][0]);
                std::swap(s[i][1], s[i + 1][1]);
                std::swap(s[i][2], s[i + 1][2]);
                sorted = false;
                break;
            }
            else {
                sorted = true;
            }
        }
    }
}

void getResults(sf::Text scoresText[]) {
    std::fstream plik;
    std::string strings[10][3];
    
    plik.open("results.txt", std::ios::in);
    //scores[0].setString("Wynik  |Data        |Godzina");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++) {
            plik >> strings[i][j];
        }
        std::stringstream ss;
        if (!strings[i][0].empty()) {
            ss <<std::setw(2)<<i+1<<". "<< std::setw(6) << strings[i][0] << " | " << strings[i][1] << " | " << strings[i][2];
            scoresText[i].setString(ss.str());
        }
        
    }
    plik.close();

}



