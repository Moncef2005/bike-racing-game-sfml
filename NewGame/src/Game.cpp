#include "Game.hpp"
#include "Constants.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game() : 
    mWindow(sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), "Moto Game"),
    mBike(),
    mBackground("assets/textures/background.png"),
    mTimer(Constants::GAME_DURATION),
    mMenu(mWindow),
    mAbout(mWindow),
    mScores(mWindow),
    mInGame(false),
    mObstacleSpawnInterval(4.0f)
{
    mWindow.setFramerateLimit(60);
    std::srand(std::time(nullptr)); // Pour la génération aléatoire
    
    if (!mTimer.loadFont("assets/fonts/Anton-Regular.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
    mTimer.setPosition(sf::Vector2f(20.f, 20.f));
     
}

void Game::run() {
    showMenu();
}

void Game::showMenu() {
    while (mWindow.isOpen()) {
        int choice = mMenu.handleInput();
        
        if (choice >= 0) {
            switch (choice) {
                case 0: runGame(); break;
                case 1: showScores(); break;
                case 2: showAbout(); break;
                case 3: mWindow.close(); return;
            }
        }
        mMenu.draw();
    }
}

void Game::runGame() {
    mTimer.start();
    mInGame = true;
    mObstacles.clear(); // Nettoyer les obstacles précédents
    mObstacleClock.restart();
    
    while (mWindow.isOpen() && mInGame) {
        sf::Time deltaTime = mGameClock.restart();
        processEvents();
        update(deltaTime);
        render();
        
        if (mTimer.isTimeUp()) {
            mInGame = false;
            mPlayerWon = true; // Le joueur a gagné en temps
            showGameOver();
        }
    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }
            
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                mBike.jump();
            }
            else if (event.key.code == sf::Keyboard::Escape) {
                mInGame = false;
            }
        }
    }
}

void Game::update(sf::Time deltaTime) {
    float dt = deltaTime.asSeconds();
    mBike.update(dt);
    mBackground.update(Constants::SCROLL_SPEED * mTimer.getSpeedMultiplier() * dt);
    mTimer.update(dt);
    
    // Gestion des obstacles
    if (mObstacleClock.getElapsedTime().asSeconds() > mObstacleSpawnInterval) {
        spawnObstacle();
        mObstacleClock.restart();
        // Réduire l'intervalle de spawn au fil du temps pour augmenter la difficulté
        mObstacleSpawnInterval = std::max(0.5f, mObstacleSpawnInterval - 0.05f);
    }
    
    // Mettre à jour les obstacles
    for (auto& obstacle : mObstacles) {
        obstacle.update(Constants::SCROLL_SPEED * mTimer.getSpeedMultiplier() * dt);
    }
    
    // Supprimer les obstacles hors de l'écran
    mObstacles.erase(std::remove_if(mObstacles.begin(), mObstacles.end(), 
        [](const Obstacle& o) { return o.getPosition().x + o.getWidth() < 0; }), 
        mObstacles.end());
    
    // Vérifier les collisions
    checkCollisions();
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(mBackground);
    
    // Dessiner les obstacles
    for (const auto& obstacle : mObstacles) {
        obstacle.draw(mWindow);
    }
    
    mBike.draw(mWindow);
    mTimer.draw(mWindow);
    mWindow.display();
}

void Game::spawnObstacle() {
    Obstacle newObstacle;
    // Positionner l'obstacle juste à droite de l'écran
    float yPosition = Constants::WINDOW_HEIGHT - newObstacle.getHeight() - 50; // 50 pour être au niveau du sol
    newObstacle.setPosition(Constants::WINDOW_WIDTH, yPosition);
    mObstacles.push_back(newObstacle);
}

void Game::checkCollisions() {
    for (const auto& obstacle : mObstacles) {
        if (mBike.getGlobalBounds().intersects(obstacle.getGlobalBounds())) {
            mInGame = false;
            mPlayerWon = false; // Le joueur a perdu
            showGameOver();
            break;
        }
    }
}

void Game::showAbout() {
    bool exitAbout = false;
    while (mWindow.isOpen() && !exitAbout) {
        exitAbout = mAbout.handleInput();
        mAbout.draw();
    }
}

void Game::showScores() {
    bool exitScores = false;
    while (mWindow.isOpen() && !exitScores) {
        exitScores = mScores.handleInput();
        mScores.draw();
    }
}

void Game::showGameOver() {
    sf::Text gameOverText;
    gameOverText.setFont(mTimer.getFont());
      if (mPlayerWon) {
        gameOverText.setString("YOU WIN!\nScore: " + 
                           std::to_string(static_cast<int>(Constants::GAME_DURATION - mTimer.getRemainingTime())) + 
                           "\nPress ESC");
        gameOverText.setFillColor(sf::Color::Green);}
        else 
    gameOverText.setString("GAME OVER\nTime end!\nScore: " + 
                         std::to_string(static_cast<int>(Constants::GAME_DURATION - mTimer.getRemainingTime())) + 
                         "\nAppuyez sur Echap");
    
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    
    sf::FloatRect bounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(bounds.width/2, bounds.height/2);
    gameOverText.setPosition(mWindow.getSize().x/2, mWindow.getSize().y/2);

    sf::RectangleShape overlay(sf::Vector2f(mWindow.getSize().x, mWindow.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

    bool exit = false;
    while (mWindow.isOpen() && !exit) {
        sf::Event event;
        while (mWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                exit = true;
            }
        }

        mWindow.clear();
        mWindow.draw(mBackground);
        for (const auto& obstacle : mObstacles) {
            obstacle.draw(mWindow);
        }
        mBike.draw(mWindow);
        mTimer.draw(mWindow);
        
        mWindow.draw(overlay);
        mWindow.draw(gameOverText);
        
        mWindow.display();
    }
}