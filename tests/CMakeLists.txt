project(parseGutenberg_Test)

add_subdirectory(googletest)

include_directories(googletest/googletest/include ../inc)

add_executable(testITso CMarkup_Tests.cpp ../src/GutenbergParser.cpp ../src/Book.cpp ../src/Markup.cpp GutenbergParser_Tests.cpp Book_Tests.cpp)

target_link_libraries(testITso gtest gtest_main iconv)

