# CMakeList.txt : CMake project for pathtracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (pathtracer  "objects.h" "main.cpp" "setup.h" "core.h")

# TODO: Add tests and install targets if needed.
