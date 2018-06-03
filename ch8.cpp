#include "stdafx.h"

#ifdef WILLNOTCOMPILE


template <class T>  // "this is a template func, that will take a TYPE PARAMETER" -> using T in the func means T is TYPE NAME
T median(vector<T> v) {  // T is type found in vector, and return type
	typedef typename vector<T>::size_type vec_sz;
	// type vector<T> depends on the template.
	// member ::size_type of that type (vector<T>) is itself a type.
	// this we must tell the implementation by using TYPENAME.
	vec_sz size = v.size();
	if (size == 0)
		throw domain_error("median of empty vector");
	sort(v.begin(), v.end());
	vec_sze mid = size / 2;
	return size % 2 == 0 ? (v[mid] + v[mid - 1]) / 2 : v[mid];
}  // any mentioning of 'v' IMPLICITLY involves the template type

template <class T, class U>
U median_iterator(T b, T e) {
	if (b == e)
		throw domain_error("median of empty vector");
	sort(b, e);
	T::distance_type mid = std::distance(b, e) / 2;
	T it = b;
	for (int i = 0; i != mid; ++i, ++it)
		; // now 'it' is either middle element, or one past middle if even number of elements
	if (size % 2 == 0) { // median value is "between" the two middle items
		T tmp = it;
		--tmp;
		return (*it + *tmp) / 2;
	}
	else return *it;
}


//* ITERATORS *//
// SEQUENTIAL READ-ONLY access == INPUT iterators
template <class In, class X> In findX(In begin, In end, const X& x) {
	while (begin != end && *begin != x) // comparing ; dereferencing '*'
		++begin; // only change to begin -> we know it is sequential access
	return begin;
}
// SEQUENTIAL WRITE-ONLY access == OUTPUT iterators
template <class In, class Out> Out copy(In begin, In end, Out dest) {
	while (begin != end)
		*dest++ = *begin++; // dereference, assign, increment
	return dest;
}
// SEQUENTIAL READ-WRITE access == FORWARD iterator
template <class For, class X>
void replace(For beg, For end, const X& x, const X& y) {
	while (beg != end) {
		if (*beg == x)
			*beg = y;
		++beg;
	}
}
//REVERSIBLE access == BIDIRECTIONAL iterator
template <class Bi>
void reverse(Bi begin, Bi end) {
	while (begin != end) {
		--end;
		if (begin != end)
			swap(*begin++, *end);
	}
}
//RANDOM access
template <class Ran, class X>
bool binary_search(Ran begin, Ran end, const X& x) {
	while (begin < end) {
		Ran mid = begin + (end - begin) / 2;
		if (x < *mid)
			end = mid;
		else if (*mid < x)
			begin = mid + 1;
		else return true;
	}
	return false;
}

// Dynamic splitting to ANY kind of container/output stream/ Output Iterator
template <class Out>
void split(const string& str, Out os) {
	typedef string::const_iterator iter;
	iter i = str.begin();
	while (i != str.end()) {
		i = find_if(i, str.end(), not_space);
		iter j = find_if(i, str.end(), space);
		if (i != str.end())
			*os++ = string(i, j);
		i = j;
	}
}

int main() {
	vector<int> vi;
	int med = median(vi); // use is INSTANTIATION of template, now we know what T is

	string s;
	while (getline(cin, s))
		split(s, ostream_iterator<string>(cout, "\n"));
	
	return 0;
}

#endif

#include "student_info.h"
#include <vector>
using std::vector;
#include <algorithm>
using std::transform;
#include <iostream>
using std::cout;
using std::endl;
/*
template <class T>
double grade_func(const Student_info& s) {
	// here, relay calls to correct func...
}*/
double median(vector<double>&) {
	cout << "\nMedian..\n";
	return 0.1;
}
double average_anal(const Student_info& s) {
	cout << "\nAverage for - " << s.name << endl;
	return 1.0;
}
double median_anal(const Student_info& s) {
	cout << "\nMedian_a for - " << s.name << endl;
	return 1.1;
}
double optimistic_med(const Student_info& s) {
	cout << "\nOptimistic_m for - " << s.name << endl;
	return 1.2;
}


template <class T>
double analyse(const vector<Student_info>& students, T grade_func(const Student_info&)) {
	vector<double> grades;
	transform(students.begin(), students.end(), back_inserter(grades), grade_func);
	return median(grades);
}

