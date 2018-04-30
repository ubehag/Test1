//////////////////////////////////////
//* CHAPTER 3 *//* Batches of data *//
//////////////////////////////////////
#include "stdafx.h"


#include <iomanip>
#include <ios> // streamsize
#include <iostream> // setprecision (noof significant digits)
#include <string>

#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::setprecision;
using std::string;
using std::streamsize;

int ch3_1();
int ch3_2();
int ch3();
int ch3_ex();
int ch4();


int main () {
	return ch4();
}

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::sort;
using std::endl;

double median(vector<double> vec) {
	typedef vector<double>::size_type vec_sze; // define this as a local type name
	vec_sze size = vec.size();
	if (size == 0)
		throw domain_error("Median of empty vector");
	sort(vec.begin(), vec.end());
	vec_sze mid = size / 2;
	return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}

int ch4() {

}


int ex3_4() {
	cout << "Enter words ... (^c to end)";
	string input;
	string l;
	string sh;
	while (cin >> input) {
		if (input.size() > l.size())
			l = input;
		else if (input.size() < sh.size() || sh.size()==0)
			sh = input;
	}
	cout << endl << "Longest word: \"" << l << "\" - length = " << l.size() << endl;
	cout << "Shortest word: \"" << sh << "\" - length = " << sh.size() << endl;
	return 0;
}

int ex3_3() {
	cout << "Enter words.. > ";
	string word;
	vector<string> words;
	while (cin >> word) {
		words.push_back(word);
	}
	cout << endl;
	sort(words.begin(), words.end());
	string prev;
	int count = 0;
	for (int i = 0; i != words.size(); ++i) {
		string current = words[i];
		if (current != prev) { // new word!
			if (prev.size()) { // had one before
				cout << "..." << count << endl;
			}
			cout << current;
			prev = current;
			count = 1;
		}
		else ++count;
	}
	if (prev.size()) cout << "..." << count << endl;
	return 0;
}

int ex3_2() {
	cout << "Enter a set of ints: ";
	int i;
	vector<int> vec;
	int count = 0;
	while (cin >> i) {
		vec.push_back(i);
		++count;
	}
	sort(vec.begin(), vec.end());
	cout << endl << "Quartiles:\n";
	int quartile = 0;
	quartile = count / 4;
	int index = 0;
	for (int j = 0; j != 4; ++j) { // four rounds
		for (int i = 0; i != quartile; ++i) {
			cout << vec[index++] << endl;
		}
		cout << "---------\n";
	}
	if (index != count) cout << ".... and the rest ...\n";
	while (index != count) {
		cout << vec[index++] << endl;
	}
	return 0;
}



int ex3_5() {
	const int noofgrades = 5;
	string name;
	double grade;
	vector<string> names;
	vector<double> grades;
	while (cin >> name && (name != "Q" || name != "q"))  {
		int gcount = 0;
		double total = 0;
		int counter = noofgrades;
		while (counter--) {
			cin >> grade;
			total += grade;
			++gcount;
		}
		cout << "grades " << total << "count " << gcount << endl;
		names.push_back(name);
		grades.push_back(total / gcount);
	}
	for (int i = 0; i != names.size(); ++i) {
		cout << "* " << names[i] << " - " << grades[i] << endl;
	}
	return 0;
}

int ch3_ex() {
	return ex3_5();
}


int ch3() {
	// using simple average for homewrk grades
	cout << "Please enter student name: ";
	string name;
	cin >> name;

//	return ch3_1(); // simple average of homework grades
	return ch3_2();

	
	
}

using std::vector;
using std::sort;

int ch3_2() {
	cout << "Enter midterm and final exam grades: ";
	double midterm, finall;
	cin >> midterm >> finall;
	cout << "Enter all homework grades, "
		"followed by e-o-f: ";
	// finding median of homework the middle value of a sorted collection (or average of the two in the middle if even noof values)
	double x;
	vector<double> homework;
	while (cin >> x)
		homework.push_back(x);
	
	typedef vector<double>::size_type vec_sz; // "DEFINE" new name
	vec_sz size = homework.size();
	if (size == 0) {
		cout << endl << "You must enter some grades. Please try again." << endl;
		return 1; // fail
	}
	sort(homework.begin(), homework.end()); // algorithm> -> nondecreasing order (some elements may be the same)
	vec_sz mid = size / 2; // rounds down
	double median;
	median = size % 2 == 0 ? // is there a remainer, i.e. was the count odd or even?
		(homework[mid] + homework[mid - 1]) / 2
		: homework[mid];
	streamsize prec = cout.precision();
	cout << "Your final grade: " << setprecision(3) << 0.2*midterm + 0.4*finall + 0.4*median
		<< setprecision(prec) << endl;

	return 0;
}

int ch3_1() {
	cout << "Enter midterm and final exam grades: ";
	double midterm, finall;
	cin >> midterm >> finall;
	cout << "Enter all homework grades, "
		"followed by e-o-f: ";
	int count = 0;
	double sum = 0;
	double x; // temp
			  // invariant: we have 'count' grades so far, these are 'sum'-med together
	while (cin >> x) {
		++count;
		sum += x;
	}
	// We want three significant digits -- generally two before and one after the decimal point
	streamsize prec = cout.precision();
	cout << "Final grade = " << setprecision(3) << 0.2*midterm + 0.4*finall + sum / count << setprecision(prec) << endl;
	// Remember to reset precision to 'original' afterwards (will happen at end of program)
	// Alternative method (not that tightly set around the area where it is needed):
	prec = cout.precision(3);
	cout << "Once again: " << 0.2*midterm + 0.4*finall + sum / count << endl;
	cout.precision(prec);

	return 0;
}