#include "stdafx.h"

#include "student_info.h"
#include "grade.h"

using std::vector;

bool failgrade(const Student_info& s);
bool failgrade(const Student2& s);

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
bool failgrade2(const Student2 s) {
	return s.finalgrade < 60;
}
vector<Student2> extract_fails4(vector<Student2>& students) {
	vector<Student2> fails;
	vector<Student2>::iterator iter = students.begin();
	while (iter != students.end()) {
		std::cout << " ..";
		if (failgrade2(*iter)) {
			fails.push_back(*iter);
			iter = students.erase(iter);
		}
		else ++iter;
	}
	std::cout << std::endl;
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
list<Student2> extract_fails(list<Student2>& students) {
	list<Student2> fails;
	list<Student2>::iterator iter = students.begin();
	while (iter != students.end()) {
		if (failgrade(*iter)) {
			fails.push_back(*iter);
			iter = students.erase(iter);
		}
		else ++iter;
	}
	return fails;
}
list<Student2> extract_fails6(list<Student2>& students) {
	list<Student2> fails;
	list<Student2>::iterator it = students.begin();
	list<Student2>::size_type passed = 0;
	while (it != students.end()) {
		if (failgrade(*it)) {
			fails.push_back(*it);
		}
		else {
			students.insert(students.begin(), *it); // inserts at the beginning; meaning (list) iterators after this insert are still valid.
													// If it was a vector, indexing would be better for keeping track but would need double increment
			++passed;
		}
		++it;
	}
	std::cout << "\nPassed " << passed << std::endl;
	students.resize(passed);
	return fails;
}
bool failgrade(const Student_info& s) {
	return grade(s) < 60;
}
bool failgrade(const Student2& s) {
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
list<string> split2(const string& s) {
	list<string> ret;
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
// ex 6_1 : using iterators:
vector<string> hcat_it(const vector<string>& left, const vector<string>& right) {
	vector<string> ret;
	string::size_type w1 = widest(left) + 1;
	//vector<string>::size_type i = 0, j = 0;
	vector<string>::const_iterator it_l = left.begin(), it_r = right.begin();
	while (it_l != left.end() && it_r != right.end()) {
		string s;
		if (it_l != left.end())
			s = *it_l;
		s += string(w1 - s.size(), ' ');
		if (it_r != right.end())
			s += *it_r;
		ret.push_back(s);
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
//if (getline(cin, line) && line != "Q" && line != "q") {
	while (getline(cin, line) && line != "Q" && line != "q") {
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

void add_stud(vector<Student2>& students, vector<string> studinfo) {
	Student2 s;
	double mid, fin, hw = 0;
	int hwcount = 0;
	for (vector<string>::size_type i= 0; i != studinfo.size(); ++i) {
		switch (i) {
		case 0: // name
			s.name = studinfo[i];
			break;
		case 1: // midterm
			mid = atof(studinfo[i].c_str());
			break;
		case 2: // final
			fin = atof(studinfo[i].c_str());
			break;
		default: // the rest are homework grades
			hw += atof(studinfo[i].c_str());
			hwcount++;
			break;
		}
	} // student can be added to output vector including calculated grade
	double grade = 0.2*mid + 0.4*fin;
	if (hwcount != 0) grade += 0.4*(hw / hwcount);
	s.finalgrade = grade;
	students.push_back(s);
}
void add_stud(list<Student2>& students, vector<string> studinfo) {
	Student2 s;
	double mid, fin, hw = 0;
	int hwcount = 0;
	for (vector<string>::size_type i = 0; i != studinfo.size(); ++i) {
		switch (i) {
		case 0: // name
			s.name = studinfo[i];
			break;
		case 1: // midterm
			mid = atof(studinfo[i].c_str());
			break;
		case 2: // final
			fin = atof(studinfo[i].c_str());
			break;
		default: // the rest are homework grades
			hw += atof(studinfo[i].c_str());
			hwcount++;
			break;
		}
	} // student can be added to output vector including calculated grade
	double grade = 0.2*mid + 0.4*fin;
	if (hwcount != 0) grade += 0.4*(hw / hwcount);
	s.finalgrade = grade;
	students.push_back(s);
}
#include <fstream>
using std::ifstream;
void read_students(vector<Student2>& studs) {
	cout << "Please enter file name: ";
	string filename;
	cin >> filename;
	ifstream infile;
	infile.open(filename);

	string line;
	while (getline(infile, line)) {
		vector<string> v;
		v = split(line);
		add_stud(studs, v);
	}
	infile.close();
}
void read_students(list<Student2>& studs) {
	cout << "Please enter file name: ";
	string filename;
	cin >> filename;
	ifstream infile;
	infile.open(filename);

	string line;
	while (getline(infile, line)) {
		vector<string> v;
		v = split(line);
		add_stud(studs, v);
	}
	infile.close();
}
void ch5_ex2() {
	// read students from file, extract failing students
	vector<Student2> vstudents;
	read_students(vstudents);
	vector<Student2> dumpstud = extract_fails4(vstudents);

	cout << "Passing students: \n";
	for (vector<Student2>::const_iterator it = vstudents.begin(); it != vstudents.end(); ++it)
		cout << it->name << "   " << it->finalgrade << endl;
	cout << "\nFailing students: \n";
	for (vector<Student2>::const_iterator it = dumpstud.begin(); it != dumpstud.end(); ++it)
		cout << it->name << "   " << it->finalgrade << endl;
	cout << "********************";

	// list version:
	list<Student2> lstudents;
	read_students(lstudents);
	list<Student2> dumpstuds = extract_fails6(lstudents);
	cout << "LISTS:: \nPassing students: \n";
	for (list<Student2>::const_iterator it = lstudents.begin(); it != lstudents.end(); ++it)
		cout << it->name << "   " << it->finalgrade << endl;
	cout << "\nFailing students: \n";
	for (list<Student2>::const_iterator it = dumpstuds.begin(); it != dumpstuds.end(); ++it)
		cout << it->name << "   " << it->finalgrade << endl;
	cout << "********************";
}

int ch5_ex3() {
	char c;
	cout << "Use lists or vectors? (l/v) > ";
	cin >> c;
	if (c == 'l' || c == 'L') {
		typedef list<Student2> collection;
		Student2 s;
	}
	else if (c == 'v' || c == 'V') {
		typedef vector<Student2> collection;
	}
	else {
		cout << "Unknown type\n";
		return 1;
	}
	return 0;
}

string to_lower(const string& s) {
	string ls;// = s; // to know we have enough
	string::size_type i;
	for (i = 0; i != s.length(); ++i)
		ls.push_back(s[i]);
	return ls;
}
void ch5_ex9() {
	cout << "Please enter words, upper and lower case: ";
	string line;
	getline(cin, line);
	list<string> words;
	words = split2(line);
	// upper and lower case words in separate containers
	list<string> lowercase;
	list<string> uppercase;
	for (list<string>::const_iterator it = words.begin(); it != words.end(); ++it) {
		string all_low = to_lower(*it);
		if (all_low == *it)
			lowercase.push_back(*it);
		else uppercase.push_back(*it);
	}
	cout << "\nSeparated:\n";
	for (list<string>::const_iterator it = lowercase.begin(); it != lowercase.end(); ++it)
		cout << "* " << *it << endl;
	cout << "-------------\n";
	for (list<string>::const_iterator it = uppercase.begin(); it != uppercase.end(); ++it)
		cout << "- " << *it << endl;
	cout << "-------------\n";
}

bool is_pal(const string& s) {
	string::size_type i, j;
	for (i = 0, j = s.size()-1; i < j; ++i, --j)
		if (s[i] != s[j])
			return false;
	return true;
}
list<string> find_pals(const string& line) {
	list<string> pals = split2(line);
	list<string>::iterator it = pals.begin();
	while (it != pals.end()) {
		if (!is_pal(*it))
			it = pals.erase(it);
		else ++it;
	}
	return pals;
}
void ch5_ex10() {
	/*cout << "Enter file name for dictionary: ";
	string filename;
	cin >> filename;*/
	cout << "Enter palindromes and other strings, finish with 'q' on a separate line.\n";
	string line;
	list<string> palindromes;
	while (getline(cin, line) && line != "q" && line != "Q") {
		palindromes = find_pals(line);
	}

	cout << "Here are the palindromes:\n";
	string::size_type lng = 0;
	list<string>::const_iterator longest = palindromes.begin();
	for (list<string>::const_iterator it = palindromes.begin(); it != palindromes.end(); ++it) {
		cout << "- " << *it << endl;
		if ((*it).size() > lng) {
			longest = it;
			lng = it->size();
		}
	}
	cout << "And the longest of them is: \n" << *longest << "   (" << lng << ")\n";
}

// ascenders / descenders
bool has_scender(const string& s) {
	for (string::size_type i = 0; i != s.size(); ++i) {
		switch (s[i]) {
		case 'b':
		case 'd':
		case 'f':
		case 'g':
		case 'h':
		case 'j':
		case 'k':
		case 'l':
		case 'p':
		case 'q':
		case 't':
		case 'y':
			return true;
		}
	}
	return false;
}
void find_scenders(vector<string>& has, vector<string>& hasnot, const vector<string>& input) {
	for (vector<string>::const_iterator it = input.begin(); it != input.end(); ++it) {
		if (has_scender(*it)) has.push_back(*it);
		else hasnot.push_back(*it);
	}
}
void ch5_ex11() {
	cout << "Enter words, quit w Q:\n";
	string line;
	vector<string> xscending;
	vector<string> plain;
	while (getline(cin, line) && line != "Q" && line != "q") {
		vector<string> words = split(line);
		find_scenders(xscending, plain, words);
	}
	cout << "\n\nWords w ascenders or descenders:\n";
	for (vector<string>::const_iterator it = xscending.begin(); it != xscending.end(); ++it) {
		cout << *it << endl;
	}
	cout << "\nWords keeping strictly to the narrowest vertical space:\n";
	for (vector<string>::const_iterator it = plain.begin(); it != plain.end(); ++it) {
		cout << *it << endl;
	}
}

int main5() {
//	ch5_splitstring();
//	ch5_splittest();
//	ch5_8();
//	ch5_ex2();
	ch5_ex11();
	return 0;
}