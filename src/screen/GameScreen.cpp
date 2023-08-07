#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>

#include <random>
#include <memory>
#include <iostream>

#include "screen/GameScreen.h"
#include "screen/GameOverScreen.h"
#include "screen/PauseScreen.h"
#include "screen/HelpScreen.h"

using namespace sfSnake;
int colorCount[4];
bool has_gift;
static int records=0;
bool has_grid = false;

GameScreen::GameScreen()
    : snake_(), grid_(), pauseButton_()
{
    pauseButton_.update("assets/image/pauseUI.png", 1 / 16.0f);
    pauseButton_.setPosition(
        Game::GlobalVideoMode.width / 15.0 * 14.0,
        Game::GlobalVideoMode.width / 15.0);

    score_.setFont(Game::GlobalFont);
    score_.setString(sf::String(L"分数:") + std::to_string(snake_.getScore()));
    score_.setCharacterSize(Game::GlobalVideoMode.width / 25.0f);
    score_.setFillColor(Game::Color::DarkBlue);
    setOriginMiddle(score_);
    score_.setPosition(
        Game::GlobalVideoMode.width / 2.0f,
        Game::GlobalVideoMode.width * 0.05f);
    colorCount[0]=colorCount[1]=colorCount[2]=colorCount[3]=0;
    has_gift = false;
}

void GameScreen::handleInput(sf::RenderWindow &window)
{
    snake_.handleInput(window);

    auto mousePosition = sf::Mouse::getPosition(window);

    pauseButton_.focused(false);

    if (pauseButton_.contain(mousePosition))
    {
        pauseButton_.focused(true);
        if (
            !Game::mouseButtonLocked &&
            sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::mouseButtonCDtime = sf::Time::Zero;
            Game::mouseButtonLocked = true;
            Game::TmpGameScreen = Game::MainScreen;
            Game::MainScreen = std::make_shared<PauseScreen>();
            return;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
		sf::sleep(sf::seconds(0.1));
        records++;
		records %= 3;
        if (has_grid == false)
            Game::BackgroundColor = records;
        else if (has_grid == true)
            Game::GridColor = records;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
		sf::sleep(sf::seconds(0.1));
		if (has_grid == false)
        {
			has_grid = true;
            Game::GridVisibility = 1;
        }
        else
        {
            has_grid = false;
            Game::GridVisibility = 0;
        }
    }
    else {}
}

void GameScreen::update(sf::Time delta)
{
    while (fruit_.size() < 20)
        generateFruit();
    while (!has_gift && snake_.getScore() > 10) 
        generateGift();
    snake_.update(delta);
    snake_.checkFruitCollisions(fruit_, colorCount, &has_gift);
    if (snake_.hitSelf())
    {
        Game::MainScreen = std::make_shared<GameOverScreen>(snake_.getScore());
    }

    score_.setString(sf::String(L"分数:\t") + std::to_string(snake_.getScore()));
}

void GameScreen::render(sf::RenderWindow &window)
{
    sf::Texture tex; 
    if (Game::GridVisibility)
        grid_.render(window);
    snake_.render(window);
    for (auto fruit : fruit_)
        fruit.render(window);
    pauseButton_.render(window);
    window.draw(score_);
}

void GameScreen::generateFruit()
{
    static std::default_random_engine engine(time(NULL));
    static std::default_random_engine colorEngine(time(NULL));

    static std::uniform_int_distribution<int> xPos(
        Game::GlobalVideoMode.width / 15.0f,
        Game::GlobalVideoMode.width - Game::GlobalVideoMode.width / 10.0f);

    static std::uniform_int_distribution<int> yPos(
        Game::GlobalVideoMode.width / 10.0f,
        Game::GlobalVideoMode.height - Game::GlobalVideoMode.width / 15.0f);

    static std::uniform_int_distribution<int> fruitColor1(0, 1);
    static std::uniform_int_distribution<int> fruitColor2(0, 2);

    if((colorCount[0]) < fruit_.size() * 0.25) 
    {
        switch (fruitColor1(colorEngine))
        {
            case 0: // black
                fruit_.push_back(Fruit(
                    sf::Vector2f(xPos(engine), yPos(engine)),
                    Game::Color::Fruit[0],
                    0));
                colorCount[0]++;
                break;
            case 1: // brown
                fruit_.push_back(Fruit(
                    sf::Vector2f(xPos(engine), yPos(engine)),
                    Game::Color::Fruit[1],
                    0));
                colorCount[0]++;
                break;
            default:
                break;  
        }
    }
    else 
    {
        switch (fruitColor2(colorEngine))
        {
            case 0:// red
                fruit_.push_back(Fruit(
                    sf::Vector2f(xPos(engine), yPos(engine)),
                    Game::Color::Fruit[2],
                    3));
                colorCount[3]++;                
                break;
            case 1:// blue
                fruit_.push_back(Fruit(
                    sf::Vector2f(xPos(engine), yPos(engine)),
                    Game::Color::Fruit[3],
                    2));
                colorCount[2]++;
                break;
            case 2: // green
                fruit_.push_back(Fruit(
                    sf::Vector2f(xPos(engine), yPos(engine)),
                    Game::Color::Fruit[4],
                    1));
                colorCount[1]++;
                break;
            default:
                break;
        }
    }
}

void GameScreen::generateGift()
{
    static std::default_random_engine engine(time(NULL));
    static std::default_random_engine colorEngine(time(NULL));

    static std::uniform_int_distribution<int> xPos(
        Game::GlobalVideoMode.width / 15.0f,
        Game::GlobalVideoMode.width - Game::GlobalVideoMode.width / 10.0f);

    static std::uniform_int_distribution<int> yPos(
        Game::GlobalVideoMode.width / 10.0f,
        Game::GlobalVideoMode.height - Game::GlobalVideoMode.width / 15.0f);
    
    static std::uniform_int_distribution<int> fruitType(0, 4);
    switch (fruitType(colorEngine)) 
    {
        case 0:
            fruit_.push_back(Fruit(
                sf::Vector2f(xPos(engine), yPos(engine)),
                "assets/image/strawberry.png",
                5));
            has_gift = true;
            break;
        case 1:
            fruit_.push_back(Fruit(
                sf::Vector2f(xPos(engine), yPos(engine)),
                "assets/image/banana.png",
                5));
            has_gift = true;
            break;
        case 2:
            fruit_.push_back(Fruit(
                sf::Vector2f(xPos(engine), yPos(engine)),
                "assets/image/apple.png",
                5));
            has_gift = true;
            break;
        case 3:
            fruit_.push_back(Fruit(
                sf::Vector2f(xPos(engine), yPos(engine)),
                "assets/image/pomegranate.png",
                5));
            has_gift = true;
            break;
        case 4:
            fruit_.push_back(Fruit(
                sf::Vector2f(xPos(engine), yPos(engine)),
                "assets/image/orange.png",
                5));
            has_gift = true;
            break;
        default:
            break;
    }
}