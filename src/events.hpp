#pragma once

#include <SFML/Graphics.hpp>

struct MoveEvent {
    sf::Vector2f direction;
    float delta_time;
};

struct FireBallEvent {};

struct BreakBreakEvent {
    int offset;
};

struct GameOverEvent {};