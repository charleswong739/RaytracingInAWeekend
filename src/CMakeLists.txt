# CMakeList.txt : CMake project for RaytracingInAWeekend, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (RaytracingInAWeekend "main.cc"  "bitmap.cc" "vec3.h" "color.h" "ray.h" "sphere.h")

# TODO: Add tests and install targets if needed.
