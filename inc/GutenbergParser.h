//
// Created by Wolfgang Kubisiak on 08.06.20.
//

#ifndef PARSEGUTENBERG_GUTENBERGPARSER_H
#define PARSEGUTENBERG_GUTENBERGPARSER_H


#include <string>
#include <vector>
#include "Markup.h"
#include "Book.h"

class GutenbergParser {
    std::string fileName;
    CMarkup xmlParser;
    bool _parseOK=false;
    Book book;

public:
    GutenbergParser(const std::string &fileName);
    bool parseOK() const { return _parseOK; }

    const Book& getBook() const { return book; }

private:
    bool parseITso();
    bool parseGutenbergID();
    bool parseTitle();
    bool parseAuthors();
    bool parseSubjects();
};


#endif //PARSEGUTENBERG_GUTENBERGPARSER_H
