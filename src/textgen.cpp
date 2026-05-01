#include "textgen.h"
#include <iostream>
void TextGenerator::createTableOfPrefixesAndSuffixes(istream& in) {
	if(!in) {
		cerr << "Ошибка при открытии входного потока\n";
		return;
	}
	string word;
	deque<string> prefix;
	bool first = true;
	while (in >> word) {
		if (prefix.size() == NPREF) {
			add(prefix, word);
			prefix.pop_front();
		}
		prefix.push_back(word);
	}
	if (prefix.size() == 1) prefix.pop_front();
	if (!prefix.empty()) {
		add(prefix, "");
	}
}
void TextGenerator::add(deque<string>& prefix, const string& suffix) {
	statetab[prefix].push_back(suffix);
}
void TextGenerator::generateText(ostream& out) {
	if (statetab.empty()) {
		out << "таблица пуста";
		return;
	}
	prefix current = statetab.begin()->first; 
	for (int i = 0; i < MAXGEN; i++) {
		vector<string>& suffixes = statetab[current];

		if (suffixes.empty()) break;

		string suffix = suffixes[rand() % suffixes.size()];

		if (suffix == "") break;

		if (i > 0) out << " ";
		out << suffix;

		current.pop_front();
		current.push_back(suffix);
	}

	out << "\n";
}
