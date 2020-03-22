//
// Progect has started at	22:47 
//							19.03.2020
//

#include <iostream>
#include <string>
#include <cstdlib>

#include "FigureClasses.h"
#include "DeskClass.h"
#include "FigureClasses.h"
using namespace std;

void coordinate_parser(string command, ChessDesk *chess_desk) {
	int x1, x2, y1, y2;
	if (command[0] > 'A' && command[0] < 'Z')
		x1 = command[0] - 'A';
	else
		x1 = command[0] - 'a';
	y1 = 8 - (command[1] - '0');
	if (command[3] > 'A' && command[3] < 'Z')
		x2 = command[3] - 'A';
	else
		x2 = command[3] - 'a';
	y2 = 8 - (command[4] - '0');
	if (x1 < 0 || x1 > 7 || x2 < 0 || x2 > 7 || y1 < 0 || y1 > 7 || y2 < 0 || y2 > 7) {
		ErrorGenerator::set("Invalid coordinates!");
	}
	else {
		chess_desk->move(x1, y1, x2, y2);
	}
}

#define TEXT 8
#define TEXT2 11 //6 - yellow
#define EMPHASIS 14 //light yellow

void print_hint() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, TEXT2);
	cout << endl << endl;
	cout << "	It is time to return to the past the game industry!" << endl;
	cout << "	Awful graphics, uncomfortable gameplay and that's not all!" << endl << endl;
	SetConsoleTextAttribute(handle, TEXT);
	cout << "	To make moves, enter commands of this format: ";
	SetConsoleTextAttribute(handle, EMPHASIS);
	cout << "e2-e4" << endl;
	SetConsoleTextAttribute(handle, TEXT);
	cout << "	To end the game, enter: ";
	SetConsoleTextAttribute(handle, EMPHASIS);
	cout << "stop" << endl << endl;

	SetConsoleTextAttribute(handle, TEXT);
	cout << "	A little help:" << endl;
	SetConsoleTextAttribute(handle, EMPHASIS);
	cout << "		1";
	SetConsoleTextAttribute(handle, TEXT);
	cout << " is a pawn		";
	SetConsoleTextAttribute(handle, EMPHASIS);
	cout << "#";
	SetConsoleTextAttribute(handle, TEXT);
	cout << " is a rook" << endl;
	SetConsoleTextAttribute(handle, EMPHASIS);
	cout << "		?";
	SetConsoleTextAttribute(handle, TEXT);
	cout << " is a knight		";
	SetConsoleTextAttribute(handle, EMPHASIS);
	cout << "&";
	SetConsoleTextAttribute(handle, TEXT);
	cout << " is a queen" << endl;
	SetConsoleTextAttribute(handle, EMPHASIS);
	cout << "		!";
	SetConsoleTextAttribute(handle, TEXT);
	cout << " is a bishop		";
	SetConsoleTextAttribute(handle, EMPHASIS);
	cout << "$";
	SetConsoleTextAttribute(handle, TEXT);
	cout << " is a king" << endl << endl;

	SetConsoleTextAttribute(handle, TEXT2);
	string pass;
	cout << "	Let's start? ";
	getline(cin, pass);
	system("cls");
}

int main() {
	print_hint(); 
	//Create a desk
	ChessDesk *chess_desk = new ChessDesk;
	chess_desk->print_chess_desk();
	string command;
	while (true) {
		cout << endl << "     Your move:  ";
		getline(cin, command);
		if (command == "stop") {
			delete chess_desk;
			exit(0);
		}
		else if (command.size() != 5) {
			ErrorGenerator::set("Invalid command, try again! (input format: e2-e4)");
		}
		else
			coordinate_parser(command, chess_desk);
		system("cls");
		chess_desk->print_chess_desk();
	}
	system("pause");
	return 0;
}
