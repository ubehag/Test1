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
bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream&, Student_info&);
std::istream& read(std::istream&, Student2&, bool&);
std::istream& read_hw(std::istream&, std::vector<double>&);
