#include <iostream>
#include "KKKLogger.h"
#include "GutenbergParser.h"

#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

static bool endsWith(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() && 0 == str.compare(str.size()-suffix.size(), suffix.size(), suffix);
}

static bool startsWith(const std::string& str, const std::string& prefix)
{
    return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
}


void makeBulk(const string& startDir) {
    std::string path = startDir;
    for (const auto & entry : fs::recursive_directory_iterator(path)) {
        string path=entry.path();
        if(endsWith(path, ".rdf")) {
            GutenbergParser gp(path);
            if (!gp.parseOK()) {
                KKKLogger::Error("Error processing file " + path);
                //break;
            }
            string json = gp.getBook().toJSon();
            if (json.length() > 0) {
                cout << gp.getBook().toElasticSearchIndexJSon() << endl;
                cout << json << endl;
            }
        }
    }
}


void FilesToJSon(int argc, char * argv[]) {
    for(auto i=1; i< argc; ++i) {
        string fileName = argv[i];
        KKKLogger::Fine("Processing: " + fileName);

        GutenbergParser gp(fileName);
        if(!gp.parseOK()) {
            KKKLogger::Error("Error processing file " + fileName);
            break;
        }
        cout << gp.getBook().toJSon() << endl;

    }
}

void parseFiles(int argc, char * argv[]) {
    for(auto i=2; i< argc; ++i) {
        string fileName = argv[i];
        KKKLogger::Fine("Processing: " + fileName);

        GutenbergParser gp(fileName);
        if(!gp.parseOK()) {
            KKKLogger::Error("Error processing file " + fileName);
            break;
        }
        const Book& book=gp.getBook();
        KKKLogger::Info(    "GutenbergID: " + to_string(gp.getBook().gutenbergID));
        KKKLogger::Info(    "Title      : " + gp.getBook().title);
        for(auto author : gp.getBook().authors) {
            KKKLogger::Info("authors    : " + author);
        }
        for(auto subject : gp.getBook().subjects) {
            KKKLogger::Info("subjects   : " + subject);
        }

        KKKLogger::Info("JSON: " + book.toJSon());
    }
}

int main(int argc, char * argv[]) {
    if (argc==3 && 0==strcmp(argv[1], "-bulk") ) {
        makeBulk(argv[2]);
    } else if (argc==3 && 0==strcmp(argv[1], "-info") ) {
        parseFiles(argc, argv);
    } else {
        FilesToJSon(argc, argv);
    }
    return 0;
}