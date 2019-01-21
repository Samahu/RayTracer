project (SceneObjects)


add_library(${PROJECT_NAME} STATIC src/SceneObjects.cpp)
add_library(sub::SceneObjects ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    sub::Math
)