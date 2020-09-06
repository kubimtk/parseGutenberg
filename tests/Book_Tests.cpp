//
// Created by Wolfgang Kubisiak on 10.06.20.
//

#include <gtest/gtest.h>
#include "Book.h"
#include "TestFilePaths.h"
#include "GutenbergParser.h"

TEST(BookTests, canCreateElasticSearchIndexJSON) {
    GutenbergParser gp(Filename_132);
    ASSERT_TRUE(gp.parseOK());
    ASSERT_EQ(
            "{\"index\":{\"_id\":\"pg132\"}}",
            gp.getBook().toElasticSearchIndexJSon()
    );

}

TEST(BookTests, canCreateBookJSON) {
    GutenbergParser gp(Filename_132);
    ASSERT_TRUE(gp.parseOK());
    ASSERT_EQ(
            "{\"id\":132,\"title\":\"The Art of War\",\""
            "authors\":[\"Giles, Lionel\",\"Sunzi, active 6th century B.C.\"],"
            "\"subjects\":[\"War -- Early works to 1800\",\"Military art and science -- Early works to 1800\"]}",
            gp.getBook().toJSon()
            );
}


TEST(BookTests, canCreateBookJSONAndMaskCR_LF_doublequote_InTitle) {
    GutenbergParser gp(Filename_10113);
    ASSERT_TRUE(gp.parseOK());
    ASSERT_EQ(
            "{\"id\":10113,\"title\":\"De mannen van '80 aan het woord\\r\\nEen onderzoek vaar "
            "eenige beginselen van de \\\"Nieuwe-Gids\\\"-school.\","
            "\"authors\":[\"D'Oliveira, E. (Elias)\"],"
            "\"subjects\":[\"Dutch literature -- 19th century -- History and criticism\"]}",
            gp.getBook().toJSon()
    );
}

TEST(BookTests, canCreateBookJSONAndMaskCR_LF_doublequote_InAuthor) {
    GutenbergParser gp(Filename_56600);
    ASSERT_TRUE(gp.parseOK());
    ASSERT_EQ(
            "{\"id\":56600,\"title\":\"Lewis Arundel\\nOr, The Railroad Of Life\",\""
            "authors\":[\"\\\"Phiz\\\"\",\"Smedley, Frank E. (Frank Edward)\"],\"subjects\":[]}",
            gp.getBook().toJSon()
    );
}

TEST(BookTests, canCreateBookJSONAndMaskCR_LF_doublequote_InSubject) {
    GutenbergParser gp(Filename_14363);
    ASSERT_TRUE(gp.parseOK());
    ASSERT_EQ(
            "{\"id\":14363,\"title\":\"The Worst Journey in the World\\r\\nAntarctic 1910-1913\","
            "\"authors\":[\"Cherry-Garrard, Apsley\"],\""
            "subjects\":[\"British Antarctic (\\\"Terra Nova\\\") Expedition (1910-1913)\","
            "\"Antarctica -- Discovery and exploration -- British\"]}",
            gp.getBook().toJSon()
    );
}


TEST(BookTests, canCreateBookJSONWithSpecialTitleHandling) {
    GutenbergParser gp(Filename_6420);
    ASSERT_TRUE(gp.parseOK());
    ASSERT_EQ(
            "{\"id\":6420,\"title\":\"Copyright Renewals 1960U.S. Copyright Renewals, 1960\","
            "\"authors\":[\"Library of Congress. Copyright Office\"],"
            "\"subjects\":[\"Copyright -- United States -- Catalogs\"]}",
            gp.getBook().toJSon()
    );
}

TEST(BookTests, cannotCreateBookJSONFOrId0) {
    GutenbergParser gp(Filename_0);
    ASSERT_TRUE(gp.parseOK());
    ASSERT_EQ(
            "",
            gp.getBook().toJSon()
    );
}


