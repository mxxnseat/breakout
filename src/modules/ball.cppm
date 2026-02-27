module;

#include <SFML/Graphics.hpp>
#include "SFML/System/Vector3.hpp"
#include "SFML/System/Vector2.hpp"
#include <math.h>

#include "../events.hpp"
#include "../constants.hpp"
#include "../collider.hpp"

export module Ball;

import Drawable;
import EventBus;
import Platform;
import Breaks;

export class Ball : public Drawable, public Collider {
    public:
        Ball(EventBus& event_bus, Platform& platform, Breaks& breaks) :
        event_bus(event_bus),
        platform(platform),
        breaks(breaks),
        ball{CONSTANTS::BALL_RADIUS}
        {
            reset();
            subscribeOnEvents();
        }

        void reset();
        void move(float delta_time);
        void draw(sf::RenderWindow& window) override;
        void subscribeOnEvents();
        sf::FloatRect bounds() const override;
    private:
        sf::CircleShape ball;
        EventBus& event_bus;
        sf::Vector2f direction = {0.0, 0.0};
        Platform& platform;
        Breaks& breaks;
};

void Ball::reset() {
    float x_position = CONSTANTS::WINDOW_WIDTH / 2 - CONSTANTS::BALL_RADIUS/2;
    float y_position = CONSTANTS::WINDOW_HEIGHT - CONSTANTS::PLATFORM_HEIGHT - CONSTANTS::BALL_RADIUS*2;
    ball.setPosition({x_position, y_position});
    ball.setFillColor(CONSTANTS::BALL_COLOR);
    direction = {0.0, 0.0};
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(ball);
}

void Ball::move(float delta_time){
    // Wall collision
    if (ball.getPosition().x < 0 || ball.getPosition().x > CONSTANTS::WINDOW_WIDTH-CONSTANTS::BALL_RADIUS) {
        if (ball.getPosition().x <= 0) {
            ball.setPosition({0, ball.getPosition().y});
        } else {
            ball.setPosition({CONSTANTS::WINDOW_WIDTH-CONSTANTS::BALL_RADIUS, ball.getPosition().y});
        }
        direction.x = -direction.x;
    }
    if (ball.getPosition().y < 0) {
        ball.setPosition({ball.getPosition().x, 0});
        direction.y = -direction.y;
    }
    if(ball.getPosition().y >= CONSTANTS::WINDOW_HEIGHT) {
        event_bus.publish(GameOverEvent{});
        return;
    }
    // Breaks collision
    for (const auto& break_ : breaks.getBreaks()) {
        auto intersection = break_->bounds().findIntersection(ball.getGlobalBounds());
        if (intersection) {
            direction.x = direction.x;
            direction.y = -direction.y;
            event_bus.publish(BreakBreakEvent{break_->getOffset()});
            break;
        }
        
    }

    // Platform collision
    auto intersection = platform.bounds().findIntersection(ball.getGlobalBounds());
    if (intersection && direction.y > 0.0) {
        float platform_top = platform.bounds().position.y;
        float platform_left   = platform.bounds().position.x;
        float platform_width  = platform.bounds().size.x;
        float platform_center = platform_left + platform_width * 0.5f;

        float ball_x = ball.getPosition().x;

        float hit_point_x = (ball_x - platform_center) / (platform_width * 0.5f);
        if (hit_point_x < -1.f) hit_point_x = -1.f;
        if (hit_point_x >  1.f) hit_point_x =  1.f;

        const float maxAngle = 75.f * M_PI / 180.f;
        float angle = hit_point_x * maxAngle;

        float speed = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        direction.x = speed*std::sin(angle);
        direction.y = -speed*std::cos(angle);

        sf::Vector2f pos = ball.getPosition();
        pos.y = platform_top - CONSTANTS::BALL_RADIUS;
        ball.setPosition(pos);
    }

    float x_velocity = direction.x * delta_time;
    float y_velocity = direction.y * delta_time;
    ball.move({x_velocity, y_velocity});

}

void Ball::subscribeOnEvents(){
    event_bus.subscribe<FireBallEvent>([this](const FireBallEvent& event){
        direction = {0.0*CONSTANTS::BALL_SPEED, -1.0*CONSTANTS::BALL_SPEED};
    });
}

sf::FloatRect Ball::bounds() const {
    return ball.getGlobalBounds();
}