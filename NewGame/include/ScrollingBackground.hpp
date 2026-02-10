#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class ScrollingBackground : public sf::Drawable {
public:
    ScrollingBackground();
    ScrollingBackground(const std::string& texturePath);
    void update(float speed);
    void setSpeed(float speed) { mSpeed = speed; }  

private:
    sf::Texture mTexture;
    sf::Sprite mBackground1;
    sf::Sprite mBackground2;
    float mSpeed = 0.f;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};