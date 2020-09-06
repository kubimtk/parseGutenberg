//
// Created by Wolfgang Kubisiak on 08.06.20.
//

#include <gtest/gtest.h>

#include "Markup.h"

#include "GutenbergParser.h"

#include "TestFilePaths.h"

using namespace testing;
using namespace std;

class GutenbergParser_Tests : public testing::Test {
public:
    unique_ptr<GutenbergParser> gp = nullptr;

    virtual void SetUp() override {
        gp.reset(new GutenbergParser(Filename_132));
    }
};

TEST_F(GutenbergParser_Tests, GutenberParserCanParseGutenbergId) {
    ASSERT_NE(nullptr, gp.get());
    ASSERT_TRUE(gp->parseOK());
    ASSERT_EQ(132, gp->getBook().gutenbergID);
}

TEST_F(GutenbergParser_Tests, GutenberParserCanParseTitle) {
    ASSERT_TRUE(gp->parseOK());
    ASSERT_EQ("The Art of War", gp->getBook().title);
}

TEST(GutenbergParser_Test2, UseEmptyTitleIfNoTitleAvailable) {
    auto gp = new GutenbergParser(Filename_192);
    ASSERT_TRUE(gp->parseOK());
    ASSERT_EQ("", gp->getBook().title);

}

TEST(GutenbergParser_Tests2, GutenberParserCanParseTitleWithSpecialTitleHandling) {
    auto gp = new GutenbergParser(Filename_6420);
    ASSERT_TRUE(gp->parseOK());
    ASSERT_EQ(
            "Copyright Renewals 1960U.S. Copyright Renewals, 1960",
            gp->getBook().title
    );
}

TEST_F(GutenbergParser_Tests, GutenberParserCanParseAuthors) {
    ASSERT_TRUE(gp->parseOK());
    auto result = gp->getBook().authors;
    vector<string> expectedAuthors{
            "Giles, Lionel",
            "Sunzi, active 6th century B.C."
    };
    ASSERT_EQ(expectedAuthors.size(), result.size());
    for (auto i = 0; i < expectedAuthors.size(); ++i) {
        ASSERT_EQ(expectedAuthors[i], result[i]);
    }
}

TEST(GutenbergParser_Tests2, GutenberParserCanParseAuthorsSpecialHandling) {
    auto gp = new GutenbergParser(Filename_999999);
    ASSERT_TRUE(gp->parseOK());
    auto result = gp->getBook().authors;
    vector<string> expectedAuthors{
            "Serao, Matilde"
    };
    ASSERT_EQ(expectedAuthors.size(), result.size());
    for (auto i = 0; i < expectedAuthors.size(); ++i) {
        ASSERT_EQ(expectedAuthors[i], result[i]);
    }
}

TEST_F(GutenbergParser_Tests, GutenberParserCanParseSubjects) {
    ASSERT_TRUE(gp->parseOK());
    auto result = gp->getBook().subjects;
    vector<string> expectedSubjects{
            "War -- Early works to 1800",
            "Military art and science -- Early works to 1800"
    };
    ASSERT_EQ(expectedSubjects.size(), result.size());
    for (auto i = 0; i < expectedSubjects.size(); ++i) {
        ASSERT_EQ(expectedSubjects[i], result[i]);
    }
}