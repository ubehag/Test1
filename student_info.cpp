#include "stdafx.h"

#include "student_info.h"

#include "grade.h"

using std::istream;
using std::vector;

/*
bool compare(const Student_info& x, const Student_info& y) {
	return x.name < y.name; // use std::string's '<'
}
*/

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

// CHAPTER 9:
std::istream& Stud_info::read(std::istream& in) {
	in >> n >> mid >> finals;
	read_hw(in, homework);
	return in;
}
double Stud_info::grade() const {
	return ::grade(mid, finals, homework); // "use the version that is not a member of anything!"
}

// this is part of our interface, so it should be declared in the same place as the class and defined same place as the member funcs.
bool compare(const Stud_info& x, const Stud_info& y) {
	return x.name() < y.name();
}

Stud_info::Stud_info() : mid(0), finals() {} // DEFAULT constructor (no params)
	// init these to 0 - 'n' and 'homework' are implicitly inited
Stud_info::Stud_info(istream& is) { read(is); } // 'read()' func does the work
// MID and FINALS are given explicit values only at VALUE-INIT, i.e. 