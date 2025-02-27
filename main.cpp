#include <cmath>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For Time
#include <iostream>
#include <random>
#include <vector>
#include <memory>

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

    std::vector<std::shared_ptr<Body>> body_list;

    for (int i = 0; i < 20; ++i) {
        float rand_x = generateRandomFloatBetweenLimits(GLOBAL_PADDING, 1920 - GLOBAL_PADDING);
        float rand_y = generateRandomFloatBetweenLimits(GLOBAL_PADDING, 1080 - GLOBAL_PADDING);

        float radius = generateRandomFloatBetweenLimits(50, 70);

        // body_list.push_back(
        //     createCircleBody(sf::Vector2f({rand_x, rand_y}), 2.f, 2.f, radius, 0.5f));
        
        body_list.push_back(
            createSquareBody(sf::Vector2f({rand_x, rand_y}), 2.f, 2.f, radius, radius, 0.5f));
    }

    // Defining Lambda function for closing the window
    const auto onClose = [&window](const sf::Event::Closed &) { window.close(); };

    sf::Clock clock;

    auto player_controller = ManualController(200.f);
    auto physics_engine = WorldPhysics();

    // sf::RectangleShape rectangle({50.f, 50.f});
    // rectangle.setPosition({80.f, 80.f});
    // rectangle.setRotation(sf::degrees(45.f));
    // std::cout << rectangle.getOrigin().x << " " << rectangle.getOrigin().y << "\n";

    while (window.isOpen()) {
        // std::cout << "Elapsed Time: " << clock.getElapsedTime().asSeconds() << "\n";
        window.handleEvents(onClose);

        window.clear();

        // Assuming body_list[0] is our player
        player_controller.movePlayerUsingInput(body_list[0], clock.restart().asSeconds());

        // check for collision
        physics_engine.handlePolygonsCollision(body_list);

        //
        // std::vector<sf::CircleShape> corner_vector(4*10);

        // for (int i=0; i<body_list.size(); i++) {
        //     std::shared_ptr<SquareBody> s_body = std::static_pointer_cast<SquareBody>(body_list[i]);
        //     for (int j=0; j<s_body->vertices_->transformed_vertices_.size(); j++) {
        //         corner_vector[(4*i)+j].setOrigin({10.f, 10.f,});
        //         corner_vector[(4*i)+j].setPosition((s_body->vertices_->transformed_vertices_)[j]);
        //         corner_vector[(4*i)+j].setRadius(10.f);
        //     }
        // }

        // Draw;
        for (const auto &shape_var : body_list) {
            window.draw(*shape_var->d_shape_);
        }

        // for (int i=0; i<corner_vector.size(); i++) {
        //     window.draw(corner_vector[i]);
        // }
        // window.draw(rectangle);

        // Display
        window.display();
    }
}
