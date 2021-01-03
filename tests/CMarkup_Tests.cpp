#include <gtest/gtest.h>
#include "Markup.h"
#include "KKKLogger.h"
#include "TestFilePaths.h"
#include <filesystem>
using namespace testing;
using namespace std;


class XMLParserTests : public testing::Test {
public:
    CMarkup xmlParser;
};

class ParseGutenbergTests : public XMLParserTests {
public:
    virtual void SetUp() override {
        xmlParser.Load(Filename_132);
    }
};

TEST_F(XMLParserTests, TestCMarkup) {
    //cout << "CWD=" << std::__fs::filesystem::current_path();
    ASSERT_TRUE(xmlParser.Load(Filename_test));
    xmlParser.FindElem();
    xmlParser.IntoElem();
    ASSERT_TRUE(xmlParser.FindElem("ITEM"));
    xmlParser.IntoElem();
    ASSERT_TRUE(xmlParser.FindElem("SN"));
    ASSERT_EQ("132487A-J", xmlParser.GetData());
}

TEST_F(ParseGutenbergTests, TestRDF) {
    ASSERT_TRUE(xmlParser.FindElem("rdf:RDF"));
    xmlParser.IntoElem();
    ASSERT_TRUE(xmlParser.FindElem("pgterms:ebook"));
}

TEST_F(ParseGutenbergTests, ParseGutenbergID) {
    ASSERT_TRUE(xmlParser.FindElem("rdf:RDF"));
    xmlParser.IntoElem();
    ASSERT_TRUE(xmlParser.FindElem("pgterms:ebook"));
    string idString=xmlParser.GetAttrib("rdf:about");
    ASSERT_EQ("ebooks/132", idString);
    auto intString=idString.substr(7);
    ASSERT_EQ("132", intString);
}

TEST_F(ParseGutenbergTests, ParseTitle) {
    ASSERT_TRUE(xmlParser.FindElem("rdf:RDF"));
    xmlParser.IntoElem();
    ASSERT_TRUE(xmlParser.FindElem("pgterms:ebook"));
    xmlParser.IntoElem();
    ASSERT_TRUE(xmlParser.FindElem("dcterms:title"));
    ASSERT_EQ("The Art of War", xmlParser.GetData());
}

TEST_F(ParseGutenbergTests, ParseAuthors) {
    xmlParser.ResetPos();
    ASSERT_TRUE(xmlParser.FindElem("rdf:RDF"));
    xmlParser.IntoElem();
    int i=0;
    while( xmlParser.FindElem() ) {
        if(i++>99) {
            KKKLogger::Error("ParseAuthors: Breaking out of long loop!!");
            break;
        }
        auto tagName=xmlParser.GetTagName();
        KKKLogger::Fine("tagName=" + tagName);
        if(tagName=="pgterms:ebook") {
            xmlParser.IntoElem();
        } else if(tagName.rfind("marcrel:")==0 || tagName=="dcterms:creator") {
            xmlParser.IntoElem();
            if(xmlParser.FindChildElem("pgterms:name")) {
                KKKLogger::Fine("Found author " + xmlParser.GetChildData());
            }
            xmlParser.OutOfElem();
        }
    }
}

TEST_F(ParseGutenbergTests, ParseSubjects) {
    xmlParser.ResetPos();
    ASSERT_TRUE(xmlParser.FindElem("rdf:RDF"));
    xmlParser.IntoElem();
    ASSERT_TRUE(xmlParser.FindElem("pgterms:ebook"));
    xmlParser.IntoElem();
    int i=0;
    while( xmlParser.FindElem("dcterms:subject") ) {
        if(i++>99) {
            KKKLogger::Error("ParseSubjects: Breaking out of long loop!!");
            break;
        }
        KKKLogger::Fine("Found dcterms:subject");
        xmlParser.IntoElem();
        if(xmlParser.FindElem("rdf:Description")) {
            KKKLogger::Fine("Found rdf:Description");
            xmlParser.IntoElem();
            if (xmlParser.FindElem("dcam:memberOf")) {
                KKKLogger::Fine("Found dcam:memberOf");
                auto memberOfValue = xmlParser.GetAttrib("rdf:resource");
                KKKLogger::Fine("memberOfValue=" + memberOfValue);
                if( (memberOfValue.length()>4) &&
                        (0 == memberOfValue.compare(memberOfValue.length()-4, 4, "LCSH")) ) {
                    KKKLogger::Fine("match found!");
                    xmlParser.ResetMainPos();
                    if (xmlParser.FindElem("rdf:value")) {
                        auto subject=xmlParser.GetData();
                        KKKLogger::Fine("Found subject " + subject);
                    }
                }
            }
            xmlParser.OutOfElem();
        }
        xmlParser.OutOfElem();
    }
}