# SFML version >= 2.5
cmake_minimum_required(VERSION 3.1)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

project(app)

include_directories(./)
include_directories(./applications)
include_directories(./utils)

# Define sources and executable
add_executable(vectors ./applications/vectors-main.cpp)

find_package(SFML 2.5 COMPONENTS network audio graphics window system REQUIRED)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(vectors sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(sphere ./applications/sphere-main.cpp)
target_link_libraries(sphere ${SDL2_LIBRARIES})
