# CMakeList.txt : CMake project for RaytracingInAWeekend, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.9)

add_subdirectory(Raytracing)


# Add source to this project's executable.
add_executable (RaytracingInAWeekend main.cu)

# Link library
target_link_libraries(RaytracingInAWeekend PUBLIC Raytracing)

# Specify includes
target_include_directories(Raytracing PUBLIC "#{CMAKE_CURRENT_SOURCE_DIR}/Raytracing")

# Request c++ 17
target_compile_features(RaytracingInAWeekend PUBLIC cxx_std_17)
