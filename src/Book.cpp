//
// Created by Wolfgang Kubisiak on 09.06.20.
//

#include "Book.h"

using namespace std;

string Book::toJSon() const {
    string ret="";
    ret += "{";
    ret += "\"id\":" + to_string(gutenbergID) + ",";
    string nl = "\\";
    string cr = "\\";
    nl += "r";
    cr += "n";
    string tit=title;
    size_t pos;
    while( (pos=tit.find("\n"))!=string::npos) {
        tit.replace(pos, 1, cr);
    }
    while( (pos=tit.find("\r"))!=string::npos) {
        tit.replace(pos, 1, nl);
    }
/*
    //while( (pos=tit.find("\r"))!=string::npos) {
    //    tit.replace(pos, 1, "\n");
    //}
*/
    //tit.erase(std::remove(tit.begin(), tit.end(), '\n'), tit.end());
    ret += "\"title\":\"" + tit + "\",";
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
        ret += "\"" + elem + "\"";
    }
    ret += "]";
    if(endWithComma) ret +=",";
    return ret;
}
