#include "stdafx.h"

#include "student_info.h"
#include "grade.h"

using std::vector;

bool failgrade(const Student_info& s);

vector<Student_info> extract_fails1(vector<Student_info>& students) {
	// takes up space (keeping double copies)
	vector<Student_info> pass, fail;
	for (vector<Student_info>::size_type i = 0; i != students.size(); ++i)
		if (failgrade(students[i]))
			fail.push_back(students[i]);
		else pass.push_back(students[i]);
	students = pass;
	return fail;
}
vector<Student_info> extract_fails2(vector<Student_info>& students) {
	// takes time (erase on vector)
	vector<Student_info> fails;
	vector<Student_info>::size_type i = 0;
	// invariant: students[0,i) are passing
	while (i != students.size()) {
		if (failgrade(students[i])) {
			fails.push_back(students[i]);
			students.erase(students.begin() + i);
		}
		else ++i;
	}
	return fails;
}
vector<Student_info> extract_fails3(vector<Student_info>& students) {
	vector<Student_info> fails;
	vector<Student_info>::iterator iter = students.begin(); // not const, since we plan to modify 'students'
	while (iter != students.end()) {
		if (failgrade(*iter)) {
			fails.push_back(*iter);
			iter = students.erase(iter); // previous iter INVALIDATED since it is erased; iter now holds the element that FOLLOWS the erased one
		}
		else ++iter;
	}
	return fails;
}
// simply change from vector to lists:
#include <list>
using std::list;
list<Student_info> extract_fails(list<Student_info>& students) {
	list<Student_info> fails;
	list<Student_info>::iterator iter = students.begin();
	while (iter != students.end()) {
		if (failgrade(*iter)) {
			fails.push_back(*iter);
			iter = students.erase(iter);
		}
		else ++iter;
	}
	return fails;
}
bool failgrade(const Student_info& s) {
	return grade(s) < 60;
}

#include <cctype> // ISSPACE and other useful funcs for processing indiviidual chars
using std::string;
vector<string> split(const string& s) {
	vector<string> ret;
	typedef string::size_type string_size;
	string_size i = 0; // index of start of new word in input string 's'

	// invariant: we have processed [0,i) chars
	while (i != s.size()) {
		// ignore leading blanks
		while (i != s.size() && isspace(s[i]))
			++i; // find start of next word
		string_size j = i; // index of end of new word in input string 's'
		while (j != s.size() && !isspace(s[j]))
			++j; // while j is non-space == find end of this word
		if (i != j) { // we have some non-white chars;
			// copy from [i] j-i number of chars
			ret.push_back(s.substr(i, j - i));
			i = j;
		} // j never > size()
	}
	return ret;
}
using std::cin;
using std::cout;
using std::endl;
void ch5_splitstring() { // for now, crashing on norwegian chars
	string s;
	while (getline(cin, s)) { // returns istream to test
		vector<string> v = split(s);
		for (vector<string>::size_type i = 0; i != v.size(); ++i)
			cout << v[i] << endl;
	}
}
void ch5_splittest() {
	string s;
	while (cin >> s)
		cout << s << endl;
}

