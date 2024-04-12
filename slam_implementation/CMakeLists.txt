cmake_minimum_required(VERSION 3.5)
project(slam_implementation)

set(CMAKE_CXX_STANDARD 17)


# Find OpenCV package
find_package(OpenCV REQUIRED)


message(STATUS "OpenCV Library Paths: ${OpenCV_LIBRARY_DIRS}")

# Add headers
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(include/slam_implementation)

# Add source files
file(GLOB SOURCES "src/*.cpp")


message(STATUS "OpenCV Include Directories: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV Library Paths: ${OpenCV_LIBRARY_DIRS}")

# Create executable
add_executable(slam ${SOURCES})

# Link OpenCV libraries
target_link_libraries(slam ${OpenCV_LIBS} pthread)
