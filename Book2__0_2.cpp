// Book2_0.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <iostream>
#include <string>


void chapter0();
void chapter1();
void chapter2();
void chapter2_1();
void chapter2_ex_1();
void chapter3();
void chapter4();
void chapter5();
void chapter6();
void chapter7();
void chapter8();
void chapter9();
void chapter10();
void chapter11();
void chapter12();
void chapter13();
void chapter14();
void chapter15();


int main1() {
//	chapter0();
//	chapter1();
//	chapter2();
//	chapter2_1();
	chapter2_ex_1();
//	chapter2_ex_2();

	return 0;
}


///////////////
//* CH 2
void chapter2() {
	std::cout << std::endl;
	std::cout << "CHAPTER 2\n";
	std::cout << "Please enter first name: ";
	std::string name;
	std::cin >> name;
	const std::string greeting = "Hello, " + name + "!";

	const int pad = 1; // noof blank rows between text and frame -- valid also for the sides
	const int rows = pad * 2 + 3; // noof rows to write: text + 2*frame + 2*pad

	std::cout << std::endl; // (separate input and output)
	int r = 0;
	// invariant: we have written 'r' rows so far
	while (r != rows) {
		// how many chars to write:
		const std::string::size_type cols = greeting.size() + pad * 2 + 2; // same length for all lines -- use STRING::SIZE_TYPE for sizeof string!!
		std::string::size_type c = 0;
		// invariant: we have written 'c' cols (==chars) so far
		while (c != cols) {
			if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1) { // first or last row or column
				std::cout << "*";
				++c;
			}
			else {
				if (r == pad + 1 && c == pad + 1) { // are we past padding? (horizontal/vertical)
					std::cout << greeting;
					c += greeting.size();
				}
				else {
					std::cout << " ";
					++c;
				}
			}
		}
		std::cout << std::endl;
		++r;
	}
}

//#include <iostream>
//#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
void chapter2_1() {
	cout << "Please enter first name: ";
	string name;
	cin >> name;
	const string greeting = "Hello " + name + "!";
	const int pad = 1;
	const int rows = pad * 2 + 3;
	const string::size_type cols = greeting.size() + pad * 2 + 2;
	cout << endl;
	for (int r = 0; r != rows; ++r) {
		string::size_type c = 0;
		while (c != cols) {
			if (r == pad + 1 && c == pad + 1) {
				cout << greeting;
				c += greeting.size();
			}
			else {
				if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1)
					cout << "*";
				else cout << " ";
				++c;
			}
		}
		cout << endl;
	}
}


