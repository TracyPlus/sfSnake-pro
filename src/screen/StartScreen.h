#pragma once

#include <SFML/Graphics.hpp>

#include "screen/Screen.h"
#include "element/Button.h"
#include "element/OptionButton.h"

#include <vector>

namespace sfSnake
{
    class StartScreen : public Screen
    {
    public:
        StartScreen();

        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;

    private:
        Button returnButton_;
        std::vector<OptionButton> optionName_;
        std::vector<OptionButton> DifficultyOptions_;
        int DifficultyFocused_;
        sf::Text text_, text2_;
    };
}