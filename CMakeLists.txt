cmake_minimum_required (VERSION 3.17)
project ("PONG_Semestralka")

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_CXX_STANDARD 14)
set(SFML_DIR C:/SFML/lib/cmake/SFML)

find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

add_executable(PONG_Semestralka main.cpp Ball.cpp Ball.h)

target_link_libraries(PONG_Semestralka sfml-system sfml-window sfml-graphics sfml-audio)

