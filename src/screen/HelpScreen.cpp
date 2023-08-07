#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "screen/GameScreen.h"
#include "screen/HelpScreen.h"
#include "screen/OptionScreen.h"
#include "screen/PauseScreen.h"
#include "Game.h"

using namespace sfSnake;

HelpScreen::HelpScreen()
    :optionName_(1), DifficultyOptions_(3), DifficultyFocused_(-1)
{ 
    if(!Game::ifShowedHelp) Game::ifShowedHelp = true;

    text_.setFont(Game::GlobalFont);
    text_.setString(
        sf::String(L"游戏中，按[w/a/s/d]或者[上下左右]键切换方向\n") +
        sf::String(L"长按空格加速\n") +
        sf::String(L"或者点击、长按鼠标（左键或右键），指引蛇的移动\n") +
        sf::String(L"屏幕上有5种不同颜色的水果，它们分别对应于得分：\n") +
        sf::String(L"黑色、棕色（不得分），红色（3分），蓝色（2分），绿色（1分）\n") +
        sf::String(L"游戏中会不间断刷新神秘水果（10分）\n") +
        sf::String(L"按下[G]设置网格开关，按下[B]选择网格颜色、背景颜色"));
    text_.setCharacterSize(Game::GlobalVideoMode.width / 35.0f);
    text_.setFillColor(Game::Color::Purple);
    setOriginMiddle(text_);
    text_.setPosition(Game::GlobalVideoMode.width / 2.0, Game::GlobalVideoMode.height / 10.0 * 7.0);

    returnButton_.update("assets/image/returnUI.png", 1 / 16.0f);
    returnButton_.setPosition(Game::GlobalVideoMode.width / 15.0f, Game::GlobalVideoMode.width / 15.0f);
}

void HelpScreen::handleInput(sf::RenderWindow &window)
{
    auto mousePosition = sf::Mouse::getPosition(window);

    returnButton_.focused(false);
    if (returnButton_.contain(mousePosition))
    {
        returnButton_.focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::mouseButtonCDtime = sf::Time::Zero;
            Game::mouseButtonLocked = true;
            Game::MainScreen = std::make_shared<PauseScreen>();
            // Game::TmpScreen = nullptr;
            return;
        }
    }
}

void HelpScreen::update(sf::Time delta)
{
    Game::GlobalTitle.update(delta);
}

void HelpScreen::render(sf::RenderWindow &window)
{
    Game::GlobalTitle.render(window);
    returnButton_.render(window);
    window.draw(text_);
}