cmake_minimum_required(VERSION 3.16)


project(3dRenderer)

find_package(OpenGL REQUIRED)

if(OpenGL_FOUND)
    message(STATUS "Found OpenGL version: ${OpenGL_VERSION}")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(INCLUDES_DIRECTORY ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fPIC  -g3")

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/glad.c
    src/Window.cpp
    src/Vector.cpp
    src/Shader.cpp
    src/Triangle.cpp
    src/Camera.cpp
)
    
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${INCLUDES_DIRECTORY}
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ${OPENGL_LIBRARY}
    glfw
)