using std::cin;
using std::string;
vector<string> split_line(const string& line) {
	vector<string> ret;
	string::size_type i = 0;
	while (i != line.size()) {
		while (i != line.size() && isspace(line[i]))
			++i;
		string::size_type j = i;
		while (j != line.size() && !isspace(line[j]))
			++j;
		if (i != j) {
			ret.push_back(line.substr(i, j - i));
			i = j;
		}
	}
	return ret;
}
void read_students(vector<Student_info>& students) {
	string line;
	cout << "Enter <name, mid, fin, hw-hw-hw-hw\n";
	while (getline(cin, line) && line != "q" && line != "Q") {
		vector<string> words;
		words = split_line(line);
		Student_info s;
		s.name = words[0];
		s.midterm = atof(words[1].c_str());
		s.finals = atof(words[2].c_str());
		vector<string>::const_iterator hw_it = words.begin();
		++hw_it;
		++hw_it;
		++hw_it;
		for (hw_it; hw_it != words.end(); ++hw_it)
			s.homework.push_back(atof((*hw_it).c_str()));
		students.push_back(s);
	}
}

void ex8_1() {
	vector<Student_info> students;
	read_students(students);
	analyse(students, average_anal);
	analyse(students, median_anal);
	analyse(students, optimistic_med);
}

template <class T>
bool my_equal(const T it_b, const T it_e, T it_b2) { // 1, 2 : input iterators not moved, 3 : moved sequentially Write
	cout << " (eq) ";
	T it = it_b;
	while (it != it_e && *it == *it_b2) {
		++it;
		++it_b2;
	}
	if (it == it_e)
		return true;
	return false;
}

template <class T, class V>
T my_find(const T it_b, const T it_e, const V& v) { // iterators not moved -> input
	cout << " (find) ";
	T it = it_b;
	while (it != it_e && *it != v)
		++it;
	return it;
}

template <class T>
T my_copy(T it_b, T it_e, T it_d) { // 1, 2 : not moved, 3 : moved sequentially Write
	cout << " (copy) ";
	T it = it_b;
	while (it != it_e) {
//		int i = *it;
//		*it_d = i;
//		++it_d;
//		++it;
		*(it_d++) = *(it++);
	}
	return it_d;
}

template <class T, class V> // (copy if different)
T my_remove_copy_if(const T it_b, const T it_e, T it_d, bool p(V)) { //1, 2 : not moved, 3 : sequential Write
	cout << " (rem_cpy_if) ";
	T it = it_b;
	T ret;
	while (it != it_e) {
		if (!p(*it)) {
//			*(it_d++) = *it;
			*it_d = *it;
			++it_d;
		}
		++it;
	}
	ret = it_d; // start of matches (after non-matches)
	it = it_b;
	while (it != it_e) {
		if (p(*it)) {
//			*(it_d++) = *it;
			*it_d = *it;
			++it_d;
		}
		++it;
	}
	it_d = ret;
	return it_d;
}

template <class T, class V>  // f takes one arg.  call f() on sequence.  d can be same as b.  f returns what we put into d
T my_transform(const T it_b, const T it_e, T it_d, V f) { // 1, 2 : not moved; input, 3 : seq Write
	cout << " (trans) ";
	T it = it_b;
	while (it != it_e) {
		*it_d = f(*it);
		++it_d;
		++it;
	}
	return it_d;
}

template <class T, class V>
V my_accumulate(T it_b, T it_e, const V& v) { // sequential read only
	cout << " (acc) ";
	T it = it_b;
	V sum = v;
	while (it != it_e) {
		sum += *it++;
	}
	return sum;
}

template <class T> // find [b2,e2) in [b, e)
T my_search(T it_b, T it_e, T it_b2, T it_e2) { // sequential read only. Forward
	cout << " (search) ";
	T it = it_b;
	T it2 = it_b2;
	T found_it = it_e;
	while (it != it_e) { // look for possible start:
		if (*it == *it2) { // look for entire range
			found_it = it;
			while (it != it_e && it2 != it_e2 && *it == *it2) { // while they are the same
				++it;
				++it2;
			}
			if (it2 == it_e2)
				return found_it;
			found_it = it_e; // else broke out of loop before substr was found
			it2 = it_b2;
		}
		else ++it;
	}
	return found_it;
}

