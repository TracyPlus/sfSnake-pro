#pragma once

#include <SFML/Graphics.hpp>
#include <deque>

#include "screen/Screen.h"
#include "element/Snake.h"
#include "element/Fruit.h"
#include "element/Grid.h"
#include "element/Button.h"

namespace sfSnake
{
    class GameScreen : public Screen
    {
    public:
        GameScreen();

        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;

        void generateFruit();
        void generateGift();

    private:
        Snake snake_;
        std::deque<Fruit> fruit_;
        Grid grid_;

        Button pauseButton_;

        sf::Text score_;
    };
}