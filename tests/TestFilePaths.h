//
// Created by Wolfgang Kubisiak on 09.06.20.
//

#ifndef PARSEGUTENBERG_TESTFILEPATHS_H
#define PARSEGUTENBERG_TESTFILEPATHS_H

#include <string>

const std::string GutenbergFilesPath = "/Users/kubi/NodeJsProgs/data/cache/epub/";
const std::string Filename_0 = GutenbergFilesPath + "0/pg0.rdf";       // unusable id
const std::string Filename_132 = GutenbergFilesPath + "132/pg132.rdf";       // book example
const std::string Filename_192 = GutenbergFilesPath + "192/pg192.rdf";       // no title
const std::string Filename_13182 = GutenbergFilesPath + "13182/pg13182.rdf"; // many authors
const std::string Filename_10113 = GutenbergFilesPath + "10113/pg10113.rdf"; //LF CR \" in title
const std::string Filename_56600 = GutenbergFilesPath + "56600/pg56600.rdf"; //LF CR \" in authors
const std::string Filename_14363 = GutenbergFilesPath + "14363/pg14363.rdf"; //LF CR \" in subjects
const std::string Filename_6420 = GutenbergFilesPath + "6420/pg6420.rdf"; //title handling
const std::string Filename_999999 = GutenbergFilesPath + "999999/pg999999.rdf"; //author handling

const std::string Filename_test = "../..//tests/test.xml"; // relative to ./cmake-build-debug/tests/testITso


#endif //PARSEGUTENBERG_TESTFILEPATHS_H
