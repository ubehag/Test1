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
}
bool failgrade(const Student_info& s) {
	return grade(s) < 60;
}

int main() {
	return 0;
}