#ifndef SFML_DEMO_WORLD_PHYSICS_H
#define SFML_DEMO_WORLD_PHYSICS_H

#include <SFML/Graphics.hpp>
#include <limits>
#include <vector>
#include <iostream>

#include <body.hpp>
#include <transform.hpp>
#include <utils.hpp>

class WorldPhysics {

  public:
    bool intersectPolygons(const std::vector<sf::Vector2f> &tf_vertices_A,
                           const std::vector<sf::Vector2f> &tf_vertices_B) const {
        for (int i = 0; i < tf_vertices_A.size(); i++) {
            const auto &tf_vert_1 = tf_vertices_A[i];
            const auto &tf_vert_2 =
                tf_vertices_A[(i + 1) % tf_vertices_A.size()]; // To make it circular

            const auto &tf_vert_diff = tf_vert_2 - tf_vert_1;
            const auto &normal_of_1_n_2 = sf::Vector2f({-tf_vert_diff.y, tf_vert_diff.x});

            float minA = std::numeric_limits<float>::max();
            float minB = std::numeric_limits<float>::max();
            float maxA = -std::numeric_limits<float>::max();
            float maxB = -std::numeric_limits<float>::max();

            projectVertices(tf_vertices_A, normal_of_1_n_2, minA, maxA);
            projectVertices(tf_vertices_B, normal_of_1_n_2, minB, maxB);

            if (minA >= maxB || minB >= maxA) {
                // There is seperation
                return false;
            }
        }

        for (int i = 0; i < tf_vertices_B.size(); i++) {
            const auto &tf_vert_1 = tf_vertices_B[i];
            const auto &tf_vert_2 =
                tf_vertices_B[(i + 1) % tf_vertices_B.size()]; // To make it circular

            const auto &tf_vert_diff = tf_vert_2 - tf_vert_1;
            const auto &normal_of_1_n_2 = sf::Vector2f({-tf_vert_diff.y, tf_vert_diff.x});

            float minA, minB = std::numeric_limits<float>::max();
            float maxA, maxB = std::numeric_limits<float>::min();

            projectVertices(tf_vertices_A, normal_of_1_n_2, minA, maxA);
            projectVertices(tf_vertices_B, normal_of_1_n_2, minB, maxB);   

            if (minA >= maxB || minB >= maxA) {
                // There is seperation
                return false;
            }
        }

        return true;
    }

    void projectVertices(const std::vector<sf::Vector2f> &tf_vertices,
                         const sf::Vector2f &normal_axis, float &min, float &max) const {
        for (int i = 0; i < tf_vertices.size(); i++) {
            float proj = TMath::dotProduct(tf_vertices[i], normal_axis);

            if (proj < min) {
                min = proj;
            }
            if (proj > max) {
                max = proj;
            }
        }

        return;
    }

    void handleCollision(std::vector<std::shared_ptr<Body>> &body_list) {
        // Right now handling in brute force way

        for (int i = 0; i < body_list.size(); ++i) {

            auto circle_body_ptr_i = std::static_pointer_cast<CircleBody>(body_list[i]);

            for (int j = 0; j < body_list.size(); ++j) {

                if (i != j) {
                    auto circle_body_ptr_j = std::static_pointer_cast<CircleBody>(body_list[j]);
                    // Check for circle collision
                    const auto distance = calculateLengthOfVector(circle_body_ptr_i->getPosition() -
                                                                  circle_body_ptr_j->getPosition());
                    if (distance < circle_body_ptr_i->radius_ + circle_body_ptr_j->radius_) {
                        auto amount_of_collision =
                            (circle_body_ptr_i->radius_ + circle_body_ptr_j->radius_) - distance +
                            1.f;

                        const auto direction_of_collision = calculateUnitVector(
                            circle_body_ptr_i->getPosition() - circle_body_ptr_j->getPosition());

                        // Move the bodies according to direction and magnitude
                        circle_body_ptr_i->updatePosition(direction_of_collision *
                                                          (amount_of_collision / 2.0f) * 1.0f);
                        circle_body_ptr_j->updatePosition(direction_of_collision *
                                                          (amount_of_collision / 2.0f) * -1.0f);

                        circle_body_ptr_i->syncShapePositionWithPosition();
                        circle_body_ptr_j->syncShapePositionWithPosition();
                    }
                }
            }
        }
    }
};

#endif // SFML_DEMO_WORLD_PHYSICS_H