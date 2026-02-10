#pragma once
#include <SFML/Graphics.hpp>

class Bike {
public:
    Bike();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    void jump();
    void resetJump();
    sf::FloatRect getGlobalBounds() const;
    
private:
    sf::Sprite sprite;  // Déclaré ici
    sf::Texture texture;
    float mVelocityY = 0.f;
    bool mIsJumping = false;
    bool mCanDoubleJump = false;
    static constexpr float GRAVITY = 1000.f;
    static constexpr float JUMP_FORCE = -500.f;
    static constexpr float DOUBLE_JUMP_FORCE = -400.f;
};