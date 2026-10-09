cmake_minimum_required(VERSION 3.22)
project(2DEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# finds vcpkg packages/targets
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

# engine is built once as a static library and shared by every experiment
add_library(engine STATIC
    engine/Engine2D.h engine/Engine2D.cpp
    engine/Colour.h engine/Colour.cpp
    engine/Shader.h engine/Shader.cpp
    engine/Rect.h engine/Rect.cpp
    engine/Texture.h engine/Texture.cpp
    engine/stb_image.h engine/stb_image.cpp
)
target_include_directories(engine PUBLIC engine)

# links the imported targets from vcpkg (PUBLIC so experiments get them too)
target_link_libraries(engine PUBLIC
    glfw
    glad::glad
    glm::glm
)

# each .cpp in src/ becomes its own executable named after the file
# (e.g. src/mandelbrot.cpp -> mandelbrot.exe)
file(GLOB EXPERIMENTS CONFIGURE_DEPENDS src/*.cpp)
foreach(experiment_src ${EXPERIMENTS})
    get_filename_component(experiment_name ${experiment_src} NAME_WE)
    add_executable(${experiment_name} ${experiment_src})
    target_link_libraries(${experiment_name} PRIVATE engine)
endforeach()
