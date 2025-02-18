#ifndef SFML_DEMO_WORLD_PHYSICS_H
#define SFML_DEMO_WORLD_PHYSICS_H

#include <SFML/Graphics.hpp>
#include <vector>

#include <body.hpp>
#include <utils.hpp>

class WorldPhysics {

  public:
    void handleCollision(std::vector<std::shared_ptr<Body>> &body_list) {
        // Right now handling in brute force way

        for (int i = 0; i < body_list.size(); ++i) {

            auto circle_body_ptr_i = std::static_pointer_cast<CircleBody>(body_list[i]);

            for (int j = 0; j < body_list.size(); ++j) {

                if (i != j) {
                    auto circle_body_ptr_j = std::static_pointer_cast<CircleBody>(body_list[j]);
                    // Check for circle collision
                    const auto distance = calculateLengthOfVector(circle_body_ptr_i->getPosition() - circle_body_ptr_j->getPosition());
                    if (distance < circle_body_ptr_i->radius_ + circle_body_ptr_j->radius_) {
                        auto amount_of_collision =
                            (circle_body_ptr_i->radius_ + circle_body_ptr_j->radius_) - distance + 1.f;

                        const auto direction_of_collision =
                            calculateUnitVector(circle_body_ptr_i->getPosition() - circle_body_ptr_j->getPosition());

                        // Move the bodies according to direction and magnitude
                        circle_body_ptr_i->updatePosition(direction_of_collision *
                                                  (amount_of_collision / 2.0f) * 1.0f);
                        circle_body_ptr_j->updatePosition(direction_of_collision *
                                                  (amount_of_collision / 2.0f) * -1.0f);
                    }
                }
            }
        }
    }
};

#endif // SFML_DEMO_WORLD_PHYSICS_H