#include <algorithm>
using std::max;
string::size_type widest(const vector<string>& v) {
	string::size_type maxlen = 0;
	for (vector<string>::size_type i = 0; i != v.size(); ++i)
		maxlen = max(maxlen, v[i].size());
	return maxlen;
}
// input=vector<string>, output=new framed vector<string>
vector<string> frame(const vector<string>& v) {
	vector<string> ret;
	string::size_type maxlen = 0;
	string border(maxlen + 4, '*'); // '*'+' '+string+' '+'*' -> maxlen+4
	
	ret.push_back(border); // top frame
	for (vector<string>::size_type i = 0; i != v.size(); ++i) {
		ret.push_back("* " + v[i] + string(maxlen - v[i].size(), ' ') + "*"); // border' '+string+padding+border
	}
	ret.push_back(border); // bottom frame
	return ret;
}
// vertical concatination
vector<string> vcat(const vector<string>& top, const vector<string>& bottom) {
	vector<string> ret = top; // COPY top picture directly
//	for (vector<string>::const_iterator it = bottom.begin(); it != bottom.end(); ++it)
//		ret.push_back(*it);
	ret.insert(ret.end(), bottom.begin(), bottom.end());
	return ret;
}
vector<string> hcat(const vector<string>& left, const vector<string>& right) {
	vector<string> ret;
	string::size_type w1 = widest(left) + 1; // 1 space between the two
	vector<string>::size_type i = 0, j = 0; // index left and right
	while (i != left.size() || j != right.size()) { // until both are exhausted
		string s; // new string to hold lines from both sides
		if (i != left.size())
			s = left[i++];
		s += string(w1 - s.size(), ' '); // pad 1st part up to widest string in lefthand side
		if (j != right.size())
			s += right[j++];
		ret.push_back(s); // new line added to return vector
	}
	return ret;
}
void ch5_8() {
	// store framed 'picture'/'bitmap' line by line, frame it w one space between, left-aligned
	// vcat, hcat
}



struct Word {
	std::string word;
	int pos, lpos;
};


list<Word> splitline(string& line, int lineno) {
	list<Word> ret;
	string::size_type i=0, j=0;
	int count = 0;
	while (i != line.size()) {
		while (i != line.size() && isspace(line[i]))
			++i; // skip blanks
		j = i;
		while (j != line.size() && !isspace(line[j]))
			++j; // read until next blank
		if (i != j) {
			string s = string(line.substr(i, j - i));
			Word w;
			w.word = s;
			w.pos = ++count;
			w.lpos = ++lineno;
			ret.push_back(w);
		}
		i = j;
	}
	return ret;
}

bool sort_by_pos(const Word& w1, const Word& w2) {
	return w1.pos < w2.pos;
}
void make_presentable(vector<list<Word>>& allLines) { // each vector element a line == list of words
	for (vector<list<Word>>::const_iterator lineIt = allLines.begin(); lineIt != allLines.end(); ++lineIt) {
		list<Word> w = *lineIt;
		w.sort(sort_by_pos);
	}
}
bool cmp(const list<Word>& w1, const list<Word>&w2) {
	// in each list: tolower and cmp first word
	string s1, s2;
	s1 = w1.begin()->word;
	for (string::size_type i = 0; i != s1.size(); ++i)
		s1[i] = tolower(s1[i]);
	s2 = w2.begin()->word;
	for (string::size_type i = 0; i != s2.size(); ++i)
		s2[i] = tolower(s2[i]);
	return s1 < s2;
}
void ch5_ex1() {
	cout << "Enter phrase(s), end w/'q'\n: ";
	string line;
	int linecounter = 0;
if (getline(cin, line) && line != "Q" && line != "q") {
//	while (cin >> line && line != "Q" && line != "q") {
		// split line into words - to juggle around
		list<Word> words = splitline(line, linecounter);
		// juggle and print : delete word from front & push_back, sort, print
		vector<list<Word>> output; // each element is a line
		for (list<string>::size_type i = 0; i != words.size(); ++i) {
			words.push_back(*words.begin()); // append
			words.erase(words.begin()); //delete
			output.push_back(words);
		} // when loop is done we have a vector containing each of the juggled lines
		sort(output.begin(), output.end(), cmp);
		// re-order words before output
		make_presentable(output);

		for (vector<list<Word>>::size_type i=0; i!=output.size(); ++i) {
			cout << "* ";
			for (list<Word>::const_iterator it = output[i].begin(); it != output[i].end(); ++it)
				cout << it->word << " ";
			cout << endl;
		}
	}
}

int main() {
//	ch5_splitstring();
//	ch5_splittest();
//	ch5_8();
	ch5_ex1();
	return 0;
}