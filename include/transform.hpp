#ifndef SFML_DEMO_TRANSFORM_HPP
#define SFML_DEMO_TRANSFORM_HPP

#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

class Transform2D {
public:
    const float x_;
    const float y_;
    const float angle_;
    const float sin_;
    const float cos_;

    Transform2D(const float &x, const float &y, const float &angle) : x_(x), y_(y), angle_(angle), sin_(std::sin(angle_)), cos_(std::cos(angle_)) {}
    Transform2D(const sf::Vector2f &position, const float &angle) : x_(position.x), y_(position.y), angle_(angle), sin_(std::sin(angle_)), cos_(std::cos(angle_)) {}
};

namespace TMath {
    sf::Vector2f transform(const sf::Vector2f &position, const Transform2D &transform) {
        // std::cout << " [TRANSFORM] " << transform.x_ << " " << transform.y_ << " SIN " << transform.sin_ << " cos " << transform.cos_ << "\n";
        const auto rx = position.x * transform.cos_ - position.y * transform.sin_;
        const auto ry = position.x * transform.sin_ + position.y * transform.cos_;

        return sf::Vector2f({rx + transform.x_, ry + transform.y_});
    }

    float dotProduct(const sf::Vector2f &vecA, const sf::Vector2f &vecB) {
        return vecA.x * vecB.x + vecB.y * vecA.y;
    }

    inline float calculateLengthOfVector(const sf::Vector2f &vec) {
        float temp = std::sqrt(dotProduct(vec, vec));
        return temp;
    }

    sf::Vector2f calculateUnitVector(const sf::Vector2f &vec) {
        const auto length = calculateLengthOfVector(vec);

        // Check for Numerical Stability
        if (length < 0.0001f) {
            return sf::Vector2f( {vec.x, vec.y} );
        }
        return sf::Vector2f( {vec.x/length, vec.y/length} );
    }

    sf::Vector2f getTransformedMidPoint(const std::vector<sf::Vector2f> &vert) {
        float total_x = 0.f;
        float total_y = 0.f;

        for (int i = 0; i < vert.size(); i++) {
            total_x += vert[i].x;
            total_y += vert[i].y;
        }

        return {total_x / vert.size(), total_y / vert.size()};
    }
}

#endif // SFML_DEMO_TRANSFORM_HPP