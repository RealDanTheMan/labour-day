cmake_minimum_required(VERSION 3.14)

project(labour-day CXX)

# Binary output paths
set(CMAKE_BINARY_DIR ./bin/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Find Dependencies
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

# Project sources
set(PROJECT_SOURCE_DIR ./src/)
include_directories(${PROJECT_SOURCE_DIR})

# Main project (user) source files
set(SOURCES 
${PROJECT_SOURCE_DIR}/main.cpp
${PROJECT_SOURCE_DIR}/app.cpp
${PROJECT_SOURCE_DIR}/engine/glfwinterface.cpp
${PROJECT_SOURCE_DIR}/engine/glewinterface.cpp
${PROJECT_SOURCE_DIR}/engine/enginecore.cpp
${PROJECT_SOURCE_DIR}/engine/shadersource.cpp
${PROJECT_SOURCE_DIR}/engine/shaderprog.cpp
${PROJECT_SOURCE_DIR}/engine/window.cpp )

add_executable(labour-day ${SOURCES})


# Link GLFW and OpenGL
target_link_libraries(labour-day glfw)
target_include_directories(labour-day PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(labour-day ${OPENGL_gl_LIBRARY})