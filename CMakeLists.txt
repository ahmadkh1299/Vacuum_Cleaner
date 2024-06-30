cmake_minimum_required(VERSION 3.22)
project(HW)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(HW main.cpp House.cpp Vacuum.cpp Algorithm.cpp)
