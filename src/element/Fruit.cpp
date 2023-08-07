#include <SFML/Graphics.hpp>
#include <iostream>

#include "Fruit.h"
#include "Game.h"

using namespace sfSnake;

Fruit::Fruit(sf::Vector2f position, sf::Color color, int score)
    : score_(score)
{
    shape_.setRadius(Game::GlobalVideoMode.width / 256.0f);
    setOriginMiddle(shape_);
    shape_.setPosition(position);
    shape_.setFillColor(color);
}

Fruit::Fruit(sf::Vector2f position, const std::string& imagePath, int score)
    : score_(score)
{
    shape_.setRadius(Game::GlobalVideoMode.width / 32.0f);
    texture.loadFromFile(imagePath);
    setOriginMiddle(shape_);
    shape_.setTexture(&texture, true);
    shape_.setPosition(position);
}

void Fruit::render(sf::RenderWindow &window)
{
    shape_.setTexture(&texture, true);
    window.draw(shape_);
}
