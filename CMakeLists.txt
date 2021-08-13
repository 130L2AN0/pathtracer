# CMakeList.txt : CMake project for pathtracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(pathtracer)

# Add source to this project's executable.
add_executable (pathtracer  "src/dependencies.h" "src/objects.h" "src/main.cpp" "src/setup.h" "src/core.h" "src/objects.cpp" "src/core.cpp")

# TODO: Add tests and install targets if needed.
