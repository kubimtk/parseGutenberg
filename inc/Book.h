//
// Created by Wolfgang Kubisiak on 09.06.20.
//

#ifndef PARSEGUTENBERG_BOOK_H
#define PARSEGUTENBERG_BOOK_H

#include <string>
#include <vector>

class Book {
    std::string escapeString(const std::string &s) const;

    std::string
    vector2JSonString(const std::string &vectorName, const std::vector<std::string> &v, bool endWithComma = true) const;

public:
    int gutenbergID = -1;
    std::string title = "n/a";
    std::vector<std::string> authors = {};
    std::vector<std::string> subjects = {};

    std::string toJSon() const;

    std::string toElasticSearchIndexJSon() const;

};


#endif //PARSEGUTENBERG_BOOK_H
