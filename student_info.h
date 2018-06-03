#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Student_info {
	std::string name;
	double midterm, finals;
	std::vector<double> homework;
};
struct Student2 {
	std::string name;
	double finalgrade;
};

// declare those functions that are very closely linked to Student_info
//bool compare(const Student_info&, const Student_info&); // ch4
std::istream& read(std::istream&, Student_info&);
std::istream& read(std::istream&, Student2&, bool&);
std::istream& read_hw(std::istream&, std::vector<double>&);

//ch9:

class Stud_info {
public:	// INTERFACE
	// constructors:
	Stud_info();
	Stud_info(std::istream&);

	std::istream& read(std::istream&);
	double grade() const; //"will not change any data member"
	std::string name() const { return n; } // return (r-o) name member
		// NB: INLINE definition of member func -> expand inline, avoid func-call overhead
		// NB: return COPY of member rather than reference, to avoid caller changing it.
	bool valid() const { return !homework.empty(); }

private: // IMPLEMENTATION
	std::string n;
	double mid, finals;
	std::vector<double> homework;
};


bool compare(const Stud_info&, const Stud_info&);

