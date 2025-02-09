#ifndef SFML_DEMO_UTILS_H
#define SFML_DEMO_UTILS_H

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

#endif // SFML_DEMO_UTILS_H