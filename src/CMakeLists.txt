# CMakeList.txt : CMake project for RaytracingInAWeekend, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (RaytracingInAWeekend "main.cc" "bitmap.cc" "vec3.cc" "color.h" "ray.h" "sphere.h" "sphere.cc" "world.h" "world.cc" "util.h" "camera.h" "material.h" "material.cc")

# TODO: Add tests and install targets if needed.
