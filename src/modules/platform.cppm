module;

#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Rect.hpp"

#include "../constants.hpp"
#include "../events.hpp"
#include "../collider.hpp"

export module Platform;

import Drawable;
import EventBus;


export class Platform : public Drawable, public Collider     {
    public:
        Platform(EventBus& event_bus, float width, float height) :
        platform{{width, height}},
        event_bus{event_bus}
        {
            reset(width, height);
            subscribeOnEvents();
        }

        void move(const MoveEvent& event);
        void draw(sf::RenderWindow& window) override;
        void subscribeOnEvents();
        void fire();
        sf::FloatRect bounds() const override;
        void reset(float width, float height);
    private:
        bool has_fired = false;
        sf::RectangleShape platform;
        EventBus& event_bus;
};

sf::FloatRect Platform::bounds() const {
    return platform.getGlobalBounds();
}

void Platform::move(const MoveEvent& event) {
    if (!has_fired) return;
    float x_velocity = event.direction.x * event.delta_time * CONSTANTS::PLATFORM_SPEED;
    float new_x = platform.getPosition().x + x_velocity;
    if (new_x <= -platform.getSize().x || new_x > CONSTANTS::WINDOW_WIDTH) {
        return;
    }
    platform.move({x_velocity, 0.0});
}

void Platform::fire() {
    has_fired = true;
}

void Platform::draw(sf::RenderWindow& window) {
    window.draw(platform);
}

void Platform::reset(float width, float height) {
    float x_position = CONSTANTS::WINDOW_WIDTH / 2 - width / 2;
    float y_position = CONSTANTS::WINDOW_HEIGHT - height;
    platform.setPosition({x_position, y_position});
    platform.setFillColor(CONSTANTS::PLATFORM_COLOR);
}

void Platform::subscribeOnEvents() {
    event_bus.subscribe<MoveEvent>([this](const MoveEvent& event) {
        move(event);
    });
    event_bus.subscribe<FireBallEvent>([this](const FireBallEvent& event) {
        fire();
    });
}