#pragma once
#include <string>
#include <windows.h>
using namespace std;


class ErrorGenerator {
private:
	static string error_line;

public:
	static void set(string error) {
		error_line = error;
	}
	static void print() {
		if (error_line.size() > 0) {
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(handle, 12); //light red
			cout << "		" << error_line << endl;
			SetConsoleTextAttribute(handle, 8); //Light gray
			reset();
		}
		else
			cout << endl;
	}
	static void reset() {
		error_line = "";
	}
};

string ErrorGenerator::error_line = ""; //Zeroing a static variable
