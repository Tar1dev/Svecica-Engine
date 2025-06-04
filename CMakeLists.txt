cmake_minimum_required(VERSION 3.10)

project(GameEngine)

set(CMAKE_CXX_STANDARD 17)

#GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)  # Désactiver Wayland
add_subdirectory(thirdparty/glfw)

# GLAD
add_library(glad STATIC thirdparty/glad/src/glad.c)
target_include_directories(glad PUBLIC thirdparty/glad/include)

#STB
add_library(stb STATIC thirdparty/stb/src/stb_image.cpp)
target_include_directories(stb PUBLIC thirdparty/stb/include)


# Définir les fichiers sources
file(GLOB SOURCES "platform/src/**/*.cpp" "platform/src/*.cpp")

set(RESOURCES_DIR "${CMAKE_SOURCE_DIR}/resources")
add_compile_definitions(RESOURCES="${RESOURCES_DIR}")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/glad/include platform/include thirdparty/stb/include)
target_link_libraries(${PROJECT_NAME} glad glfw GL dl stb)