#include <iostream>
#include <string>
void chapter2_ex_1() {
	using namespace std;
	using std::string;
	cout << "Enter name: ";
	string name;
	cin >> name;
	cout << endl;
	const string greeting = "Hello " + name + "!";
	// ex 2_1
	for (int l = 0; l != 3; ++l) { // one line at a time
		if (l == 0 || l == 2) {
			for (string::size_type c = 0; c != greeting.size() + 2; ++c)
				cout << "*";
			cout << endl;
		}
		else {
			string::size_type c = 0;
			while (c != greeting.size() + 2) {
				if (c == 0 || c == greeting.size() + 1) {
					cout << "*";
					++c;
				}
				else {
					cout << greeting;
					c += greeting.size();
				}
			}
			cout << endl;
		}
	}
	cout << endl;
	// ex 2_2
	const int hor_pad = 3;
	const int vert_pad = 2;
	int maxlines = vert_pad * 2 + 3;
	string::size_type maxcols = hor_pad * 2 + greeting.size() + 2;
	for (int linecount = 0; linecount != maxlines; ++linecount) {
		string::size_type c = 0;
		while (c != maxcols) {
			if (c == hor_pad + 1 && linecount == vert_pad + 1) {
				cout << greeting;
				c += greeting.size();
			}
			else {
				if (linecount == 0 || linecount == maxlines - 1 || c == 0 || c == maxcols - 1)
					cout << "*";
				else cout << " ";
				++c;
			}
		}
		cout << endl;
	}
	/*// ex 2_3
	string::size_type horspace = 0;
	cout << "How many spaces between frame and name? ";
	cin >> horspace;
	cout << endl;
	int verspace = 0;
	cout << "How many white lines between frame and name? ";
	cin >> verspace;
	cout << endl;
	maxlines = verspace * 2 + 3;
	maxcols = horspace * 2 + greeting.size() + 2;
	for (int linecount = 0; linecount != maxlines; ++linecount) {
		//string::size_type count = 0;
		//while (count != maxcols) {
		//	if (count == horspace + 1 && linecount == verspace + 1) {
		//		cout << greeting;
		//		count += greeting.size();
		//	}
		//	else {
		//		if (linecount == 0 || linecount == maxlines-1 || count == 0 || count == maxcols-1)
		//			cout << "*";
		//		else cout << " ";
		//		++count;
		//	}
		//}
		if (linecount != 0 && linecount != maxlines - 1) { // those two have * only
			 if (linecount == verspace + 1) { // this line needs text
				string::size_type c = 0;
				while (c != maxcols) {
					if (c == 0 || c == maxcols - 1) {
						cout << "*";
						++c;
					}
					else if (c <= horspace) {
						for (; c != horspace + 1; ++c) {
							cout << " ";
						}
					}
					else if (c == horspace + greeting.size()+1) {
						for (; c != maxcols-1; ++c)
							cout << " ";
					}
					else {
						cout << greeting;
						c += greeting.size();
					}
				}
			}
			else { // empty lines lined with *
				for (string::size_type c = 0; c != maxcols; ++c) {
					if (c == 0 || c == maxcols - 1)
						cout << "*";
					else
						cout << " ";
				}
			}
		}
		else {
			for (string::size_type i = 0; i != maxcols; ++i) // top && bottom rows
				cout << "*";
		}
		cout << endl;
	}*/
	// 2_5
	// square
	const int x = 8;
	for (int i = 0; i != x; ++i) {
		for (int j = 0; j != x; ++j)
			cout << "*";
		cout << endl;
	}
	cout << endl;
	// rectangle
	const int y = 16;
	for (int i = 0; i != y; ++i) {
		for (int j = 0; j != x; ++j)
			cout << "*";
		cout << endl;
	}
	cout << endl;
	// triangle
	const int maxline = 5;
	const int maxstar = 9;
	cout << endl;
	int blanks = (maxstar - 1) / 2;
	for (int i = 0; i != maxline; ++i) {
		for (int j = 0; j != blanks; ++j)
			cout << " ";
		for (int j = 0; j != i * 2 + 1; ++j)
			cout << "*";
		for (int j = 0; j != blanks; ++j)
			cout << " ";
		--blanks;
		cout << endl;
	}
	// 2_7
	cout << endl;
	const int too_low = -6;
	const int start = 10;
	for (int i = start; i != too_low; --i)
		cout << i << endl;
	// 2_8
	cout << endl;
	int prod = 1;
	for (int i = 1; i != 10;++i)
		prod *= i;
	cout << "Product of [1:10) = " << prod << endl;
	// 2_9
	cout << endl;
	cout << "Enter two numbers: ";
	int no1 = 0;
	cin >> no1;
	int no2 = 0;
	cin >> no2;
	cout << endl << "MAGIC: the largest of these two numbers is: " << __max(no1, no2) << endl;
}



///////////////
//* CH 1

//#include <string>
void ch1_2_framing();
void ch1_exercises();

void chapter1 () {
	std::cout << "CHAPTER 1::\n";
	std::cout << "Please enter first name: ";
	std::string name;
	std::cin >> name; // discarding initial whitespaces (' ' \t \backspace \n), continues until next whitespace (or eof)
	std::cout << "Hello, " << name << "!\n";
	ch1_2_framing();
	ch1_exercises();
}

//#include <iostream>
//#include <string>
void ch1_2_framing() {
	std::cout << "Please enter your first name: ";
	std::string name;
	std::cin >> name;
	const std::string greeting = "Hello, " + name + "!"; // build greeting message
	const std::string spaces(greeting.size(), ' '); // same amount of spaces as chars in greeting
	const std::string second = "* " + spaces + " *"; // second&fourth line
	const std::string first(second.size(), '*'); // first&last line: '*' same amount as the other lines' lengths

	std::cout << std::endl;
	std::cout << first << std::endl << second << std::endl << "* " << greeting << " *" << std::endl << second << std::endl << first << std::endl;
}

void ch1_exercises() {
	std::cout << "\nNAME, please> ";
	std::string name;
	std::cin >> name;
	std::cout << "HELLO, " << name << std::endl;
	std::cout << "AND what is yours? ";
	std::cin >> name;
	std::cout << "\nAnd hi to you too " + name << std::endl;
}


///////////////
//* CH 0
void chapter0() {
	std::cout << "CHAPTER 0::\n";
	std::cout << "Exercise 0-0:" << std::endl;
	std::cout << "Hello, World!" << std::endl; // std::cout is std::ostream type
	std::cout << "Exercise 0-2:" << std::endl;
	std::cout << "This (\") is a quote, and this (\\) is a backslash." << std::endl;
	std::cout << "Exercise 0-3:" << std::endl;
	std::cout << "My tabs look like this : '\t'. \nWonder how many spaces.. '      ' \nLet us do some counting: '......'" << std::endl;
	std::cout << "Exercise 0-4:" << std::endl;
	std::cout << "#include <iostream>\nint main() {\n\tstd:cout << \"Hello, world!!\" << std::endl;\n\n\treturn 0;\n}" << std::endl;
	std::cout << std::endl;
}
