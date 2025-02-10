#ifndef SFML_DEMO_BODY_H
#define SFML_DEMO_BODY_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <memory>

#include <sfml_random.hpp>
#include <utils.hpp>

enum ShapeType { circle = 0, square = 1 };

class Body {
  public:
    sf::Vector2f position_;
    sf::Vector2f linearVelocity_;

    float density_;
    float mass_;
    float restitution_;
    float area_;

    std::unique_ptr<sf::Shape> d_shape_;

    ShapeType shape_type_;

    Body(const sf::Vector2f &position, const float density, const float mass, float restitution,
         float area, ShapeType shape_type)
        : position_(position), linearVelocity_(sf::Vector2f({0.0f, 0.0f})), density_(density),
          mass_(mass), restitution_(restitution), area_(area), shape_type_(shape_type) {}

    virtual void syncShapePositionWithPosition() = 0;

    void updatePosition(sf::Vector2f position) {
        this->position_ = position;
        this->syncShapePositionWithPosition();
    }

    void movePosition(const sf::Vector2f &position_difference) {
        this->position_ += position_difference;
        this->syncShapePositionWithPosition();
    }
    sf::Vector2f getPosition() const { return position_; }
};

class CircleBody : public Body {

  public:
    float radius_;
    // sf::CircleShape d_shape_;

    CircleBody(const sf::Vector2f &position, const float &density, const float &mass,
               const float &restitution, const float &area, const float &radius)
        : Body(position, density, mass, restitution, area, ShapeType::circle), radius_(radius) {
            this->d_shape_ = std::make_unique<sf::CircleShape>(this->radius_);
            syncShapePositionWithPosition();
            const auto &rand_index = generateRandomIntBetweenLimits(0, VALID_COLORS.size() - 1);
            this->d_shape_->setFillColor(VALID_COLORS[rand_index]);
        }

    void syncShapePositionWithPosition() {
        this->d_shape_->setPosition(this->position_ - this->radius_);
    }
};

class SquareBody : public Body {
  public:
    float width_;
    float height_;

    SquareBody(const sf::Vector2f &position, const float &density, const float &mass,
               const float &restitution, const float &area, const float &width, const float &height)
        : Body(position, density, mass, restitution, area, ShapeType::square), width_(width),
          height_(height) {
            d_shape_ = std::make_unique<sf::RectangleShape>(sf::Vector2f({this->width_, this->height_}));
            syncShapePositionWithPosition();
            const auto &rand_index = generateRandomIntBetweenLimits(0, VALID_COLORS.size() - 1);
            this->d_shape_->setFillColor(VALID_COLORS[rand_index]);
          }

    void syncShapePositionWithPosition() {
        this->d_shape_->setPosition(this->position_ -
                                   sf::Vector2f({this->width_ / 2.f, this->height_ / 2.f}));
    }
};

std::shared_ptr<Body> createCircleBody (const sf::Vector2f position, const float density, const float mass,
                       const float radius, const float restitution) {
    float area = radius * radius * M_PI;
    std::shared_ptr<Body> ptr = std::make_shared<CircleBody>(position, density, mass, restitution, area, radius);
    return ptr;
}

std::shared_ptr<Body> createSquareBody(const sf::Vector2f position, const float density, const float mass,
                      const float width, const float height, const float restitution) {
    float area = width * height;
    std::shared_ptr<Body> ptr = std::make_shared<SquareBody>(position, density, mass, restitution, area, width, height);
    return ptr;
}

#endif // SFML_DEMO_BODY_H