template <class T, class V>
T my_find_if(T it_b, T it_e, bool p(V)) {
	cout << " (findIf) ";
	T it = it_b;
	while (it != it_e && !p(*it))
		++it;
	return it;
}

template <class T, class V>  // copy those that do NOT match, return dest.end
T my_remove_copy(T it_b, T it_e, T it_d, const V& v) { // 1, 2 : input only , 3: seq Write
	cout << " (rem_cpy) ";
	T it = it_b;
	while (it != it_e) {
		if (*it == v)
			*it_d++ = *it;
		++it;
	}
	return it_d;
}

template <class T, class V> // rearrange elements so that the NON-matches are in the front of the seq, returns iter to first AFTER
T my_remove(T it_b, T it_e, const V& v) { // sequential access, sequential Write
	cout << " (rem) ";
	T it = it_b;
	T it_front = it_b;
	while (it != it_e) {
		if (*it != v) {
//			T it_tmp = it_front;
			V val = *it;
			*it = *it_front;
			*it_front = val;
			++it_front;
		}
		++it;			
	}
	return it_front;
}

template <class T, class V> // all ele where p==true up front
T my_partition(T it_b, T it_e, bool p(V)) {
	cout << " (part) ";
	T it = it_b;
	T it_front = it_b;
	while (it != it_e) {
		if (p(*it)) {
			V val = *it;
			*it = *it_front;
			*it_front = val;
			++it_front;
		}
		++it;
	}
	return it_front;
}

#include <list>
using std::list;

