#include <deque>
#include <map>
#include <string>
#include <vector>
using namespace std;

class TextGenerator {
	typedef deque<string> prefix;          // очередь префиксов
	map<prefix, vector<string> > statetab; // префикс-суффиксы

	const int NPREF = 2; // количество слов в префиксе
	const int MAXGEN = 2000; //объем текста на выходе

	public:
		void createTableOfPrefixesAndSuffixes(istream& in);
		void generateText(ostream& out);
		void add(deque<string>& prefix, const string& suffix);
		map<prefix, vector<string>>& getStateTab() { return statetab; }
		int getNPREF() const { return NPREF; }
		int getMAXGEN() const { return MAXGEN; }

};