#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include <world_physics.hpp>
#include <transform.hpp>

std::vector<sf::Vector2f> triangleTypeOne() {
    return {{3.f, 5.f}, {5.f, 7.f}, {6.f, 4.f}};
}

std::vector<sf::Vector2f> triangleTypeTwo() {
    return {{3.f, 3.f}, {5.f, 2.f}, {2.f, 1.f}};
}

std::vector<sf::Vector2f> triangleTypeThree() {
    return {{5.f, 5.f}, {7.f, 7.f}, {7.f, 2.f}};
}

int main() {
    // Need to define two triangles (transformed)
    const auto &triangle_1 = triangleTypeOne();
    const auto &triangle_2 = triangleTypeTwo();//triangleTypeTwo();

    const auto wp = WorldPhysics();

    std::cout << "Triangles 1 and 2 intersect? " << wp.intersectPolygons(triangle_1, triangle_2) << "\n";
}