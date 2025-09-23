cmake_minimum_required(VERSION 3.20.0)

project(polygraphia VERSION 0.01)

add_subdirectory(ciphers)
add_subdirectory(mediator)
add_subdirectory(parsers)

add_executable(polygraphia main.cpp ${SRC_FILES})
target_link_libraries(polygraphia PUBLIC ciphers mediator parsers)