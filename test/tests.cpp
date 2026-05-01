// Copyright 2021 GHA Test Team
#include "textgen.h"
#include <deque>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <gtest/gtest.h>

TEST(PrefixTable, EmptyInputGivesEmptyTable) {
    TextGenerator generator;
    std::istringstream in("");
    generator.createTableOfPrefixesAndSuffixes(in);
    EXPECT_TRUE(generator.getStateTab().empty());
}

TEST(PrefixTable, LessThanNPREFWordsGivesEmptyTable) {
    TextGenerator generator;
    std::istringstream in("word");
    generator.createTableOfPrefixesAndSuffixes(in);
    EXPECT_TRUE(generator.getStateTab().empty());
}

TEST(PrefixTable, PrefixSizeEqualsNPREF) {
    TextGenerator generator;
    std::istringstream in("gh hd gdsf");
    generator.createTableOfPrefixesAndSuffixes(in);
    auto& tab = generator.getStateTab();
    for (auto& entry : tab) {
        EXPECT_EQ(static_cast<int>(entry.first.size()), generator.getNPREF());
    }
}

TEST(PrefixTable, PrefixSuffixEntryIsCorrect) {
    TextGenerator generator;
    std::istringstream in("one two three");
    generator.createTableOfPrefixesAndSuffixes(in);
    auto& tab = generator.getStateTab();
    std::deque<std::string> key = { "one", "two" };
    ASSERT_GT(tab.count(key), 0u);
    EXPECT_EQ(tab[key][0], "three");
}

TEST(PrefixTable, MultipleEntriesAreCorrect) {
    TextGenerator generator;
    std::istringstream in("a b c d");
    generator.createTableOfPrefixesAndSuffixes(in);
    auto& tab = generator.getStateTab();
    std::deque<std::string> key1 = { "a", "b" };
    std::deque<std::string> key2 = { "b", "c" };
    ASSERT_GT(tab.count(key1), 0u);
    ASSERT_GT(tab.count(key2), 0u);
    EXPECT_EQ(tab[key1][0], "c");
    EXPECT_EQ(tab[key2][0], "d");
}

TEST(PrefixTable, SamePrefixMultipleSuffixes) {
    TextGenerator generator;
    std::istringstream in("a b c a b d");
    generator.createTableOfPrefixesAndSuffixes(in);
    auto& tab = generator.getStateTab();
    std::deque<std::string> key = { "a", "b" };
    ASSERT_GT(tab.count(key), 0u);
    EXPECT_EQ(tab[key].size(), 2u);
}

TEST(SuffixSelection, SingleSuffixAlwaysSelected) {
    TextGenerator generator;
    std::istringstream in("a b c");
    generator.createTableOfPrefixesAndSuffixes(in);
    std::ostringstream out;
    generator.generateText(out);
    EXPECT_EQ(out.str(), "c\n");
}

TEST(SuffixSelection, MultipleSuffixesSelectsValidOne) {
    TextGenerator generator;
    std::istringstream in("a b c a b d");
    generator.createTableOfPrefixesAndSuffixes(in);
    auto& tab = generator.getStateTab();
    std::deque<std::string> key = { "a", "b" };
    std::vector<std::string>& suffixes = tab[key];
    for (auto& s : suffixes) {
        EXPECT_TRUE(s == "c" || s == "d");
    }
}

TEST(SuffixSelection, MultipleSuffixesProduceDifferentResults) {
    std::set<std::string> results;
    for (int i = 0; i < 100; i++) {
        srand(i);
        TextGenerator generator;
        std::istringstream in("a b c a b d");
        generator.createTableOfPrefixesAndSuffixes(in);
        std::ostringstream out;
        generator.generateText(out);
        results.insert(out.str());
    }
    EXPECT_GT(results.size(), 1u);
}

TEST(TextGeneration, GeneratedTextDoesNotExceedMaxLength) {
    TextGenerator generator;
    std::istringstream in("a b c d e f g h");
    generator.createTableOfPrefixesAndSuffixes(in);
    std::ostringstream out;
    generator.generateText(out);
    std::istringstream counter(out.str());
    std::string word;
    int count = 0;
    while (counter >> word) count++;
    EXPECT_LE(count, generator.getMAXGEN());
}

TEST(TextGeneration, EmptyTableDoesNotCrash) {
    TextGenerator generator;
    std::ostringstream out;
    EXPECT_NO_THROW(generator.generateText(out));
}
