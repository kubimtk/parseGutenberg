project(parseGutenberg_Test)

add_subdirectory(googletest)

include_directories(googletest/googletest/include ../inc)

add_executable(testITso CMarkup_Tests.cpp ../src/GutenbergParser.cpp ../src/Markup.cpp GutenbergParser_Tests.cpp)

target_link_libraries(testITso gtest gtest_main iconv)

