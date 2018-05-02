#include "stdafx.h"

#include "student_info.h"

using std::istream;
using std::vector;

bool compare(const Student_info& x, const Student_info& y) {
	return x.name < y.name; // use std::string's '<'
}

istream& read(istream& is, Student_info& s) {
	is >> s.name >> s.midterm >> s.finals;
//	std::cout << "* " << s.name << ' ' << s.midterm << ' ' << s.finals << std::endl;
	read_hw(is, s.homework);  // which does not reset stream.state if it was not OK when arriving there
	//std::cout << "BLING?? ("<<s.name<<")\n";
	//std::cout << "   return from read " << "("<<s.name<<") "<< std::endl << std::flush;
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
//	else 		std::cout << "-readhw(err)-\n";

	return is;
}