module;


#include <SFML/Graphics.hpp>

#include "../constants.hpp"
#include "../collider.hpp"
#include "../events.hpp"
#include <iostream>

export module Breaks;

import Drawable;
import EventBus;

export class Break : public Drawable, public Collider {
    public:
        Break(int offset, float y) : 
        offset(offset),
        break_{{float(CONSTANTS::WINDOW_WIDTH/CONSTANTS::BREAK_WIDTH_COUNT), CONSTANTS::BREAK_HEIGHT}}
        {
            float width = float(CONSTANTS::WINDOW_WIDTH/CONSTANTS::BREAK_WIDTH_COUNT);
            break_.setPosition({width * offset, y});
            break_.setOutlineThickness(1);
            break_.setOutlineColor(sf::Color::Black);
            break_.setFillColor(CONSTANTS::BREAK_COLOR);
        }
        void draw(sf::RenderWindow& window) override {
            window.draw(break_);
        }
        sf::FloatRect bounds() const override {
            return break_.getGlobalBounds();
        }
        int getOffset() const {
            return offset;
        }

    private:
        int offset;
        sf::RectangleShape break_;
};

export class Breaks : public Drawable {
    public:
        Breaks(EventBus& event_bus) : event_bus(event_bus)  {
            for (int i = 0; i < CONSTANTS::BREAK_WIDTH_COUNT; i++) {
                breaks.push_back(std::make_unique<Break>(i, 0));
            }
            subscribeOnEvents();
        }
        void draw(sf::RenderWindow& window) override {
            for (const auto& break_ : breaks) {
                break_->draw(window);
            }
        }
        std::vector<std::unique_ptr<Break>>& getBreaks()  {
            return breaks;
        }
        void breakBreak(const BreakBreakEvent& event) {
            breaks.erase(std::remove_if(breaks.begin(), breaks.end(), [&](std::unique_ptr<Break>& break_){
                return break_->getOffset() ==event.offset;
            }), breaks.end());
        }
        void subscribeOnEvents();
        void reset();
    private:
        std::vector<std::unique_ptr<Break>> breaks;
        EventBus& event_bus;
};

void Breaks::subscribeOnEvents() {
    event_bus.subscribe<BreakBreakEvent>([this](const BreakBreakEvent& event){
        breakBreak(event);
    });
}

void Breaks::reset() {
    breaks.clear();
    for (int i = 0; i < CONSTANTS::BREAK_WIDTH_COUNT; i++) {
        breaks.push_back(std::make_unique<Break>(i, 0));
    }
}