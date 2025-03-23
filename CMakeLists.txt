cmake_minimum_required(VERSION 3.10)
project(SensorFusion)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(nlohmann_json REQUIRED)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Source files
set(SOURCES
    src/main.cpp
    src/timestamp.cpp
    src/kalmanfilter.cpp
    src/parser.cpp
    src/clustering.cpp
    src/fusion.cpp
)

if(WIN32)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()
# Add executable
add_executable(sensor_fusion ${SOURCES})

# Link libraries
target_link_libraries(sensor_fusion PRIVATE nlohmann_json::nlohmann_json)

# Add optimization flags for Release build
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")