#pragma once

// #include <SFML/Graphics.hpp>

// namespace sfSnake
// {
//     struct Fruit
//     {
//         sf::CircleShape shape_;
//         int score_;

//         Fruit(sf::Vector2f position, sf::Color color, int score);
//         Fruit(sf::Vector2f position, const std::string& imagePath, int score);

//         void render(sf::RenderWindow &window);
//     };
// }

#include <SFML/Graphics.hpp>

namespace sfSnake
{
    class Fruit
    {
    public:
        // Fruit(sf::Vector2f position = sf::Vector2f(0, 0));
        Fruit(sf::Vector2f position, sf::Color color, int score);
        Fruit(sf::Vector2f position, const std::string& imagePath, int score);

        void render(sf::RenderWindow& window);

        sf::FloatRect getBounds() const;
        sf::CircleShape shape(){return shape_;};
        sf::Color color(){return color_;};
        void color_change(){shape_.setFillColor(color_);};
        void setcolor(sf::Color colors){color_=colors;};

        sf::CircleShape shape_;
        int score_;
        sf::Color color_;
        static const float Radius;
        sf::Texture texture;
    };
}
