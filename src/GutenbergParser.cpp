//
// Created by Wolfgang Kubisiak on 08.06.20.
//

#include "GutenbergParser.h"
#include <iostream>
using namespace std;
bool logITso=false;

GutenbergParser::GutenbergParser(const std::string &fileName) {
    this->fileName=fileName;
    xmlParser.Load(fileName);
    _parseOK = parseITso();
}

bool GutenbergParser::parseITso() {

    bool ret=true;
    ret &= parseGutenbergID();
    if(book.gutenbergID>0) {
        ret &= parseTitle();
        ret &= parseAuthors();
        ret &= parseSubjects();
    }
    return ret;
}

bool GutenbergParser::parseGutenbergID() {
    xmlParser.ResetPos();
    if(!xmlParser.FindElem("rdf:RDF")) return false;
    xmlParser.IntoElem();
    if(!xmlParser.FindElem("pgterms:ebook")) return false;
    string idString=xmlParser.GetAttrib("rdf:about");
    if(!idString.rfind("ebooks/"==0)) return false;
    book.gutenbergID = std::stoi(idString.substr(7));
    return true;
}

bool GutenbergParser::parseTitle() {
    xmlParser.ResetPos();
    if(!xmlParser.FindElem("rdf:RDF")) return false;
    xmlParser.IntoElem();
    if(!xmlParser.FindElem("pgterms:ebook")) return false;
    xmlParser.IntoElem();
    string title="";
    while(xmlParser.FindElem("dcterms:title")) {
        title += xmlParser.GetData();
    }
    book.title = title;
    return true;
}

bool GutenbergParser::parseAuthors() {
    int level=0;
    book.authors.clear();
    xmlParser.ResetPos();
    if(!xmlParser.FindElem("rdf:RDF")) return false;
    xmlParser.IntoElem();
    while(level>=0) {
        while( xmlParser.FindElem() ) {
            auto tagName=xmlParser.GetTagName();
            if(logITso) cout << "Author: tagName=" << tagName << endl;
            if(tagName=="pgterms:agent") {
                if(logITso) cout << "Found agent on 1st level " << endl;
                if(xmlParser.FindChildElem("pgterms:name")) {
                    string author = xmlParser.GetChildData();
                    book.authors.push_back(author);
                    if(logITso) cout << "Found author on 1st level " << author << endl;
                }
            } else if (level<2){
                xmlParser.IntoElem();
                level += 1;
            }
        }
        xmlParser.OutOfElem();
        level -= 1;

    }
    return true;
}

bool GutenbergParser::parseSubjects() {
    book.subjects.clear();
    xmlParser.ResetPos();
    if(!xmlParser.FindElem("rdf:RDF")) return false;
    xmlParser.IntoElem();
    if(!(xmlParser.FindElem("pgterms:ebook"))) return false;
    xmlParser.IntoElem();
    while( xmlParser.FindElem("dcterms:subject") ) {
        if(logITso) cout << "Found dcterms:subject" << endl;
        xmlParser.IntoElem();
        if(xmlParser.FindElem("rdf:Description")) {
            if(logITso) cout << "Found rdf:Description" << endl;
            xmlParser.IntoElem();
            if (xmlParser.FindElem("dcam:memberOf")) {
                if(logITso) cout << "Found dcam:memberOf" << endl;
                //xmlParser.IntoElem();
                auto memberOfValue = xmlParser.GetAttrib("rdf:resource");
                if(logITso) cout << "memberOfValue=" << memberOfValue << endl;
                if( (memberOfValue.length()>4) &&
                    (0 == memberOfValue.compare(memberOfValue.length()-4, 4, "LCSH")) ) {
                    if(logITso) cout << "match found!" << endl;
                    xmlParser.ResetMainPos();
                    if (xmlParser.FindElem("rdf:value")) {
                        auto subject=xmlParser.GetData();
                        book.subjects.push_back(subject);
                        if(logITso) cout << "Found subject " << subject << endl;
                    }
                }
            }
            xmlParser.OutOfElem();
        }
        xmlParser.OutOfElem();
    }
    return true;
}


