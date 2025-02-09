#ifndef SFML_DEMO_BODY_H
#define SFML_DEMO_BODY_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <stdexcept>

#include <sfml_random.hpp>
#include <utils.hpp>

enum ShapeType { circle = 0, square = 1 };

class Body {
    sf::Vector2f position_;
    sf::Vector2f linearVelocity_;

  public:
    float density_;
    float mass_;
    float restitution_;
    float area_;

    float radius_;
    float width_;
    float height_;

    ShapeType shapeType_;

    sf::CircleShape c_shape_;

    Body(const sf::Vector2f position, const float density, const float mass, float restitution,
         float area, float radius, float width, float height, ShapeType shapeType)
        : position_(position), linearVelocity_(sf::Vector2f({0.0f, 0.0f})), density_(density),
          mass_(mass), restitution_(restitution), area_(area), radius_(radius), width_(width),
          height_(height), shapeType_(shapeType), c_shape_(radius_) {
        // Temporary

        if (shapeType_ == ShapeType::circle) {
            // this->c_shape_.setFillColor(sf::Color::Green);
            const auto &rand_index = generateRandomIntBetweenLimits(0, VALID_COLORS.size() - 1);
            this->c_shape_.setFillColor(VALID_COLORS[rand_index]);
            this->c_shape_.setPosition(this->position_ - this->radius_);
        } else {
            throw std::invalid_argument("Shape not implemented");
        }
    }
};

Body createCircleBody(const sf::Vector2f position, const float density, const float mass,
                      const float radius, const float restitution) {
    float area = radius * radius * M_PI;
    return Body(position, density, mass, restitution, area, radius, 0.f, 0.f, ShapeType::circle);
}

#endif // SFML_DEMO_BODY_H