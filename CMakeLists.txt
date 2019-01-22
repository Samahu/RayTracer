cmake_minimum_required (VERSION 3.5)

project(RayTracer)

set (CMAKE_CXX_STANDARD 14)

# Add sub directories
add_subdirectory(Math)
add_subdirectory(SceneObjects)
add_subdirectory(SimpleRT)
add_subdirectory(RayTracer)
