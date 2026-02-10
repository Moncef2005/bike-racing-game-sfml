#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>

class Timer {
public:
    Timer(float timeLimit = 60.0f);
    void start();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    bool loadFont(const std::string& fontPath);
    void setPosition(const sf::Vector2f& position);
    float getRemainingTime() const { return mRemainingTime; }
    bool isTimeUp() const { return mRemainingTime <= 0.f; }
    float getSpeedMultiplier() const;
    const sf::Font& getFont() const { return mFont; }
    
private:
    sf::Clock mClock;
    float mRemainingTime;
    float mTimeLimit;
    sf::Text mText;
    sf::Font mFont;
    
    void updateTextDisplay();
};