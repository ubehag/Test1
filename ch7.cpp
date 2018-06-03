
#include "stdafx.h"
#include <string>
#include <map>
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::map;


int main7_1() {
	string s;
	map<string, int> counters;
	while (cin >> s && s != "q")
		++counters[s]; // find - or add - ele w key=s; increment its int
	for (map<string, int>::const_iterator it = counters.begin(); it != counters.end(); ++it)
		cout << it->first << ":\t" << it->second << endl;
	return 0;
}

#include <vector>
using std::vector;
using std::istream;
vector<string> splitline(const string& line) {
	vector<string> ret;
	string::size_type i = 0;
	while (i != line.size()) {
		while (i != line.size() && isspace(line[i]))
			++i;
		string::size_type j = i;
		while (j != line.size() && !isspace(line[j]))
			++j;
		if (i != j) {
			ret.push_back(line.substr(i, j - i));
			i = j;
		}
	}
	return ret;
}
#include <list>
using std::list;
list<string> splitline_l(const string& line) {
	list<string> ret;
	string::size_type i = 0;
	while (i != line.size()) {
		while (i != line.size() && isspace(line[i]))
			++i;
		string::size_type j = i;
		while (j != line.size() && !isspace(line[j]))
			++j;
		if (i != j) {
			ret.push_back(line.substr(i, j - i));
			i = j;
		}
	}
	return ret;
}
map<string, vector<int> > xref(istream& in, vector<string> find_words(const string&) = splitline) { // NB splitline is DEFAULT arg to use if omitted from call
	string line;
	int line_number = 0;
	map<string, vector<int> > ret;

	while (getline(in, line) && line != "q") {
		++line_number;
		vector<string> words = find_words(line);
		for (vector<string>::const_iterator it = words.begin(); it != words.end(); ++it) {
			// add same line number only once
			map<string, vector<int>>::const_iterator w = ret.find(*it);
			if (w == ret.end()) // first occurence
				ret[*it].push_back(line_number);
			else {
				vector<int>::const_iterator lookup = w->second.begin();
				while (lookup != w->second.end() && *lookup != line_number)
					++lookup;
				if (lookup == w->second.end())
					ret[*it].push_back(line_number);
			}
			// *it == one word from input line == index
			// ret[*it] returns the VALUE, a vector<int>, holding line numbers, onto which a new number is push-back'ed
			// if it was first occurence of this word, the vector<int> is VALUE-INITALIZED == w/o elements
		}
	}
	return ret;
}

void sort_word_count_ex71(map<string, int>);
void count_words() {
	//xref(cin); // or xref(cin, find_urls); // from ch6(?)
	cout << "Enter words, line by line:\n";
	map<string, vector<int>> ret = xref(cin);

	for (map<string, vector<int>>::const_iterator it = ret.begin(); it != ret.end(); ++it) {
		cout << it->first << " occurs on line(s): ";
		vector<int>::const_iterator line_it = it->second.begin();
		cout << *line_it; // the first line number
		++line_it;
		while (line_it != it->second.end()) {
			cout << ", " << *line_it;
			++line_it;
		}
		cout << endl;
	}
}

void sort_word_count_ex71() {
	cout << "Enter words, quit w Q: \n";
	map<string, int> words;
	string s;
	while (cin >> s && s != "q" && s != "Q")
		++words[s];
	// foreach ele in that map: sort by V.size();
	map<int, vector<string>> by_freq;
	for (map<string, int>::const_iterator it = words.begin(); it != words.end(); ++it)
		by_freq[it->second].push_back(it->first);
	cout << "Number of occurences: \n";
	for (map<int, vector<string>>::const_iterator it = by_freq.begin(); it != by_freq.end(); ++it) {
		cout << it->first << " :\n";
		for (vector<string>::const_iterator w = it->second.begin(); w != it->second.end(); ++w)
			cout << *w << endl;
	}
}

typedef vector<string> Rule; // one or more choices
typedef vector<Rule> Rule_collection; // one or more specifications
typedef map<string, Rule_collection> Grammar; // set of rules

//typedef list<string> RuleL; 
//typedef list<Rule> Rule_collectionL;
//typedef map<string, Rule_collectionL> GrammarL; // set of rules

