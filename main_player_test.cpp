#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include <transform.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "SFML works!");

    sf::RectangleShape shape(sf::Vector2f({50.0f, 50.0f}));
    // std::cout << shape.getLocalBounds().size.x << " " << shape.getLocalBounds().size.y << "\n";
    shape.setOrigin({shape.getLocalBounds().size.x / 2, shape.getLocalBounds().size.y / 2});

    shape.setFillColor(sf::Color::Green);

    shape.setPosition(sf::Vector2f({100.0f, 100.0f}));

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

        // if (dx != 0 || dy != 0 || dr!= 0) {
        //     auto direction = TMath::calculateUnitVector(sf::Vector2f({(float)dx, (float)dy}));
        //     float rotation_radian = (float)dr * 0.01f;

        //     auto velocity = direction * 300.f *  e_time;

        //     std::cout << shape.getRotation().asRadians() << " " << rotation_radian << " " << e_time <<  "\n";

        //     shape.rotate(sf::radians(rotation_radian));
        //     // shape.move(velocity);
        //     // shape.setOrigin({shape.getLocalBounds().size.x / 2, shape.getLocalBounds().size.y / 2});
        // }
        
        float e_time = clock.restart().asSeconds();
        
        if (update) {
            float length = TMath::calculateLengthOfVector(movement);
            const auto direction = TMath::calculateUnitVector(movement);
            shape.move(direction * 300.f * e_time);
            shape.rotate(sf::radians(dr * 10.f * e_time));
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
