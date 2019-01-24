cmake_minimum_required(VERSION 3.0.0)

project(RayTracerUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets CONFIG REQUIRED)

set(RayTracerUI_SRCS
	"MainWindow.ui"
	"MainWindow.cpp"
        "RenderArea.cpp"
	"main.cpp"
)

add_executable(${PROJECT_NAME}  ${RayTracerUI_SRCS})

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    sub::Math
    sub::SceneObjects
    sub::SimpleRT
)
