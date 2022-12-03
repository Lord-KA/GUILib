cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20" CACHE STRING "Comment" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -D NDEBUG" CACHE STRING "Comment" FORCE)
set(CMAKE_CXX_FLAGS_SANITIZER "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wformat=2 -fsanitize=address,undefined -g" CACHE STRING "Comment" FORCE)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

include(FetchContent)

FetchContent_Declare(
  utils
  GIT_REPOSITORY https://github.com/Lord-KA/CPPUtils.git
  GIT_TAG        release-0.1
)

FetchContent_GetProperties(utils)
if(NOT utils_POPULATED)
  FetchContent_Populate(utils)
  include_directories(${utils_SOURCE_DIR})
endif()

FetchContent_Declare(
  commonTools
  GIT_REPOSITORY https://github.com/mishaglik/Elpidifor-s-legacy.git
  GIT_TAG        v1.1.0
)

FetchContent_GetProperties(commonTools)
if(NOT commonTools_POPULATED)
  FetchContent_Populate(commonTools)
  include_directories(./build/_deps/commontools-src)
endif()

include_directories(./)
include_directories(./applications)
include_directories(./utils)
include_directories(./objects)

# Define sources and executable
add_executable(window ./applications/window-app.cpp ./Events.cpp ./ToolSetup.cpp ./ToolPalette.cpp)

find_package(SFML 2.5 COMPONENTS network audio graphics window system REQUIRED)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(window sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
endif()

# find_package(SDL2 REQUIRED)
# include_directories(${SDL2_INCLUDE_DIRS})
# target_link_libraries(raytracer ${SDL2_LIBRARIES})
