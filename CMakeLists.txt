cmake_minimum_required(VERSION 3.22)
project(2DEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# finds vcpkg packages/targets
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(2DEngine "engine/Engine2D.cpp" "engine/Colour.h" "engine/Colour.cpp" "src/main.cpp" "engine/Engine2D.h" "engine/Shader.h" "engine/Shader.cpp"
    engine/Rect.h
    engine/Rect.cpp)

# links the imported targets from vcpkg
target_link_libraries(2DEngine PRIVATE
    glfw
    glad::glad
    glm::glm
)
