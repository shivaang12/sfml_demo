#ifndef SFML_DEMO_SFML_RANDOM_H
#define SFML_DEMO_SFML_RANDOM_H

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For Time
#include <random>

int generateRandomIntBetweenLimits(const int &low, const int &high) {
    // Create a random device (for non-deterministic seeding)
    std::random_device rd;

    // Use Mersenne Twister engine
    std::mt19937 gen(rd());

    // Define a uniform real distribution between 0.0 and 1.0
    std::uniform_real_distribution<float> dist(low, high);

    return (int)dist(gen);
}

float generateRandomFloatBetweenLimits(const float &low, const float &high) {
    // Create a random device (for non-deterministic seeding)
    std::random_device rd;

    // Use Mersenne Twister engine
    std::mt19937 gen(rd());

    // Define a uniform real distribution between 0.0 and 1.0
    std::uniform_real_distribution<float> dist(low, high);

    return dist(gen);
}

#endif // SFML_DEMO_SFML_RANDOM_H