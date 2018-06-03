#include "stdafx.h"

#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

bool space(char c) {
	return isspace(c);
}
bool not_space(char c) {
	return !isspace(c);
}
vector<string> split_iter(const string& str) {
	typedef string::const_iterator iter;
	vector<string> ret;
	iter i = str.begin();
	while (i != str.end()) {
		i = find_if(i, str.end(), not_space); // ignore leading blanks
		iter j = find_if(i, str.end(), space); // find end of current word
		if (i != j)
			ret.push_back(string(i, j)); // copy [i,j)
		i = j;
	}
	return ret;
}

bool is_palindrome(const string& s) {
	return equal(s.begin(), s.end(), s.rbegin()); // compare two SEQUENCES
}

#include <cctype> // isalnum()
// finding URLs embedded in a string  protocol-name://resource-name
// protocol-name is letters only
// resource-name is letters, digits, certain punctuation chars
// : find '://', look for protocol-name in front and resource-name after
bool not_url_char(char c) {
	static const string url_ch = "~;/?:@=&$-_.+!*'(),"; // legal url chars in addition to alnum
	// STATIC local var is PRESERVED after first call
	return !(isalnum(c) || // to stop at what's no longer an url
		find(url_ch.begin(), url_ch.end(), c) != url_ch.end()); // FIND looks for a specific char
}
string::const_iterator url_end(string::const_iterator b, string::const_iterator e) {
	return find_if(b, e, not_url_char);
}
string::const_iterator url_beg(string::const_iterator b, string::const_iterator e) {
	static const string sep = "://";
	typedef string::const_iterator c_iter;
	c_iter i = b;
	while ((i = search(i, e, sep.begin(), sep.end())) != e) {
		// the separator shouldn't be at the beginning or end of the line
		if (i != b && i + sep.size() != e) {
			c_iter beg = i;
			while (beg != b && isalpha(beg[-1])) // b is beginning, "safe" to look at the byte _before_ current separator
				--beg;
			// at least one char before && after separator?
			if (beg != i && !not_url_char(i[sep.size()]))
				return beg;
		}
		i += sep.size(); // not a url -> read past separator
	}
	return e;
}
vector<string> find_urls(const string& s) {
	vector<string> ret;
	typedef string::const_iterator c_iter;
	c_iter b = s.begin(), e = s.end();
	while (b != e) {
		b = url_beg(b, e); // look for letters followed by ://
		if (b != e) {
			c_iter after = url_end(b, e); // find rest of url
			ret.push_back(string(b, after));
			b = after; // more urls on this line?
		}
	}
	return ret;
}

// students again... separate those that did hw from those who didn't
// Student_info from p62 / student.h
#include "student_info.h"
// read() func from p62 (and 57)
#include <iostream>
using std::istream;
using std::ostream;
//istream& read_hw(istream& in, vector<double>& hw);
//istream& read(istream& is, Student_info& s);
bool did_all_hw(const Student_info& s) {
	return ((find(s.homework.begin(), s.homework.end(), 0)) == s.homework.end()); // missing homework == 0
}

#include "grade.h"
#include <stdexcept>
using std::endl;
double grade_aux(const Student_info& s) { // auxiliary func
	try {
		return grade(s); // now the compiler knows the argument(s) and can decide which overload to use
	}
	catch (std::domain_error) { // prev grade func throws exception if no homework is done
		return grade(s.midterm, s.finals, 0);
	}
}
#include "median.h"
double median_analysis(const vector<Student_info>& students) {
	vector<double> grades;
	transform(students.begin(), students.end(), back_inserter(grades), grade_aux);;
	return median(grades);
}
void write_analysis(ostream& out, const string& name, double analysis(const vector<Student_info>&), 
					const vector<Student_info>& did, const vector<Student_info>& didnt) {
	out << name << ": median(did) = " << analysis(did) << ", median(didnt) = " << analysis(didnt) << endl;
}

using std::cin;
using std::cout;
double average_analysis(const vector<Student_info>&);
double optimistic_median_analysis(const vector<Student_info>&);
#include <numeric> // (accumulate)
double average(const vector<double>& v) {
	return accumulate(v.begin(), v.end(), 0.0) / v.size();
}
double average_grade(const Student_info& s) {
	return grade(s.midterm, s.finals, average(s.homework));
}
double average_analysis(const vector<Student_info>& students) {
	vector<double> grades;
	transform(students.begin(), students.end(), back_inserter(grades), average_grade);
	// (range begin, range end, iter destination, func to use)
	return median(grades);
}
double optimistic_median(const Student_info& s) { // reckon the missing homework equals the present, instead of counting as a 0
	vector<double> nonzero;
	remove_copy(s.homework.begin(), s.homework.end(), back_inserter(nonzero), 0); // copy those that DON't match given value to given destination
	if (nonzero.empty())
		return grade(s.midterm, s.finals, 0);
	return grade (s.midterm, s.finals, median(nonzero));
}
// TMP
double optimistic_median_analysis(const vector<Student_info>& students) { return 0; }

bool fgrade(const Student_info& s) {
	return s.finals < 60; // f.eks
}
bool pgrade(const Student_info& s) {
	return !fgrade(s);
}
vector<Student_info> extract_fails(vector<Student_info>& students) {
	// here the grade is calculated twice for each stud; in the calls to remove() and remove_if().
	vector<Student_info> fail;
	remove_copy_if(students.begin(), students.end(), back_inserter(fail), pgrade); // remove vs remove_if: cmp to value / predicate (func)
	students.erase(remove_if(students.begin(), students.end(), fgrade), students.end()); // iterators describing a range to remove
	return fail;
}
vector<Student_info> extract_fails_new(vector<Student_info>& students) {
	vector<Student_info>::iterator iter = stable_partition(students.begin(), students.end(), pgrade);
	vector<Student_info> fail(iter, students.end()); // initialize new vec w this range
	students.erase(iter, students.end());
	return fail;
}

int ch6() {
	vector<Student_info> did, didnt;
	Student_info student;
	while (read(cin, student)) {
		if (did_all_hw(student))
			did.push_back(student);
		else didnt.push_back(student);
	}
	if (did.empty()) {
		cout << "No students did all homework assignments!\n";
		return 1;
	}
	if (didnt.empty()) {
		cout << "All students did all their homework!\n";
		return 1;
	}
	write_analysis(cout, "median", median_analysis, did, didnt);
	write_analysis(cout, "average", average_analysis, did, didnt);
	write_analysis(cout, "median of homework done", optimistic_median_analysis, did, didnt);
	return 0;
}


void ch6ex3() {
	vector<int> u(10, 100);
	vector<int> v;
//	copy(u.begin(), u.end(), v.begin()); // crashes, adding elements to empty vector

	copy(u.begin(), u.end(), back_inserter(v)); //OK!
	vector<int> w(10);
	copy(u.begin(), u.end(), w.begin());

	cout << "V:\n";
	for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
		cout << *it << endl;
	cout << "W:\n";
	for (vector<int>::const_iterator it = w.begin(); it != w.end(); ++it)
		cout << *it << endl;
}
void ch6ex9() {
	vector<string> strings = { "alle", "fugler", "smaa", "de", "er" };
	string result = accumulate(strings.begin(), strings.end(), string(""));
	cout << "*\n" << result << "\n*\n";
}
int main6() {
	ch6ex9();

	return 0;
}