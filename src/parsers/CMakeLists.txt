add_library(parsers SHARED parser.cpp terminal_parser.cpp)
target_include_directories(parsers PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")