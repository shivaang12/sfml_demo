#include <vector>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

#include <transform.hpp>
#include <body.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "SFML works!");

    // sf::RectangleShape shape(sf::Vector2f({50.0f, 50.0f}));
    // std::cout << shape.getLocalBounds().size.x << " " << shape.getLocalBounds().size.y << "\n";

    std::shared_ptr<Body> square_body = createSquareBody(sf::Vector2f({200.0f, 200.0f}), 2.f, 2.f, 100.0f, 100.0f, 0.5f);

    sf::Clock clock;
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float dr = 0.f;
        sf::Vector2f movement(0.f, 0.f);
        bool update = false;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::E)) {
            dr -= 1.f;
            update = true;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::R)) {
            dr += 1.f;
            update = true;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) {
            movement.y -= 1.f;
            update = true;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down)) {
            movement.y += 1.f;
            update = true;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) {
            movement.x -= 1.f;
            update = true;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) {
            movement.x += 1.f;
            update = true;
        }
        
        float e_time = clock.restart().asSeconds();

        std::shared_ptr<SquareBody> s_body = std::static_pointer_cast<SquareBody>(square_body);
        
        if (update) {
            float length = TMath::calculateLengthOfVector(movement);
            const auto direction = TMath::calculateUnitVector(movement);
            s_body->updatePosition(direction * 300.f * e_time);
            s_body->updateRotation(dr * 4.f * e_time);
            s_body->syncShapePositionWithPosition();
        }

        std::vector<sf::CircleShape> corner_vector(4);

        for (int i=0; i<s_body->vertices_->transformed_vertices_.size(); i++) {
            corner_vector[i].setOrigin({10.f, 10.f,});
            corner_vector[i].setPosition((s_body->vertices_->transformed_vertices_)[i]);
            corner_vector[i].setRadius(10.f);
        }

        window.clear();
        window.draw(*(square_body->d_shape_));
        for (int i=0; i<corner_vector.size(); i++) {
            window.draw(corner_vector[i]);
        }
        window.display();
    }

    return 0;
}
