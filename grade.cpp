#include "stdafx.h"

#include <stdexcept>
#include <vector>
#include "grade.h"
#include "median.h"
#include "student_info.h"

using std::domain_error;
using std::vector;

double grade(double midterm, double finals, double homework) {
	return 0.2*midterm + 0.4*finals + 0.4*homework;
}

double grade(double midterm, double finals, const vector<double>& homework) {
	if (homework.size() == 0)
		throw domain_error("No homework done by this student");
	return grade(midterm, finals, median(homework));
}

double grade(const Student_info& s) {
	return grade(s.midterm, s.finals, s.homework);
}

double grade(const Student2& s) {
	return s.finalgrade;
}
