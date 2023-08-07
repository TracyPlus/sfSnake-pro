#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "Game.h"
#include "screen/GameScreen.h"
#include "screen/GameOverScreen.h"
#include "screen/HelpScreen.h"
#include "screen/StartScreen.h"

using namespace sfSnake;

GameOverScreen::GameOverScreen(std::size_t score)
    : button_(3), score_(score)
{
    text_.setFont(Game::GlobalFont);
    text_.setString(sf::String(L"最终分数：") + std::to_string(score));
    text_.setFillColor(Game::Color::DarkBlue);
    text_.setCharacterSize(Game::GlobalVideoMode.width / 15);
    setOriginMiddle(text_);
    text_.setPosition(Game::GlobalVideoMode.width / 2.0f, Game::GlobalVideoMode.height / 4.0f);

    button_[0].update("assets/image/optionUI.png");
    button_[1].update("assets/image/restartUI.png");
    button_[2].update("assets/image/exitUI.png");

    button_[0].setPosition(Game::GlobalVideoMode.width / 3.0, Game::GlobalVideoMode.height / 5.0 * 3.0);
    button_[1].setPosition(Game::GlobalVideoMode.width / 2.0, Game::GlobalVideoMode.height / 5.0 * 3.0);
    button_[2].setPosition(Game::GlobalVideoMode.width / 3.0 * 2.0, Game::GlobalVideoMode.height / 5.0 * 3.0);
}

void GameOverScreen::handleInput(sf::RenderWindow &window)
{
    static sf::Vector2i mousePosition;
    mousePosition = sf::Mouse::getPosition(window);

    for (auto &i : button_)
        i.focused(false);

    if (button_[0].contain(mousePosition))
    {
        button_[0].focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::mouseButtonCDtime = sf::Time::Zero;
            Game::mouseButtonLocked = true;
            Game::TmpScreen = Game::MainScreen;
            Game::MainScreen = std::make_shared<OptionScreen>();
            return;
        }
    }

    if (button_[1].contain(mousePosition))
    {
        button_[1].focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::mouseButtonCDtime = Game::mouseButtonClock.restart();
            Game::mouseButtonLocked = true;
            Game::MainScreen = std::make_shared<GameScreen>();
            return;
        }
    }

    if (button_[2].contain(mousePosition))
    {
        button_[2].focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            window.close();
            return;
        }
    }
}

void GameOverScreen::update(sf::Time delta)
{
}

void GameOverScreen::render(sf::RenderWindow &window)
{
    window.draw(text_);
    for (auto &button : button_)
        button.render(window);
}