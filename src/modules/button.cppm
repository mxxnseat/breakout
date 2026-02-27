module;

#include <SFML/Graphics.hpp>
#include <functional>

#include "../constants.hpp"

export module Button;

export class Button {
    public:
        Button(const std::string& text_) : 
        button{{CONSTANTS::BUTTON_WIDTH, CONSTANTS::BUTTON_HEIGHT}},
        font("assets/font.ttf"),
        text(font, text_)
        {
            text.setCharacterSize(CONSTANTS::BUTTON_TEXT_SIZE);
            text.setFillColor(CONSTANTS::BUTTON_TEXT_COLOR);
            text.setPosition({float(CONSTANTS::WINDOW_WIDTH / 2- text.getGlobalBounds().size.x / 2), float(CONSTANTS::WINDOW_HEIGHT / 2- text.getGlobalBounds().size.y)});

            button.setFillColor(CONSTANTS::BUTTON_COLOR);
            button.setPosition({CONSTANTS::WINDOW_WIDTH / 2 - CONSTANTS::BUTTON_WIDTH / 2, CONSTANTS::WINDOW_HEIGHT / 2 - CONSTANTS::BUTTON_HEIGHT / 2});
        }

        void setOnClickHandler(std::function<void()> handler_) {
            handler = std::move(handler_);
        }

        void onClick() {
            if (handler) {
                handler();
            }
        }

        void draw(sf::RenderWindow& window) {
            window.draw(button);
            window.draw(text);
        }

        bool contains(const sf::Vector2f& point) const {
            return button.getGlobalBounds().contains(point);
        }

    private:
        sf::RectangleShape button;
        sf::Font font;
        sf::Text text;
        std::function<void()> handler;
};