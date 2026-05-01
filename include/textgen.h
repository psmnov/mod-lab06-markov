// Copyright 2026 Petr Smirnov
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <deque>
#include <map>
#include <string>
#include <vector>
#include <iostream>

class TextGenerator {
    typedef std::deque<std::string> prefix;
    std::map<prefix, std::vector<std::string>> statetab;
    const int NPREF = 2;
    const int MAXGEN = 2000;

 public:
    void createTableOfPrefixesAndSuffixes(std::istream& in);
    void generateText(std::ostream& out);
    void add(std::deque<std::string>& prefix, const std::string& suffix);
    std::map<prefix, std::vector<std::string>>& getStateTab() {
        return statetab;
    }
    int getNPREF() const { return NPREF; }
    int getMAXGEN() const { return MAXGEN; }
};

#endif  // INCLUDE_TEXTGEN_H_
