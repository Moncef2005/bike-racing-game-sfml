#pragma once
#include <SFML/System/Clock.hpp>
#include <vector>
#include "Bike.hpp"
#include "ScrollingBackground.hpp"
#include "Timer.hpp"
#include "Menu.hpp"
#include "About.hpp"
#include "Scores.hpp"
#include "Obstacle.hpp"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void showMenu();
    void showAbout();
    void showScores();
    void runGame();
    void showGameOver();
    void spawnObstacle();
    void checkCollisions();
    bool mPlayerWon; 

    
    sf::RenderWindow mWindow;
    Bike mBike;
    ScrollingBackground mBackground;
    Timer mTimer;
    sf::Clock mGameClock;
    sf::Clock mObstacleClock;
    Menu mMenu;
    About mAbout;
    Scores mScores;
    bool mInGame;
    std::vector<Obstacle> mObstacles;
    float mObstacleSpawnInterval;
};