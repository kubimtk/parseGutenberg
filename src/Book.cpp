//
// Created by Wolfgang Kubisiak on 09.06.20.
//
#include <iostream>
#include "Book.h"

using namespace std;

string Book::toJSon() const {
    if(gutenbergID==0) return "";
    string ret="";
    ret += "{";
    ret += "\"id\":" + to_string(gutenbergID) + ",";

    ret += "\"title\":\"" + escapeString(title) + "\",";
    ret += vector2JSonString("authors", authors);
    ret += vector2JSonString("subjects", subjects, false);
    ret += "}";
    return ret;
}

string Book::vector2JSonString(const string& vectorName, const vector<string>& v, bool endWithComma) const {
    string ret="";
    ret += "\"" + vectorName + "\":[";

    bool nextLine=false;
    for(auto const& elem : v) {
        if(nextLine)
            ret += ",";
        else
            nextLine=true;
        ret += "\"" + escapeString(elem) + "\"";
    }
    ret += "]";
    if(endWithComma) ret +=",";
    return ret;
}

std::string Book::toElasticSearchIndexJSon() const {
    return "{\"index\":{\"_id\":\"pg" + to_string(gutenbergID) + "\"}}";
}

std::string Book::escapeString(const string &s) const {
    string ret="";
    for(auto ch : s) {
        if(ch == '\n') {
            ret.push_back('\\');
            ret.push_back('n');
        } else if(ch == '\r') {
            ret.push_back('\\');
            ret.push_back('r');
        } else if(ch == '"') {
            ret.push_back('\\');
            ret.push_back('"');
        } else {
            ret.push_back(ch);
        }
    }
    return ret;
}
