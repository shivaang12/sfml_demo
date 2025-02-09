#ifndef SFML_DEMO_MANUAL_CONTROLLER_H
#define SFML_DEMO_MANUAL_CONTROLLER_H

#include <SFML/Graphics.hpp>

#include <utils.hpp>
#include <body.hpp>

class ManualController {

public:
    ManualController(const float &speed) : speed_(speed) {
    }

    void movePlayerUsingInput(Body &player, const float &elapsed_time) const {
        int dx = 0;
        int dy = 0;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) {
            dy--;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down)) {
            dy++;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) {
            dx--;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) {
            dx++;
        }

        if (dx != 0 || dy != 0) {
            auto direction = calculateUnitVector(sf::Vector2f({(float)dx, (float)dy}));
            // TODO: 
            auto velocity = direction * this->speed_ * elapsed_time;
            player.movePosition(velocity);
        }
    }

    void updateSpeed (const float &speed) {
        speed_ = speed;
    }

    float speed_;
};

#endif // SFML_DEMO_MANUAL_CONTROLLER_H