cmake_minimum_required(VERSION 3.16)
project(parseGutenberg)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(tests)
include_directories(inc)
add_executable(parseGutenberg src/main.cpp src/GutenbergParser.cpp  src/Book.cpp src/Markup.cpp)

target_link_libraries(parseGutenberg iconv)
