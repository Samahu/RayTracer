project (Math)


add_library(${PROJECT_NAME} src/Vector3.cpp)
add_library(sub::Math ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)