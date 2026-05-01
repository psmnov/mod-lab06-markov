// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <sstream>
#include "textgen.h"

// таблица пуста если входной поток пуст
TEST(PrefixTable, EmptyInputGivesEmptyTable) {
    TextGenerator generator;
    istringstream in("");
    generator.createTableOfPrefixesAndSuffixes(in);
    EXPECT_TRUE(generator.getStateTab().empty());
}
// таблица пуста если слов меньше чем NPREF
TEST(PrefixTable, LessThanNPREFWordsGivesEmptyTable) {
    TextGenerator generator;
    istringstream in("поаывлао");
    generator.createTableOfPrefixesAndSuffixes(in);
    EXPECT_TRUE(generator.getStateTab().empty());
}
// каждый ключ таблицы имеет размер NPREF
TEST(PrefixTable, PrefixSizeEqualsNPREF) {
    TextGenerator generator;
    istringstream in("gh hd gdsf");
    generator.createTableOfPrefixesAndSuffixes(in);
    auto& tab = generator.getStateTab();
    for (auto& entry : tab) {
        EXPECT_EQ((int)entry.first.size(), generator.getNPREF());
    }
}
// префикс "раз два" имеет суффикс "три"
TEST(PrefixTable, PrefixSuffixEntryIsCorrect) {
    TextGenerator generator;
    istringstream in("раз два три");
    generator.createTableOfPrefixesAndSuffixes(in);
    auto& tab = generator.getStateTab();
    deque<string> key = { "раз", "два" };
    ASSERT_TRUE(tab.count(key) > 0);
    EXPECT_EQ(tab[key][0], "три");
}
// несколько префиксов формируются корректно
TEST(PrefixTable, MultipleEntriesAreCorrect) {
    TextGenerator generator;
    istringstream in("а б в г");
    generator.createTableOfPrefixesAndSuffixes(in);
    auto& tab = generator.getStateTab();
    deque<string> key1 = { "а", "б" };
    deque<string> key2 = { "б", "в" };
    ASSERT_TRUE(tab.count(key1) > 0);
    ASSERT_TRUE(tab.count(key2) > 0);
    EXPECT_EQ(tab[key1][0], "в");
    EXPECT_EQ(tab[key2][0], "г");
}
// один префикс с двумя разными суффиксами
TEST(PrefixTable, SamePrefixMultipleSuffixes) {
    TextGenerator generator;
    istringstream in("а б в а б е");
    generator.createTableOfPrefixesAndSuffixes(in);
    auto& tab = generator.getStateTab();
    deque<string> key = { "а", "б" };
    ASSERT_TRUE(tab.count(key) > 0);
    EXPECT_EQ(tab[key].size(), 2);
}
// единственный суффикс всегда выбирается один и тот же
TEST(SuffixSelection, SingleSuffixAlwaysSelected) {
    TextGenerator generator;
    istringstream in("а б в");
    generator.createTableOfPrefixesAndSuffixes(in);
    ostringstream out;
    generator.generateText(out);
    EXPECT_EQ(out.str(), "в\n");
}

// при нескольких суффиксах выбирается один из допустимых
TEST(SuffixSelection, MultipleSuffixesSelectsValidOne) {
    TextGenerator generator;
    istringstream in("а б в г д е");
    generator.createTableOfPrefixesAndSuffixes(in);
    auto& tab = generator.getStateTab();
    deque<string> key = { "а", "б" };
    vector<string>& suffixes = tab[key];
    for (auto& s : suffixes) {
        EXPECT_TRUE(s == "в" || s == "г");
    }
}
// за много запусков при нескольких суффиксах результат меняется
TEST(SuffixSelection, MultipleSuffixesProduceDifferentResults) {
    set<string> results;
    for (int i = 0; i < 100; i++) {
        srand(i);
        TextGenerator generator;
        istringstream in("а б в а б е");
        generator.createTableOfPrefixesAndSuffixes(in);
        ostringstream out;
        generator.generateText(out);
        results.insert(out.str());
    }
    EXPECT_GT(results.size(), 1);
}
// генерация не превышает MAXGEN слов
TEST(TextGeneration, GeneratedTextDoesNotExceedMaxLength) {
    TextGenerator generator;
    istringstream in("а б в г д е ё ж");
    generator.createTableOfPrefixesAndSuffixes(in);
    ostringstream out;
    generator.generateText(out);
    istringstream counter(out.str());
    string word;
    int count = 0;
    while (counter >> word) count++;
    EXPECT_LE(count, generator.getMAXGEN());
}

// генерация на пустой таблице
TEST(TextGeneration, EmptyTableDoesNotCrash) {
    TextGenerator generator;
    ostringstream out;
    EXPECT_NO_THROW(generator.generateText(out));
}