#include "Bike.hpp"
#include "Constants.hpp"
#include <iostream>

Bike::Bike() {
    if (!texture.loadFromFile("assets/textures/spr_bike2man_0.png")) {
        throw std::runtime_error("Failed to load bike texture");
    }
    sprite.setTexture(texture);
    sprite.setPosition(100, Constants::WINDOW_HEIGHT - texture.getSize().y - 50);
}

void Bike::update(float deltaTime) {
    // Gestion du saut
    if (mIsJumping) {
        mVelocityY += GRAVITY * deltaTime;
        sprite.move(0, mVelocityY * deltaTime);
        
        if (sprite.getPosition().y >= Constants::WINDOW_HEIGHT - texture.getSize().y - 50) {
            sprite.setPosition(sprite.getPosition().x, Constants::WINDOW_HEIGHT - texture.getSize().y - 50);
            resetJump();
        }
    }

    // Gestion déplacement horizontal
    float moveX = 0.f;
    const float bikeWidth = sprite.getGlobalBounds().width;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (sprite.getPosition().x < Constants::WINDOW_WIDTH - bikeWidth) {
            moveX += Constants::BIKE_SPEED * deltaTime;
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (sprite.getPosition().x > 0) {
            moveX -= Constants::BIKE_SPEED * deltaTime;
        }
    }
    
    sprite.move(moveX, 0);
}

void Bike::jump() {
    if (!mIsJumping) {
        mIsJumping = true;
        mCanDoubleJump = true;
        mVelocityY = JUMP_FORCE;
    } else if (mCanDoubleJump) {
        mVelocityY = DOUBLE_JUMP_FORCE;
        mCanDoubleJump = false;
    }
}

void Bike::resetJump() {
    mIsJumping = false;
    mCanDoubleJump = false;
}

void Bike::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Bike::getGlobalBounds() const {
    return sprite.getGlobalBounds(); // Retourne les limites de la sprite du vélo
}
