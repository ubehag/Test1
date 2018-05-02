#include "stdafx.h"

#include "student_info.h"

#include "grade.h"

using std::istream;
using std::vector;

bool compare(const Student_info& x, const Student_info& y) {
	return x.name < y.name; // use std::string's '<'
}

istream& read(istream& is, Student_info& s) {
	is >> s.name >> s.midterm >> s.finals;
	read_hw(is, s.homework);  // which does not reset stream.state if it was not OK when arriving there
	return is;
}

istream& read_hw(istream& is, vector<double>& hw) {
	if (is) { // might be in error state before arriving here! 
	//	std::cout << "-readhw(ok)-\n";
		hw.clear(); // may be full of previous
		double x;
		while (is >> x) // may fail due to eof, or encountering a non-grade --> FAILURE STATE
			hw.push_back(x);
		is.clear(); // clear stream error state to make it ready for next student (ignore the reason why above loop stopped)
	}

	return is;
}

istream& read(istream& is, Student2& s, bool& q) {
	q = false;
	std::string name;
	is >> name;
	if (name != "q") {
		s.name = name;
		double mid, fin;
		is >> mid >> fin;
		vector<double> hw;
		read_hw(is, hw);  // which does not reset stream.state if it was not OK when arriving there
		s.finalgrade = grade(mid, fin, hw);
	}
	else q = true;
	return is;
}

istream& read_hw2(istream& is, vector<double>& hw) {
	if (is) { // might be in error state before arriving here! 
			  //	std::cout << "-readhw(ok)-\n";
		hw.clear(); // may be full of previous
		double x;
		while (is >> x) // may fail due to eof, or encountering a non-grade --> FAILURE STATE
			hw.push_back(x);
		is.clear(); // clear stream error state to make it ready for next student (ignore the reason why above loop stopped)
	}

	return is;
}