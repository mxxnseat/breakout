module;

#include <SFML/Window.hpp>
#include "../events.hpp"

export module Controller;

import EventBus;

export class Controller {
    public:
        Controller(EventBus& event_bus) : event_bus(event_bus) {}
        void poll(float delta_time) const;
        void fire(float delta_time) const;
        void move(float delta_time) const;

    private:
        EventBus& event_bus;
};

void Controller::move(float delta_time) const {
    sf::Vector2f direction = {0.0, 0.0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        direction = {-1.0, 0.0};
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        direction = {1.0, 0.0};
    }

    if (direction.x != 0.0) {
        event_bus.publish(MoveEvent{direction, delta_time});
    }
}

void Controller::fire(float delta_time) const {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        event_bus.publish(FireBallEvent{});
    }
}

void Controller::poll(float delta_time) const {
    move(delta_time);
    fire(delta_time);
}
