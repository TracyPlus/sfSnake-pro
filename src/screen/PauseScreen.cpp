#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "screen/MenuScreen.h"
#include "screen/GameScreen.h"
#include "screen/PauseScreen.h"
#include "screen/OptionScreen.h"
#include "screen/HelpScreen.h"
#include "screen/StartScreen.h"
#include "Game.h"

using namespace sfSnake;

PauseScreen::PauseScreen()
    : button_(3)
{
    button_[0].update("assets/image/optionUI.png");
    button_[1].update("assets/image/continueUI.png");
    button_[2].update("assets/image/restartUI.png");

    button_[0].setPosition(Game::GlobalVideoMode.width / 3.0, Game::GlobalVideoMode.height / 5.0 * 3.0);
    button_[1].setPosition(Game::GlobalVideoMode.width / 2.0, Game::GlobalVideoMode.height / 5.0 * 3.0);
    button_[2].setPosition(Game::GlobalVideoMode.width / 3.0 * 2.0, Game::GlobalVideoMode.height / 5.0 * 3.0);
    helpButton_.update("assets/image/helpUI.png", 1 / 16.0f);
    helpButton_.setPosition(
        Game::GlobalVideoMode.width / 15.0 * 14.0,
        Game::GlobalVideoMode.width / 15.0);
}

void PauseScreen::handleInput(sf::RenderWindow &window)
{
    auto mousePosition = sf::Mouse::getPosition(window);

    for (auto &i : button_)
        i.focused(false);
    helpButton_.focused(false);

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
            Game::MainScreen = Game::TmpGameScreen;
            Game::TmpGameScreen = nullptr;
            return;
        }
    }

    if (button_[2].contain(mousePosition))
    {
        button_[2].focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::mouseButtonCDtime = Game::mouseButtonClock.restart();
            Game::mouseButtonLocked = true;
            Game::speedMode=0;
            Game::MainScreen = std::make_shared<StartScreen>();
            return;
        }
    }

    if (helpButton_.contain(mousePosition))
    {
        helpButton_.focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::mouseButtonCDtime = Game::mouseButtonClock.restart();
            Game::mouseButtonLocked = true;
            Game::MainScreen = std::make_shared<HelpScreen>();
            return;
        }
    }
}

void PauseScreen::update(sf::Time delta)
{
    Game::GlobalTitle.update(delta);
}

void PauseScreen::render(sf::RenderWindow &window)
{
    Game::GlobalTitle.render(window);
    for (auto &button : button_)
    {
        button.render(window);
    }
    helpButton_.render(window);
}