cmake_minimum_required(VERSION 3.29.6)
project(space-shootout CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} src/main.cpp)

set(BUILD_EXAMPLES
    OFF
    CACHE BOOL "" FORCE)
set(BUILD_GAMES
    OFF
    CACHE BOOL "" FORCE)
set(JSON_BuildTests
    OFF
    CACHE INTERNAL "")

add_subdirectory(external/raylib)
add_subdirectory(external/enet)
add_subdirectory(external/json)
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC external/raylib/include
  PUBLIC external/enet/include
  PUBLIC external/json/include)
target_link_directories(${PROJECT_NAME} PRIVATE external/raylib/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib enet nlohmann_json)
