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

std::vector<sf::Vector2f> squareTypeOne() {
    return {{2.f, 2.f}, {2.f, 3.f}, {3.f, 3.f}, {3.f, 2.f}};
}
std::vector<sf::Vector2f> squareTypeTwo() {
    return {{3.1f, 2.5f}, {4.1f, 3.5f}, {5.1f, 2.5f}, {4.1f, 1.5f}};
}

std::vector<sf::Vector2f> squareTypeThree() {
    return {{1409.54, 536.06}, {1453.31,494.942}, {1494.43,538.719},{1450.65,579.838}};
}

std::vector<sf::Vector2f> squareTypeFour() {
    return {{1313.02 ,507.374} , {1382.63 ,507.374},  {1382.63, 576.985},  {1313.02, 576.985}};
}


int main() {
    // Need to define two triangles (transformed)
    const auto &triangle_1 = squareTypeThree();
    const auto &triangle_2 = squareTypeFour();//triangleTypeTwo();

    const auto wp = WorldPhysics();

    // Check if Collision
    sf::Vector2f normal_of_collision = sf::Vector2f({0.f, 0.f});
    float depth_of_collision = 0.f;

    auto b_value = wp.intersectPolygons(triangle_1, triangle_2, normal_of_collision, depth_of_collision);

    std::cout << "Triangles 1 and 2 intersect? " << b_value << " Normal " << normal_of_collision.x << " " << normal_of_collision.y << " Depth " << depth_of_collision << "\n";
}