bool mycmp(int i) {
	return i == 1 ? true : false;
}
int my_trans(int i) {
	return i += 100;
}
bool more_than(int i) {
	return i > 50 ? true : false;
}
bool part_cmp(string s) {
	return s == "sei" ? true : false;
}
void ex8_2() {
	list<int> l1{ 1,2,3,4,5,6,7 };
	list<int> l2{ 1,2,3,4,5,6,7 };
	list<int> l3{ 2,4,7,8,8,8,8 };
	list<string> s1{ "hei" };
	//bool my_equal(const T it_b, const T it_e, T it_b2); // 1, 2 : input iterators not moved, 3 : moved sequentially Write
	cout << "My_equal:\n";
	if (my_equal(l1.begin(), l1.end(), l2.begin()))
		cout << "Fant en match!\n";
	else cout << ":-( Fant ikke like.\n";
	if (my_equal(l1.begin(), l1.end(), l3.begin()))
		cout << ":-( Fant en match!\n";
	else cout << "Fant ikke like.\n";
/*	if (my_equal(l1.begin(), l1.end(), s1.begin()) == l1.end())
		cout << "Fant ikke like.\n";
	else cout << ":-( Fant en match!\n";*/

	// T my_find(const T it_b, const T it_e, const V& v); // iterators not moved -> input
	cout << "--------------------\nMy_find:\n";
	list<int>::iterator it = my_find(l1.begin(), l1.end(), 5);
	if (it != l1.end())
		cout << "Fant en match!\n";
	else cout << ":-( Fant ikke.\n";
	it = my_find(l1.begin(), l1.end(), 500);
	if (it != l1.end())
		cout << ":-( Fant en match!\n";
	else cout << "Fant ikke.\n";

	//	T my_copy(const T it_b, const T it_e, T it_d); // 1, 2 : not moved, 3 : moved sequentially Write
	cout << "--------------------\nMy_copy:\n";
	vector<int> v1{ 1,2,3,4,5,6,7,8,9,0 };
	vector<int> a_copy (v1.size());
	vector<int>::iterator iter = a_copy.begin();
	my_copy(v1.begin(), v1.end(), iter);
	for (vector<int>::const_iterator i = a_copy.begin(); i != a_copy.end(); ++i)
		cout << *i << " - ";
	cout << endl;
	iter = a_copy.begin();
	vector<int>::iterator i_t = v1.begin();
	++i_t++;
	iter = my_copy(i_t, v1.end(), iter);
	for (vector<int>::const_iterator i = a_copy.begin(); i != iter; ++i)
		cout << *i << " - ";
	cout << endl;

	//T my_remove_copy_if(const T it_b, const T it_e, T it_d, bool p); //1, 2 : not moved, 3 : sequential Write
	cout << "--------------------\nMy_remove_copy:\n"; // first n elements does not match p, from it_d they match
	list<int> l4{ 1,2,3,2,344,1,1 };
	list<int> ldest (l4.size());
	list<int>::iterator it2 = ldest.begin();
	it2 = my_remove_copy_if(l4.begin(), l4.end(), it2, mycmp);
	cout << "\nMatch: \n";
	for (list<int>::const_iterator i = it2; i!=ldest.end(); ++i)
		cout << *i << " - ";
	cout << endl;
	cout << "Don't match: \n";
	for (list<int>::const_iterator i = ldest.begin(); i != it2; ++i)
		cout << *i << " - ";
	cout << endl;

	//T my_transform(const T it_b, const T it_e, T it_d, V f); // 1, 2 : not moved; input, 3 : seq Write
	cout << "--------------------\nMmy_transform:\n";
	list<int> l5{ 1,2,3,4,5 };
	list<int> res (l5.size());
	list<int>::iterator newlistit = res.begin();
	my_transform(l5.begin(), l5.end(), newlistit, my_trans);
	for (list<int>::const_iterator i = l5.begin(); i != l5.end(); ++i)
		cout << *i << " - ";
	cout << endl;
	for (list<int>::const_iterator i = res.begin(); i != res.end(); ++i)
		cout << *i << " - ";
	cout << endl;

	//V my_accumulate(T it_b, T it_e, const V& v); // sequential read only
	cout << "--------------------\nMy_accum:\n";
	vector<int> v3{ 1,2,3 };
	cout << " - " << my_accumulate(v3.begin(), v3.end(), 10) << " -\n";

	// 	T my_search(T it_b, T it_e, T it_b2, T it_e2); // sequential read only. Forward
	cout << "--------------------\nMy_search:\n";
	list<int> findin{ 1,2,3,4,6,1,2,3, 4,5 };
	list<int> findme{ 4,5 };
	list<int>::iterator found = my_search(findin.begin(), findin.end(), findme.begin(), findme.end());
	while (found != findin.end()) {
		cout << *found << " - ";
		++found;
	}
	cout << endl;

	// 	T my_find_if(T it_b, T it_e, bool p);
	cout << "--------------------\nMy_find_if:\n";
	vector<int> v4{ 33, 1,2,3,4,55 };
	vector<int>::iterator found_if = my_find_if(v4.begin(), v4.end(), more_than);
	if (found_if != v4.end())
		cout << "Found this: " << *found_if;
	else cout << "Found none";
	cout << endl;

	//	T my_remove_copy(T it_b, T it_e, T it_d, const V& v); // 1, 2 : input only , 3: seq Write
	cout << "--------------------\nMy_rem_cpy:\n";
	list<string> slist{ "hei", "nei", "sei", "nei", "nei", "nei", "blei", "grei", "sei" };
	list<string> rlist (slist.size());
	list<string>::iterator same = my_remove_copy(slist.begin(), slist.end(), rlist.begin(), "nei");
	cout << "Diffs:\n";
	for (list<string>::const_iterator i = rlist.begin(); i != same; ++i)
		cout << *i << " ";
	cout << endl;

	//	T my_remove(T it_b, T it_e, const V& v); // sequential access, sequential Write //re-arrange
	cout << "--------------------\nMy_remove:\n";
	same = my_remove(slist.begin(), slist.end(), string("nei"));
	cout << "Diffs:\n";
	for (list<string>::const_iterator i = slist.begin(); i != same; ++i)
		cout << *i << " ";
	cout << endl << "Same:\n";
	for (list<string>::const_iterator i = same; i != slist.end(); ++i)
		cout << *i << " ";
	cout << endl;

	// T my_partition(T it_b, T it_e, bool p);
	cout << "--------------------\nMy_partition:\n";
	slist = { "hei", "nei", "sei", "nei", "nei", "nei", "blei", "grei", "sei" };
	list<string>::iterator listit = my_partition(slist.begin(), slist.end(), part_cmp);
	cout << "Same:\n";
	for (list<string>::const_iterator i = slist.begin(); i != listit; ++i)
		cout << *i << " ";
	cout << endl << "Diffs:\n";
	for (list<string>::const_iterator i = listit; i != slist.end(); ++i)
		cout << *i << " ";
	cout << endl;

}
	
