cmake_minimum_required(VERSION 2.8.8)

cmake_policy(SET CMP0048 NEW)

project(parseGutenberg_Test)

add_subdirectory(googletest)

include_directories(googletest/googletest/include ../inc)

add_executable(testITso CMarkup_Tests.cpp ../src/GutenbergParser.cpp ../src/Book.cpp ../src/Markup.cpp GutenbergParser_Tests.cpp Book_Tests.cpp )

#target_compile_options( -target arm64-apple-macos11)
#target_compile_features( -target arm64-apple-macos11)
target_link_libraries(testITso gtest gtest_main iconv)

