#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "screen/GameScreen.h"
#include "screen/StartScreen.h"
#include "screen/OptionScreen.h"
#include "Game.h"

using namespace sfSnake;

StartScreen::StartScreen()
    :optionName_(2), DifficultyOptions_(3), DifficultyFocused_(-1)
{ 
    if(!Game::ifShowedHelp) Game::ifShowedHelp = true;

    text_.setFont(Game::GlobalFont);
    text_.setString(
        sf::String(L"(1) 游戏中，按[w/a/s/d]或者[上下左右]键切换方向\n") +
        sf::String(L"(2) 长按空格加速\n") +
        sf::String(L"(3) 或者点击、长按鼠标（左键或右键），指引蛇的移动\n") +
        sf::String(L"(4) 屏幕上有5种不同颜色的水果，它们分别对应于得分：\n") +
        sf::String(L"(5) 黑色、棕色（不得分），红色（3分），蓝色（2分），绿色（1分）\n") +
        sf::String(L"(6) 游戏中会不间断刷新神秘水果（10分）\n") +
        sf::String(L"(7) 按下[G]设置网格开关，按下[B]选择网格颜色、背景颜色\n") +
        sf::String(L"\n") +
        sf::String(L"请先选择游戏难度，按下[Space]开始游戏"));
    text_.setCharacterSize(Game::GlobalVideoMode.width / 35.0f);
    text_.setFillColor(Game::Color::Purple);
    setOriginMiddle(text_);
    text_.setPosition(Game::GlobalVideoMode.width / 2.0, Game::GlobalVideoMode.height / 2.2f);

    float characterSize = Game::GlobalVideoMode.width / 25.f;

    optionName_[0].settings(
        L"游戏规则：",
        Game::GlobalFont,
        characterSize,
        Game::Color::DarkBlue,
        sf::Vector2f(Game::GlobalVideoMode.width / 7.0f, Game::GlobalVideoMode.height / 8.0f));

    optionName_[1].settings(
        L"难度选择：",
        Game::GlobalFont,
        characterSize,
        Game::Color::DarkBlue,
        sf::Vector2f(Game::GlobalVideoMode.width / 7.0f, Game::GlobalVideoMode.height / 5.0 * 4.0f ));

    DifficultyOptions_[0].settings(
        L"简单",
        Game::GlobalFont,
        characterSize,
        Game::Color::NotSeleted,
        sf::Vector2f(Game::GlobalVideoMode.width / 5.0f * 2.0f, Game::GlobalVideoMode.height /  5.0 * 4.0f ));
    DifficultyOptions_[1].settings(
        L"一般",
        Game::GlobalFont,
        characterSize,
        Game::Color::NotSeleted,
        sf::Vector2f(Game::GlobalVideoMode.width / 5.0f * 3.0f, Game::GlobalVideoMode.height /  5.0 * 4.0f ));
    DifficultyOptions_[2].settings(
        L"困难",
        Game::GlobalFont,
        characterSize,
        Game::Color::NotSeleted,
        sf::Vector2f(Game::GlobalVideoMode.width / 5.0f * 4.0f, Game::GlobalVideoMode.height /  5.0 * 4.0f ));
 
}

void StartScreen::handleInput(sf::RenderWindow &window)
{
    auto mousePosition = sf::Mouse::getPosition(window);
    DifficultyFocused_ = -1;

    if (DifficultyOptions_[0].contains(mousePosition))
    {
        DifficultyFocused_ = 0;
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::speedMode = 0.0;
            return;
        }
    }
    if (DifficultyOptions_[1].contains(mousePosition))
    {
        DifficultyFocused_ = 1;
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::speedMode = 1.0;
            return;
        }
    }
    if (DifficultyOptions_[2].contains(mousePosition))
    {
        DifficultyFocused_ = 2;
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::speedMode = 2.0;
            return;
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		sf::sleep(sf::seconds(0.1));
        Game::mouseButtonCDtime = sf::Time::Zero;
        Game::mouseButtonLocked = true;
        Game::MainScreen = std::make_shared<GameScreen>();
        // Game::TmpScreen = nullptr;
        return;
	}

    returnButton_.focused(false);
    if (returnButton_.contain(mousePosition))
    {
        returnButton_.focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::mouseButtonCDtime = sf::Time::Zero;
            Game::mouseButtonLocked = true;
            Game::MainScreen = Game::TmpScreen;
            Game::TmpScreen = nullptr;
            return;
        }
    }
}

void StartScreen::update(sf::Time delta)
{
    Game::GlobalTitle.update(delta);
    for (auto &i : DifficultyOptions_)
        i.clear();
    DifficultyOptions_[int(Game::speedMode)].seleted();
    if (DifficultyFocused_ != -1)
        DifficultyOptions_[DifficultyFocused_].focused();

}

void StartScreen::render(sf::RenderWindow &window)
{
    // Game::GlobalTitle.render(window);
    for (auto &i : optionName_)
        i.render(window);
    for (auto &i : DifficultyOptions_)
        i.render(window);

    returnButton_.render(window);
    window.draw(text_);
}