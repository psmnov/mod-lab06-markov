// Copyright 2026 Petr Smirnov
#include "textgen.h"
#include <deque>
#include <iostream>
#include <string>
#include <vector>

void TextGenerator::createTableOfPrefixesAndSuffixes(std::istream& in) {
    if (!in) {
        std::cerr << "Cannot open input stream\n";
        return;
    }
    std::string word;
    std::deque<std::string> pref;
    while (in >> word) {
        if (static_cast<int>(pref.size()) == NPREF) {
            add(pref, word);
            pref.pop_front();
        }
        pref.push_back(word);
    }
    if (pref.size() == 1) {
		pref.pop_front();
    }
    if (!pref.empty()) {
        add(pref, "");
    }
}

void TextGenerator::add(std::deque<std::string>& pref,
    const std::string& suffix) {
    statetab[pref].push_back(suffix);
}

void TextGenerator::generateText(std::ostream& out) {
    if (statetab.empty()) {
        out << "table is empty";
        return;
    }
    prefix current = statetab.begin()->first;
    for (int i = 0; i < MAXGEN; i++) {
        std::vector<std::string>& suffixes = statetab[current];
        if (suffixes.empty()) break;
        std::string suffix = suffixes[rand() % suffixes.size()];
        if (suffix == "") break;
        if (i > 0) out << " ";
        out << suffix;
        current.pop_front();
        current.push_back(suffix);
    }
    out << "\n";
}