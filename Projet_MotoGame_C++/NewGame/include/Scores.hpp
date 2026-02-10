// Scores.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Scores {
public:
    Scores(sf::RenderWindow& window);
    void draw();
    bool handleInput();
    void loadScores();
    void addScore(float elapsedTime); // Doit accepter le temps écoulé

private:
    sf::RenderWindow& mWindow;
    sf::Font mFont;
    std::vector<sf::Text> mScoreItems;
    sf::Text mTitle;
    sf::Text mBackText;
    std::vector<float> mScores;
};