//
// Created by Wolfgang Kubisiak on 08.06.20.
//

#include "GutenbergParser.h"
#include <iostream>
using namespace std;
bool log=false;

GutenbergParser::GutenbergParser(const std::string &fileName) {
    this->fileName=fileName;
    xmlParser.Load(fileName);
    _parseOK = parseITso();
    //cout << "Hier GutenbergParser!" << endl;
}

bool GutenbergParser::parseITso() {

    bool ret=true;
    ret &= parseGutenbergID();
    ret &= parseTitle();
    ret &= parseAuthors();
    ret &= parseSubjects();
    return true;
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
    if(!xmlParser.FindElem("dcterms:title")) return false;
    book.title = xmlParser.GetData();
    return true;
}

bool GutenbergParser::parseAuthors() {
    book.authors.clear();
    xmlParser.ResetPos();
    if(!xmlParser.FindElem("rdf:RDF")) return false;
    xmlParser.IntoElem();
    while( xmlParser.FindElem() ) {
        auto tagName=xmlParser.GetTagName();
        if(log) cout << "tagName=" << tagName << endl;
        if(tagName=="pgterms:ebook") {
            xmlParser.IntoElem();
        } else if(tagName.rfind("marcrel:")==0 || tagName=="dcterms:creator") {
            xmlParser.IntoElem();
            if(xmlParser.FindChildElem("pgterms:name")) {
                string author = xmlParser.GetChildData();
                book.authors.push_back(author);
                if(log) cout << "Found author " << author << endl;
            }
            xmlParser.OutOfElem();
        }
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
        if(log) cout << "Found dcterms:subject" << endl;
        xmlParser.IntoElem();
        if(xmlParser.FindElem("rdf:Description")) {
            if(log) cout << "Found rdf:Description" << endl;
            xmlParser.IntoElem();
            if (xmlParser.FindElem("dcam:memberOf")) {
                if(log) cout << "Found dcam:memberOf" << endl;
                //xmlParser.IntoElem();
                auto memberOfValue = xmlParser.GetAttrib("rdf:resource");
                if(log) cout << "memberOfValue=" << memberOfValue << endl;
                if( (memberOfValue.length()>4) &&
                    (0 == memberOfValue.compare(memberOfValue.length()-4, 4, "LCSH")) ) {
                    if(log) cout << "match found!" << endl;
                    xmlParser.ResetMainPos();
                    if (xmlParser.FindElem("rdf:value")) {
                        auto subject=xmlParser.GetData();
                        book.subjects.push_back(subject);
                        if(log) cout << "Found subject " << subject << endl;
                    }
                }
            }
            xmlParser.OutOfElem();
        }
        xmlParser.OutOfElem();
    }
    return false;
}


