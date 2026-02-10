#include "Timer.hpp"
#include "Constants.hpp"
#include <iostream>

Timer::Timer(float timeLimit) : 
    mRemainingTime(timeLimit), // Changé ici
    mTimeLimit(timeLimit)
{
    mText.setCharacterSize(24);
    mText.setFillColor(sf::Color::White);
}

void Timer::start() {
    mClock.restart();
    mRemainingTime = mTimeLimit; // Changé ici
    updateTextDisplay();
}


void Timer::update(float deltaTime) {
    if (mRemainingTime > 0) {
        mRemainingTime -= deltaTime; // Changé ici
        updateTextDisplay();
    }
}

void Timer::draw(sf::RenderWindow& window) const {
    window.draw(mText);
}

bool Timer::loadFont(const std::string& fontPath) {
    return mFont.loadFromFile(fontPath);
}

void Timer::setPosition(const sf::Vector2f& position) {
    mText.setPosition(position);
}


float Timer::getSpeedMultiplier() const {
    float progress = 1.0f - (mRemainingTime / mTimeLimit);
    return 1.0f + (progress * (Constants::MAX_SPEED_MULTIPLIER - 2.5f));
}


void Timer::updateTextDisplay() {
    int totalSeconds = static_cast<int>(mRemainingTime);
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    float speed = getSpeedMultiplier();

    std::stringstream ss;
    ss << "TIMER: " 
       << std::setfill('0') << std::setw(2) << minutes << ":"
       << std::setfill('0') << std::setw(2) << seconds
       << "\nSPEED: x" << std::fixed << std::setprecision(1) << speed;

    mText.setString(ss.str());
    mText.setFont(mFont);
}
