#include "stdafx.h"
#include "Converter.h"


Converter::Converter()
{
}


Converter::~Converter()
{
}

string Converter::str_to_hex(string src, bool upper_case) {

	stringstream ss;
	string desc = "";

	for (int i = 0; i < src.length(); i++) {

		ss << std::hex << setfill('0') << setw(2) << (upper_case ? std::uppercase : std::nouppercase) << (int)src[i];
	}

	desc = ss.str();

	return desc;
}

string Converter::hex_to_str(string src) {

	string desc = "";
	stringstream ss;
	string code = "";

	for (int i = 0, ch = 0; i < src.length(); i++) {

		code += src[i];
		if (ch == 1) {
			ss << (char)strtoul(code.c_str(), NULL, 16);
			code.clear();
			ch = 0;
		}
		else {
			ch++;
		}
		
		
	}

	desc = ss.str();

	return desc;
}

string Converter::zip_pocket(string src) {

	string desc = "";
	stringstream ss;
	string code = "";

	for (int i = 0, ch = 0; i < src.length(); i++) {

		code += src[i];

		if (ch == 1) {

			if (code == FEND) {
				ss << FESC << TFEND;
			}
			else if (code == FESC) {
				ss << FESC << TFESC;
			}
			else {
				ss << code;
			}

			code.clear();
			ch = 0;
		}
		else {
			ch++;
		}


	}

	desc = FEND + ss.str() + FEND;

	return desc;
}

string Converter::unzip_pocket(string src) {

	string desc = "";
	stringstream ss;
	string code = "";
	string code_next = "";

	for (int i = 2, ch = 0; i < src.length() - 2; i++) {

		code += src[i];
		code_next += src[i+2];

		if (ch == 1) {

			if (code == FESC) {
				if (code_next == TFEND) {
					ss << FEND;
				}
				else if (code_next == TFESC) {
					ss << FESC;
				}
				i += 2;
			}
			else {
				ss << code;
			}

			code.clear();
			code_next.clear();
			ch = 0;
		}
		else {
			ch++;
		}

	}

	desc = ss.str();

	return desc;
}
