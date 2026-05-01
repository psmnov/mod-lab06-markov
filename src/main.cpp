// Copyright 2026 Petr Smirnov
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include "textgen.h"

int main() {
    srand(static_cast<unsigned>(time(0)));
    TextGenerator generator;
    std::ifstream in(std::string(PROJECT_DIR) + "/src/input.txt");
    if (!in) {
        std::cerr << "Cannot open input.txt\n";
        return 1;
    }
    generator.createTableOfPrefixesAndSuffixes(in);
    std::ofstream out(std::string(PROJECT_DIR) + "/result/gen.txt");
    if (!out) {
        std::cerr << "Cannot open result/gen.txt\n";
        return 1;
    }
    generator.generateText(out);
    return 0;
}
