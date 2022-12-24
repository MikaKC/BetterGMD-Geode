cmake_minimum_required(VERSION 3.3.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GEODE_LINK_NIGHTLY on)

project(BetterGMD VERSION 1.0.0)

# Use GLOB_RECURSE instead of GLOB
# to recursively add all source files 
# under src/ 
file(GLOB SOURCES
	src/*.cpp
)

# Set up the mod binary
add_library(${PROJECT_NAME} SHARED ${SOURCES})

add_subdirectory(D:/Apps/Dev/GeodeSDK D:/Apps/Dev/GeodeSDK/build)

target_link_libraries(${PROJECT_NAME} geode-sdk)
create_geode_file(${PROJECT_NAME})
