#ifndef SFML_DEMO_UTILS_H
#define SFML_DEMO_UTILS_H

#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

// Some serious missing op overloading
namespace sf {
Vector2f operator-(const Vector2f &v, const float &scalar_float) {
    return Vector2f({v.x - scalar_float, v.y - scalar_float});
}

Vector2f operator+(const Vector2f &v, const float &scalar_float) {
    return Vector2f({v.x + scalar_float, v.y + scalar_float});
}
} // namespace sf

std::vector<sf::Color> VALID_COLORS = {sf::Color(52, 82, 74),    sf::Color(162, 232, 221),
                                       sf::Color(184, 12, 9),    sf::Color(107, 43, 6),
                                       sf::Color(229, 231, 230), sf::Color(160, 113, 120),
                                       sf::Color(119, 98, 116)};

float calculateLengthOfVector(const sf::Vector2f &vec) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}
                                       
sf::Vector2f calculateUnitVector(const sf::Vector2f &vec) {
    const auto length = calculateLengthOfVector(vec);
    return sf::Vector2f( {vec.x/length, vec.y/length} );
}
#endif // SFML_DEMO_UTILS_H