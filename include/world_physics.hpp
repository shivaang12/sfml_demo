#ifndef SFML_DEMO_WORLD_PHYSICS_H
#define SFML_DEMO_WORLD_PHYSICS_H

#include <SFML/Graphics.hpp>
#include <vector>

#include <body.hpp>
#include <utils.hpp>

class WorldPhysics {

  public:
    void handleCollision(std::vector<Body> &body_list) {
        // Right now handling in brute force way

        for (int i = 0; i < body_list.size(); ++i) {

            for (int j = 0; j < body_list.size(); ++j) {
                if (i != j) {
                    // Check for circle collision
                    const auto distance = calculateLengthOfVector(body_list[i].getPosition() -
                                                                  body_list[j].getPosition());
                    if (distance < body_list[i].radius_ + body_list[j].radius_) {
                        auto amount_of_collision =
                            (body_list[i].radius_ + body_list[j].radius_) - distance + 1.f;

                        const auto direction_of_collision =
                            calculateUnitVector(body_list[i].getPosition() - body_list[j].getPosition());

                        // Move the bodies according to direction and magnitude
                        body_list[i].movePosition(direction_of_collision *
                                                  (amount_of_collision / 2.0f) * 1.0f);
                        body_list[j].movePosition(direction_of_collision *
                                                  (amount_of_collision / 2.0f) * -1.0f);
                    }
                }
            }
        }
    }
};

#endif // SFML_DEMO_WORLD_PHYSICS_H