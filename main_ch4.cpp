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
	sort(students.begin(), students.end(), compare);
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

void ch4ex_2() {
	string::size_type maxlen = 0;
	Student_info s;
	max(s.name.size(), maxlen);
}

int main() {
	//ch4_final();
	ch4ex_2();
	return 0;
}