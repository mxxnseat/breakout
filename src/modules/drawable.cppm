module;

#include <SFML/Graphics.hpp>

export module Drawable;

export class Drawable{
    public:
        virtual ~Drawable() = default;
        virtual void draw(sf::RenderWindow& window) = 0;
};
