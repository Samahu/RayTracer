project (SimpleRT)

add_library(${PROJECT_NAME} src/SimpleRT.cpp)
add_library(sub::SimpleRT ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    sub::Math
)