Grammar read_grammar(istream& in) {
	Grammar ret;
	string line;
	while (getline(in, line)) {
		vector<string> entry = splitline(line);
		if (!entry.empty()) // use category 'name' to store rule (blank lines are discarded)
			// the first word 'entry[0]' of the line is the category name
			;//ret[entry[0]].push_back(Rule(entry.begin() + 1, entry.end()));
	}
	return ret;
}
/*GrammarL read_grammar_l(istream& in) {
	GrammarL ret;
	string line;
	while (getline(in, line)) {
		list<string> entry = splitline_l(line);
		if (!entry.empty()) // use category 'name' to store rule (blank lines are discarded)
							// the first word 'entry[0]' of the line is the category name
			//ret[entry[0]].push_back(Rule(entry.begin() + 1, entry.end()));
			ret[*entry.begin()].push_back(RuleL(entry.begin()+1, entry.end()));
	}
	return ret;
}*/
bool bracketed(const string& s) {
	return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}
#include <stdexcept>
using std::logic_error;
int nrand(int n) {
	if (n <= 0 || n > RAND_MAX)
		throw std::domain_error("Arg to nrand is out of range");
	const int bucket_size = RAND_MAX / n;
	int r;
	do
		r = rand() / bucket_size;
	while (r >= n);
	return r;
}
void gen_aux(const Grammar& g, const string& word, vector<string>& ret) {
	if (!bracketed(word))
		ret.push_back(word); // recursion stops when "real" word encountered
	else {
		Grammar::const_iterator it = g.find(word); // no direct referencing g[word] since that would create the entry if not found!!!
		if (it == g.end())
			throw logic_error("empty rule!");
		// fetch set of possible rules
		const Rule_collection& c = it->second;
		// from which we select one at random
		const Rule& r = c[nrand(c.size())];
		// recursively expand the given rule
		for (Rule::const_iterator it = r.begin(); it != r.end(); ++it)
			gen_aux(g, *it, ret);
	}
}
/*void gen_aux_l(const Grammar& g, const string& word, list<string>& ret) {
	if (!bracketed(word))
		ret.push_back(word); // recursion stops when "real" word encountered
	else {
		GrammarL::const_iterator it = g.find(word); // no direct referencing g[word] since that would create the entry if not found!!!
		if (it == g.end())
			throw logic_error("empty rule!");
		// fetch set of possible rules
		const Rule_collectionL& c = it->second;
		// from which we select one at random
		const RuleL& r = c[nrand(c.size())];
		// recursively expand the given rule
		for (RuleL::const_iterator it = r.begin(); it != r.end(); ++it)
			gen_aux(g, *it, ret);
	}
}*/
vector<string> gen_sentence(const Grammar& g) {
	vector<string> ret;
	gen_aux(g, "<sentence>", ret);
	return ret;
}
list<string> gen_sentence_l(const Grammar& g) {
	vector<string> ret;
	gen_aux(g, "<sentence>", ret);
	list<string> retlist;
	for (vector<string>::const_iterator it = ret.begin(); it != ret.end(); ++it)
		retlist.push_back(*it);
	return retlist;
}
void ch7_4() {
	vector<string> sentence = gen_sentence(read_grammar(cin));
	vector<string>::const_iterator it = sentence.begin();
	if (!sentence.empty()) {
		cout << *it;
		++it;
	}
	while (it != sentence.end()) {
		cout << " " << *it;
		++it;
	}
	cout << endl;
}
void ch7_4x5() {
	list<string> sentence = gen_sentence_l(read_grammar(cin));
	list<string>::const_iterator it = sentence.begin();
	if (!sentence.empty()) {
		cout << *it;
		++it;
	}
	while (it != sentence.end()) {
		cout << " " << *it;
		++it;
	}
	cout << endl;
}
using std::domain_error;
int nrand_x(const int n) {
	int ret = n;
	if (ret <= 0)
		domain_error("Input <= 0");
	if (ret > RAND_MAX)
		ret = RAND_MAX;
	return nrand(ret);
}
int main7() {
//	count_words();
//	ch7_4();
//	sort_word_count_ex71();
	return 0;
}