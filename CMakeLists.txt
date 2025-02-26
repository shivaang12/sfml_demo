cmake_minimum_required(VERSION 3.10)  # Minimum required CMake version
project(sfml_demo)  # Project name

# Find SFML package
find_package(SFML 3.0.0 COMPONENTS Graphics Window System REQUIRED)

add_executable(sfml_demo main.cpp)  # Create an executable from source file(s)
add_executable(sfml_demo_test main_test.cpp)  # Create an executable from source file(s)

# Link SFML to the target
target_link_libraries(sfml_demo PRIVATE SFML::Graphics SFML::Window SFML::System)
target_link_libraries(sfml_demo_test PRIVATE SFML::Graphics SFML::Window SFML::System)

target_include_directories(sfml_demo PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(sfml_demo_test PRIVATE ${CMAKE_SOURCE_DIR}/include)