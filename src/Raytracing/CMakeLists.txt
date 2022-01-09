add_library(Raytracing STATIC
	bitmap.cc
	material.cc
	sphere.cc
	vec3.cc
	world.cc
)

# Request c++ 17
target_compile_features(Raytracing PUBLIC cxx_std_17)