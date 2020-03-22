#pragma once
#include <iostream>
#include <map>
#include <ctime>
using namespace std;

class ChessTimer {
private:
	map <char, int> timer;
	int start_time;

public:
	ChessTimer() {
		timer['w'] = 0;
		timer['b'] = 0;
		start_time = clock();
	}
	~ChessTimer() {}

	void update_time(char whose_move) {
		timer[whose_move] += (clock() - start_time) / CLOCKS_PER_SEC; //Time calculation of one move
		start_time = clock();
	}
	void print_time(char color) {
		int all_sec = timer[color];
		cout << all_sec / 3600 << ":"; //hourse
		all_sec = all_sec % 3600;
		cout << all_sec / 60 / 10 << all_sec / 60 % 10 << ":"; //minutes
		all_sec = all_sec % 60;
		cout << all_sec / 10 << all_sec % 10 << endl; //seconds
	}
};