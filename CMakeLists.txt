cmake_minimum_required(VERSION 3.10)  # Minimum required CMake version
project(sfml_demo)  # Project name

# Find SFML package
find_package(SFML 3.0.0 COMPONENTS Graphics Window System REQUIRED)

FILE(GLOB_RECURSE TARGET_INC "include/*.hpp")
message("${TARGET_INC}")

IF(CMAKE_GENERATOR MATCHES "Xcode")
add_executable(sfml_demo main.cpp ${TARGET_INC})
ELSE()
add_executable(sfml_demo main.cpp)
ENDIF()

IF(CMAKE_GENERATOR MATCHES "Xcode")
add_executable(sfml_demo_test main_test.cpp ${TARGET_INC})
ELSE()
add_executable(sfml_demo_test main_test.cpp)
ENDIF()

IF(CMAKE_GENERATOR MATCHES "Xcode")
add_executable(sfml_demo_player_test main_player_test.cpp ${TARGET_INC})
ELSE()
add_executable(sfml_demo_player_test main_player_test.cpp)  # Create an executable from source file(s)
ENDIF()

# Link SFML to the target
target_link_libraries(sfml_demo PRIVATE SFML::Graphics SFML::Window SFML::System)
target_link_libraries(sfml_demo_test PRIVATE SFML::Graphics SFML::Window SFML::System)
target_link_libraries(sfml_demo_player_test PRIVATE SFML::Graphics SFML::Window SFML::System)

target_include_directories(sfml_demo PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(sfml_demo_test PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(sfml_demo_player_test PUBLIC ${PROJECT_SOURCE_DIR}/include)

include_directories(${PROJECT_SOURCE_DIR}/include)