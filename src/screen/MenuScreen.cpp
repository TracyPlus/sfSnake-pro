#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "Game.h"
#include "screen/GameScreen.h"
#include "screen/MenuScreen.h"
#include "screen/OptionScreen.h"
#include "screen/HelpScreen.h"
#include "screen/StartScreen.h"

using namespace sfSnake;

MenuScreen::MenuScreen()
    : button_(1)
{
    Game::GlobalFont.loadFromFile("assets/fonts/SourceHanSansSC-Bold.otf");

    button_[0].update("assets/image/startUI.png");
    button_[0].setPosition(Game::GlobalVideoMode.width / 2.0, Game::GlobalVideoMode.height / 5.0 * 3.0);
}

void MenuScreen::handleInput(sf::RenderWindow &window)
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
            Game::mouseButtonLocked = true;
            Game::mouseButtonCDtime = sf::Time::Zero;
            if (!Game::ifShowedHelp)
            {
                Game::TmpScreen = std::make_shared<GameScreen>();
                Game::MainScreen = std::make_shared<StartScreen>();
            }
            else
            {
                Game::MainScreen = std::make_shared<GameScreen>();
                return;
            }
        }
    }
}

void MenuScreen::update(sf::Time delta)
{
    Game::GlobalTitle.update(delta);
}

void MenuScreen::render(sf::RenderWindow &window)
{
    Game::GlobalTitle.render(window);
    for (auto &button : button_)
        button.render(window);
}