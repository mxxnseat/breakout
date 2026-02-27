#pragma once

#include "SFML/Graphics/Color.hpp"

namespace CONSTANTS {
    // Window constants
    inline constexpr double WINDOW_WIDTH = 800.0;
    inline constexpr double WINDOW_HEIGHT = 800.0;
    inline constexpr sf::Color WINDOW_COLOR = sf::Color::Blue;

    // Platform constants
    inline constexpr double PLATFORM_SPEED = 300.0;
    inline constexpr double PLATFORM_WIDTH = 180.0;
    inline constexpr double PLATFORM_HEIGHT = 15.0;
    inline constexpr sf::Color PLATFORM_COLOR{226,10,183};

    // Ball constants
    inline constexpr double BALL_SPEED = 500.0;
    inline constexpr double BALL_RADIUS = 15.0;
    inline constexpr sf::Color BALL_COLOR{26,215,26};

    // Break constants
    inline constexpr double BREAK_WIDTH_COUNT = 15;
    inline constexpr double BREAK_HEIGHT = 14;
    inline constexpr sf::Color BREAK_COLOR{255,255,255};

    // Button constants
    inline constexpr double BUTTON_WIDTH = 250.0;
    inline constexpr double BUTTON_HEIGHT = 80.0;
    inline constexpr sf::Color BUTTON_COLOR{255,255,255};
    inline constexpr sf::Color BUTTON_TEXT_COLOR{127,127,127};
    inline constexpr int BUTTON_TEXT_SIZE = 48;
}