#include "stdafx.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

using std::domain_error;
using std::sort;
using std::vector;

double median(vector<double> vec) {
	typedef vector<double>::size_type vec_sze;
	vec_sze size = vec.size();
	if (size == 0)
		throw domain_error("Empty vector gives no median");
	sort(vec.begin(), vec.end());
	vec_sze mid = size / 2;
	return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}