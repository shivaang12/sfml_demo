#include <cmath>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For Time
#include <iostream>
#include <random>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <body.hpp>
#include <sfml_random.hpp>
#include <utils.hpp>
#include <manual_controller.hpp>
#include <world_physics.hpp>

const int GLOBAL_PADDING = 100;

int main() {
    // Defining Rendering Window
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "SFML works!");

    std::vector<Body> body_list;

    for (int i = 0; i < 10; ++i) {
        float rand_x = generateRandomFloatBetweenLimits(GLOBAL_PADDING, 1920 - GLOBAL_PADDING);
        float rand_y = generateRandomFloatBetweenLimits(GLOBAL_PADDING, 1080 - GLOBAL_PADDING);

        float radius = generateRandomFloatBetweenLimits(20, 50);

        body_list.push_back(
            createCircleBody(sf::Vector2f({rand_x, rand_y}), 2.f, 2.f, radius, 0.5f));
    }

    // Defining Lambda function for closing the window
    const auto onClose = [&window](const sf::Event::Closed &) { window.close(); };

    sf::Clock clock;

    auto player_controller = ManualController(100.f);
    auto physics_engine = WorldPhysics();

    while (window.isOpen()) {
        // std::cout << "Elapsed Time: " << clock.getElapsedTime().asSeconds() << "\n";
        window.handleEvents(onClose);

        window.clear();

        // Assuming body_list[0] is our player
        player_controller.movePlayerUsingInput(body_list[0], clock.getElapsedTime().asSeconds());

        clock.restart();

        // check for collision
        physics_engine.handleCollision(body_list);

        // Draw;
        for (const auto &shape_var : body_list) {
            window.draw(shape_var.c_shape_);
        }

        // Display
        window.display();
    }
}