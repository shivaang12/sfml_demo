#include <cstdlib>  // For rand() and srand()
#include <ctime> // For Time
#include <random>
#include <cmath>

#include <SFML/Graphics.hpp>

// Some serious missing op overloading
namespace sf {
    Vector2f operator-(const Vector2f& v, const float& scalar_float){
        return Vector2f({v.x - scalar_float, v.y - scalar_float});
    }

    Vector2f operator+(const Vector2f& v, const float& scalar_float){
        return Vector2f({v.x + scalar_float, v.y + scalar_float});
    }
}

// Collision checking function
void HandleWindowCollision(const sf::CircleShape &cirShape, const sf::Vector2u &window_size,
    sf::Vector2f& shapeDir, const float& speed) {
    const auto &wsize = window_size;

    const auto &shapeRad = cirShape.getRadius();
    const auto &shapePosNorm = cirShape.getPosition() + shapeRad; // Normalized Postion

    const auto &futPos = shapePosNorm + (shapeDir * speed);

    if ( futPos.x - shapeRad < 0.0f ) {
        shapeDir.x *= -1.0f;
    }

    if (futPos.x + shapeRad >= wsize.x) {
        shapeDir.x *= -1.0f;
    }

    if (futPos.y - shapeRad < 0.0f) {
        shapeDir.y *= -1.0f;
    }

    if (futPos.y + shapeRad >= wsize.y) {
        shapeDir.y *= -1.0f;
    }

    return;
}

sf::Vector2f RandomInitialPosition(const sf::Vector2u& windowSize, const float& circleRad) {

    // Seed random number generator
    std::srand(std::time(nullptr));

    // Nomalize to valid width and heigth
    const float &validWidth = windowSize.x - (2 * circleRad);
    const float &validHeight = windowSize.y - (2 * circleRad);

    const float& randWidth = (1 + (std::rand() % int(validWidth))) + circleRad ;
    const float& randHeigth = (1 + (std::rand() % int(validHeight))) + circleRad ;

    return sf::Vector2f({randWidth, randHeigth});
}

sf::Vector2f RandomInitialDirection() {
    // Create a random device (for non-deterministic seeding)
    std::random_device rd;

    // Use Mersenne Twister engine
    std::mt19937 gen(rd());

    // Define a uniform real distribution between 0.0 and 1.0
    std::uniform_real_distribution<float> dist(0.0, 1.0);

    // Generate a random floating-point number
    float dirX = dist(gen);
    float dirY = dist(gen);

    // Calculating Norm
    float normXY = std::sqrt(dirX*dirX + dirY*dirY);

    // Dividing with Norm to get Unit Vector
    return sf::Vector2f({dirX/normXY, dirY/normXY});
}

int main()
{
    // Defining Rendering Window
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "SFML works!");

    // Defining circle radius
    const float circleRadius= 100.f;

    // Get random initial position for circle
    auto shapePos = RandomInitialPosition(window.getSize(), circleRadius);

    // Defining our Circle object
    sf::CircleShape shape(circleRadius);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(
        shapePos - shape.getRadius()
    );

    // Defining Direction
    auto shapeDir = RandomInitialDirection();

    // Defining Speed
    float speed = 0.05f;

    // Defining Lambda function for closing the window
    const auto onClose = [&window](const sf::Event::Closed&){
        window.close();
    };

    // Defining Lambda function for adjusting the speed for the ball
    const auto onKeyPressed = [&speed](const sf::Event::KeyPressed& keyPressed){
        if (keyPressed.scancode == sf::Keyboard::Scancode::I) {
            speed = speed - 0.01;
        } else if (keyPressed.scancode == sf::Keyboard::Scancode::O) {
            speed = speed + 0.01;
        } else {
            
        }
    };

    while (window.isOpen())
    {
        window.handleEvents(onClose, onKeyPressed);

        window.clear();
        window.draw(shape);
        HandleWindowCollision(
            shape,
            window.getSize(),
            shapeDir,
            speed
        );
        shape.move(shapeDir * speed);
        window.display();
    }
}