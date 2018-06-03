#include "stdafx.h"

#include <iostream>
#include <ios>
#include <iomanip>
#include "student_info.h"

#include <algorithm>
#include <vector>

#include <stdexcept>

using std::domain_error;

using std::vector;

using std::istream;
using std::cin;
using std::cout;
using std::endl;

using std::streamsize;
using std::setprecision;

using std::string;

using std::max;
using std::sort;

int main() {
	vector<Stud_info> students;
	Stud_info record; // value-init via default (no-param) constructor
	string::size_type maxlen = 0;

	cout << "Add student(s): name mid final hw hw hw ... \n";

	while (record.read(cin)) {
		maxlen = max(maxlen, record.name().size());
		students.push_back(record);
	}
	sort(students.begin(), students.end(), compare);

	for (vector<Stud_info>::size_type i = 0; i != students.size(); ++i) {
		cout << students[i].name() << string(maxlen + 1 - students[i].name().size(), ' ');
		try {
			double final_grade = students[i].grade();
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade << setprecision(prec) << endl;
		}
		catch (domain_error e) {
			cout << e.what() << endl;
		}
	}
	return 0;
}