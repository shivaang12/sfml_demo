#ifndef SFML_DEMO_BODY_H
#define SFML_DEMO_BODY_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <vector>

#include <sfml_random.hpp>
#include <utils.hpp>
#include <transform.hpp>

enum ShapeType { circle = 0, square = 1 };

class BodyVertices {
public:
    const std::vector<sf::Vector2f> primitive_vertices_;
    std::vector<sf::Vector2f> transformed_vertices_;
    BodyVertices() = default;
    BodyVertices(const std::vector<sf::Vector2f> &vertices) : primitive_vertices_(vertices), transformed_vertices_(vertices) {}
};

class Body {
  public:
    sf::Vector2f position_;
    sf::Vector2f linearVelocity_;
    float rotation_;

    float density_;
    float mass_;
    float restitution_;
    float area_;

    std::unique_ptr<sf::Shape> d_shape_;

    ShapeType shape_type_;

    bool update_required_;

    Body(const sf::Vector2f &position, const float density, const float mass, float restitution,
         float area, ShapeType shape_type)
        : position_(position), linearVelocity_(sf::Vector2f({0.0f, 0.0f})), rotation_(0.0), density_(density),
          mass_(mass), restitution_(restitution), area_(area), shape_type_(shape_type), update_required_(true) {}

    virtual void syncShapePositionWithPosition() = 0;

    void setPosition(sf::Vector2f position) {
        this->position_ = position;
        // this->syncShapePositionWithPosition();
        this->update_required_ = true;
    }

    void updatePosition(const sf::Vector2f &position_difference) {
        this->position_ += position_difference;
        // this->syncShapePositionWithPosition();
        this->update_required_ = true;
    }

    void setRotation(const float &rotation) {
        this->rotation_ = rotation;
        this->update_required_ = true;
    }

    void updateRotation(const float &rotation) {
        this->rotation_ += rotation;
        this->update_required_ = true;
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
        if (update_required_) {
            this->d_shape_->setOrigin({this->radius_, this->radius_});
            this->d_shape_->setPosition(this->position_);
            this->update_required_ = false;
        }
    }
};

class SquareBody : public Body {
  public:
    float width_;
    float height_;

    std::shared_ptr<BodyVertices> vertices_;

    SquareBody(const sf::Vector2f &position, const float &density, const float &mass,
               const float &restitution, const float &area, const float &width, const float &height)
        : Body(position, density, mass, restitution, area, ShapeType::square), width_(width),
          height_(height) {
            // Initialize Vertices
            this->setVertices();
            this->d_shape_ = std::make_unique<sf::RectangleShape>(sf::Vector2f({this->width_, this->height_}));
            syncShapePositionWithPosition();
            const auto &rand_index = generateRandomIntBetweenLimits(0, VALID_COLORS.size() - 1);
            this->d_shape_->setFillColor(VALID_COLORS[rand_index]);
          }

    void syncShapePositionWithPosition() {
        if (update_required_) {
            this->d_shape_->setOrigin({this->width_ / 2.f, this->height_ / 2.f});
            this->d_shape_->setPosition(this->position_);
            this->d_shape_->setRotation(sf::degrees(this->rotation_));

            // Update vertices
            const auto current_transform = Transform2D(this->position_, this->rotation_);

            std::vector<sf::Vector2f> temp_trans(vertices_->primitive_vertices_.size());
            for (int i = 0;i < vertices_->primitive_vertices_.size(); i++) {
                temp_trans[i] = TMath::transform(vertices_->primitive_vertices_[i], current_transform);
            }
            vertices_->transformed_vertices_ = temp_trans;

            this->update_required_ = false;
        }
    }

    /*
    This Function changes position with transform
    */
    void transformUsingTransformation(const Transform2D &transform) {
        
    }

    void setVertices() {
        const float left = -this->width_/2.f;
        const float right = left + this->width_;
        const float up = -this->height_/2.f;
        const float down = up + this->height_;

        std::vector<sf::Vector2f> square_vertices = {sf::Vector2f({left, up}), sf::Vector2f({right, up}), sf::Vector2f({right, down}), sf::Vector2f({left, down})};

        this->vertices_ = std::make_shared<BodyVertices>(square_vertices);
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