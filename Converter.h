#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Converter {

	// FEND -> FESC + TFEND
	// FESC -> FESC + TFESC
	const string FEND = "7E";
	const string FESC = "7D";
	const string TFEND = "5E";
	const string TFESC = "5D";

public:
	Converter();
	~Converter();
	string str_to_hex(string src, bool upper_case = true);
	string hex_to_str(string src);
	string zip_pocket(string src);
	string unzip_pocket(string src);
};

