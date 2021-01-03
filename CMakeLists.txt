cmake_minimum_required(VERSION 3.6)
project(parseGutenberg)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(tests)
include_directories(inc)
add_executable(parseGutenberg src/main.cpp src/GutenbergParser.cpp  src/Book.cpp src/Markup.cpp)

target_link_libraries(parseGutenberg iconv)
