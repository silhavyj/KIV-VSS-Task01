# Minimum required version of cmake
cmake_minimum_required(VERSION 3.0)

# Specify the C++ standard used in the project
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the name of the project, version, description,
# home URL, and a list of all languages used in the project
project(
    kivvss01
    VERSION 0.0.1
    DESCRIPTION "KIV/VSS - task 01"
    LANGUAGES CXX C)

# Add src folder
add_subdirectory(src)