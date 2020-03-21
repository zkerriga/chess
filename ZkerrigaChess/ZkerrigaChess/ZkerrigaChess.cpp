//
// Progect has started at	22:47 
//							19.03.2020
//

#include <iostream>
#include <string>

#include "FigureClasses.h"
#include "DeskClass.h"
using namespace std;

void coordinate_parser(string command, ChessDesk *chess_desk) {
	int x1, x2, y1, y2;
	x1 = command[0] - 'a';
	y1 = 8 - (command[1] - '0');
	x2 = command[3] - 'a';
	y2 = 8 - (command[4] - '0');
	if (x1 < 0 || x1 > 7 || x2 < 0 || x2 > 7 || y1 < 0 || y1 > 7 || y2 < 0 || y2 > 7) {
		cout << "Invalid coordinates!" << endl;
	}
	else {
		chess_desk->move(x1, y1, x2, y2);
	}
}

int main() {
	//Create a desk
	ChessDesk *chess_desk = new ChessDesk;
	chess_desk->print_chess_desk();

	string command;
	for (int i = 0; i < 4; i++) {
		getline(cin, command);
		coordinate_parser(command, chess_desk);
		chess_desk->print_chess_desk();
	}

	//Close program on Enter
	if (getchar() == 13) exit(0);
	return 0;
}
