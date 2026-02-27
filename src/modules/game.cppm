module;

#include <SFML/Graphics.hpp>
#include "SFML/Window/Mouse.hpp"

#include "../constants.hpp"
#include "../events.hpp"

export module Game;

import Platform;
import Controller;
import Drawable;
import EventBus;
import Ball;
import Breaks;
import Button;

enum class GameState {STARTED, GAME_OVER};

export class Game {
    public:
        Game(unsigned int window_width, unsigned int window_height) : 
        event_bus(),
        controller(event_bus),
        window(sf::VideoMode({window_width, window_height}), "Breakout"),
        clock(),
        window_width(window_width),
        window_height(window_height),
        ball(event_bus, platform, breaks),
        platform(event_bus, CONSTANTS::PLATFORM_WIDTH, CONSTANTS::PLATFORM_HEIGHT),
        breaks(event_bus),
        game_over_button("Game Over")
        {
            window.setFramerateLimit(60);
            window.clear(CONSTANTS::WINDOW_COLOR);
            game_over_button.setOnClickHandler([this]() {
                game_state = GameState::STARTED;
                reset();
            });
            subscribeOnEvents();
        };

        void reset();
        void run();
        void processEvents();
        void draw();

        void gameOverScreen(float delta_time);
        void startedScreen(float delta_time);
        void subscribeOnEvents();
    private:
        EventBus event_bus;
        Ball ball;
        Platform platform;
        Breaks breaks;
        Controller controller;
        sf::RenderWindow window;
        sf::Clock clock;
        int window_width;
        int window_height;
        GameState game_state = GameState::STARTED;
        Button game_over_button;
};


void Game::reset() {
    ball.reset();
    platform.reset(CONSTANTS::PLATFORM_WIDTH, CONSTANTS::PLATFORM_HEIGHT);
    breaks.reset();
}

void Game::draw() {
    ball.draw(window);
    platform.draw(window);
    breaks.draw(window);
}

void Game::processEvents() {
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            auto p = sf::Mouse::getPosition(window);
            if (game_over_button.contains({float(p.x), float(p.y)})) {
                game_over_button.onClick();
            }
        }
    }
}

void Game::gameOverScreen(float delta_time) {
    processEvents();
    window.clear(CONSTANTS::WINDOW_COLOR);
    game_over_button.draw(window);
    window.display();
}

void Game::startedScreen(float delta_time) {
    processEvents();
    controller.poll(delta_time);
    window.clear(CONSTANTS::WINDOW_COLOR);
    draw();
    ball.move(delta_time);
    window.display();
}

void Game::subscribeOnEvents() {
    event_bus.subscribe<GameOverEvent>([this](const GameOverEvent& event) {
        game_state = GameState::GAME_OVER;
    });
}

void Game::run() {
    while (window.isOpen())
    {
        float delta_time = clock.restart().asSeconds();

        switch (game_state) {
            case GameState::STARTED:
                startedScreen(delta_time);
                break;
            case GameState::GAME_OVER:
                gameOverScreen(delta_time);
                break;
        }
    }
}