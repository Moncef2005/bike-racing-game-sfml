#include "ScrollingBackground.hpp"
#include "Constants.hpp"  
#include <iostream>

ScrollingBackground::ScrollingBackground() {}

ScrollingBackground::ScrollingBackground(const std::string& texturePath) {
    if (!mTexture.loadFromFile(texturePath)) {
        std::cerr << "Erreur de chargement de texture : " << texturePath << std::endl;
    }

    mBackground1.setTexture(mTexture);
    mBackground2.setTexture(mTexture);

    float scaleX = static_cast<float>(Constants::WINDOW_WIDTH) / mTexture.getSize().x;
    float scaleY = static_cast<float>(Constants::WINDOW_HEIGHT) / mTexture.getSize().y;

    mBackground1.setScale(scaleX, scaleY);
    mBackground2.setScale(scaleX, scaleY);

    mBackground1.setPosition(0.f, 0.f);
    mBackground2.setPosition(static_cast<float>(Constants::WINDOW_WIDTH), 0.f);
}


void ScrollingBackground::update(float speed) {
    mBackground1.move(-speed, 0);
    mBackground2.move(-speed, 0);

    float width = mBackground1.getGlobalBounds().width;

    if (mBackground1.getPosition().x <= -width) {
        mBackground1.setPosition(mBackground2.getPosition().x + width - 1, 0.f);
    }
    if (mBackground2.getPosition().x <= -width) {
        mBackground2.setPosition(mBackground1.getPosition().x + width - 1, 0.f);
    }
}

void ScrollingBackground::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mBackground1, states);
    target.draw(mBackground2, states);
}
