project(RayTracerCmd)

# Create the executable
add_executable(${PROJECT_NAME} RayTracer.cpp)

target_link_libraries(${PROJECT_NAME}
    sub::Math
    sub::SimpleRT
	sub::MultiThreadedRT
	sub::OpenMP_RT
    sub::SceneObjects
)
