#include <iostream>
#include <fstream>

#include "textgen.h"

using namespace std;

int main() {
	srand((unsigned)time(0));
	TextGenerator generator;
	ifstream in("input.txt");
	if (!in) {
		cerr << "Не удалось открыть файл input.txt\n";
		return 1;
	}
	generator.createTableOfPrefixesAndSuffixes(in);
	generator.generateText(cout);
	ofstream out(string(PROJECT_DIR) + "/result/gen.txt");
	generator.generateText(out);
	
	return 0;
}