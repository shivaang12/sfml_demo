cmake_minimum_required(VERSION 3.10)  # Minimum required CMake version
project(sfml_demo)  # Project name

# Find SFML package
find_package(SFML 3.0.0 COMPONENTS Graphics Window System REQUIRED)

add_executable(sfml_demo main.cpp)  # Create an executable from source file(s)

# Link SFML to the target
target_link_libraries(sfml_demo PRIVATE SFML::Graphics SFML::Window SFML::System)

message(PROJECT_SOURCE_DIR="${SFML_INCLUDE_DIR}")

target_include_directories(sfml_demo PRIVATE ${CMAKE_SOURCE_DIR}/include)