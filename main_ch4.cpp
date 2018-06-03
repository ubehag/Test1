#include "stdafx.h"

#include <ios>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <stdexcept>
#include "grade.h"
#include "student_info.h"

using std::cin;
using std::cout;
using std::endl;
using std::streamsize;
using std::setprecision;
using std::sort;
using std::domain_error;
using std::max;
using std::vector;
using std::string;

void ch4_final() {
	vector<Student_info> students;
	Student_info record;
	string::size_type maxlen = 0;

	cout << "Enter name and grade: ";
	while (read(cin, record)) {
		maxlen = max(maxlen, record.name.size());
		students.push_back(record);
		//		cout << " - added - " << record.name << endl;
	}
	//	cout << "\ncompute\n";
	sort(students.begin(), students.end(), compare); // how to specify which version of compare to use?!?! (stud_info.h)
	for (vector<Student_info>::size_type i = 0; i != students.size(); ++i) {
		//		cout << ("***");
		cout << students[i].name << string(maxlen + 1 - students[i].name.size(), ' ');
		try {
			double final_grade = grade(students[i]);
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade << setprecision(prec);
		}
		catch (domain_error e) {
			cout << e.what();
		}
		cout << endl;
	}
}

void ch4ex_1() {
	string::size_type maxlen = 0;
	Student_info s;
	max(s.name.size(), maxlen);
}

void ch4ex_2() {
	for (int i = 0; i != 101; ++i) {
		cout << std::setw(3) << i << std::setw(6) << i * i << endl;
	}
}

void ch4ex_5() {
	cout << "Word counting: \n";
	vector<string> v;
	string w;
	int noof = 0;
	while (cin >> w && w != "q") {
		v.push_back(w);
		++noof;
	}
	cout << endl << "Number of words: " << noof << endl;
	sort(v.begin(), v.end());
	int count = 0;
	int i;
	for (i = 0; i != v.size(); ++i) {

		if (i != 0 && v[i] != v[i - 1])
			cout << count << endl;

		if (i == 0 || v[i] != v[i - 1])
			cout << v[i] << " ";

		if (i == 0 || v[i] == v[i - 1])
			++count;
		else count = 1;
	}
	if (i != 0)
		cout << count << endl;
}

void ch4ex_6() {
	cout << "Enter studname  mid final hw_grades - quit by 'q'\n";
	vector<Student2> students;
	Student2 s;
	bool q = false;
	while (!q) {
		read(cin, s, q);
		if (!q)
			students.push_back(s);
	}
	cout << "FINAL SCORES:\n";
	for (vector<Student2>::size_type i = 0; i != students.size(); ++i)
		cout << students[i].name << "  " << students[i].finalgrade << endl;

}

void ch4ex_7() {
	cout << "Enter doubles, I'll give you the average!\n";
	vector<double> v;
	double d;
	while (cin >> d) {
		v.push_back(d);
	}
	double sum = 0;
	for (vector<double>::size_type i = 0; i != v.size(); ++i) {
		sum += v[i];
	}
	cout << "Average is " << sum / v.size() << endl;
}

int main4() {
	//ch4_final();
	ch4ex_7();
	return 0;
}