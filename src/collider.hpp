#pragma once

#include <SFML/Graphics.hpp>

struct Collider {
    virtual ~Collider() = default;
    virtual sf::FloatRect bounds() const = 0;
};
