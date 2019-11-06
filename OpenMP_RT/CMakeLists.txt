cmake_minimum_required(VERSION 3.9)

project (OpenMP_RT)

add_library(${PROJECT_NAME} STATIC src/OpenMP_RT.cpp)
add_library(sub::OpenMP_RT ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

find_package(OpenMP REQUIRED)
if (OpenMP_FOUND)
	message( "OpenMP found")
	target_link_libraries(${PROJECT_NAME} OpenMP::OpenMP_CXX)
else()
	message(FATAL_ERROR "OpenMP not fount")
endif()

target_link_libraries(${PROJECT_NAME}
	sub::Math
	sub::SceneObjects
)