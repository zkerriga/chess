//
// Progect has started at	22:47 
//							19.03.2020
//

#pragma once
#include <iostream>
#include <map>
#include <Windows.h>

#include "ErrorGenerator.h"
#include "FigureClasses.h"
#include "Timer.h"
using namespace std;

class ChessDesk {
private:
	char whose_move; //'w' or 'b' equal 'white' or 'black'
	map <char, int[2]> king_place;
	Figure *desk[8][8];
	ChessTimer chess_timer;

public:
	//Constructor:
	ChessDesk() {
		whose_move = 'w';
		char current_color = 'b';
		desk[0][0] = new Rook(current_color);
		desk[1][0] = new Knight(current_color);
		desk[2][0] = new Bishop(current_color);
		desk[3][0] = new Queen(current_color);
		desk[4][0] = new King(current_color);
		desk[5][0] = new Bishop(current_color);
		desk[6][0] = new Knight(current_color);
		desk[7][0] = new Rook(current_color);
		for (char y = 1; y < 7; y++) {
			for (char x = 0; x < 8; x++) {
				if (y == 1 || y == 6)
					desk[x][y] = new Pawn(current_color);
				else
					desk[x][y] = new EmptyFigure; //empty slots
			}
			if (y > 2)
				current_color = 'w';
		}
		desk[0][7] = new Rook(current_color);
		desk[1][7] = new Knight(current_color);
		desk[2][7] = new Bishop(current_color);
		desk[3][7] = new Queen(current_color);
		desk[4][7] = new King(current_color);
		desk[5][7] = new Bishop(current_color);
		desk[6][7] = new Knight(current_color);
		desk[7][7] = new Rook(current_color);
		king_place['w'][0] = 4;
		king_place['w'][1] = 7;
		king_place['b'][0] = 4;
		king_place['b'][1] = 0;
	}
	~ChessDesk() {
		cout << "Ou.. Is this the end?!";
	}

	void print_chess_desk() {
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, 8); //gray
		cout << endl << endl << "         A   B   C   D   E   F   G   H" << endl;
		for (int y = 0; y < 8; y++) {
			cout << "       ----+---+---+---+---+---+---+----" << endl << "     " << 8 - y << " ";
			for (int x = 0; x < 8; x++) {
				cout << "| ";
				if (desk[x][y]->get_figure_color() == 'b') {
					SetConsoleTextAttribute(handle, 3); //cyan
					cout << desk[x][y]->get_figure_sign();
					SetConsoleTextAttribute(handle, 8); //gray
				}
				else if (desk[x][y]->get_figure_color() == 'w') {
					SetConsoleTextAttribute(handle,15); //white
					cout << desk[x][y]->get_figure_sign();
					SetConsoleTextAttribute(handle, 8); //gray
				}
				else
					cout << desk[x][y]->get_figure_sign();
				cout << " ";
			}
			cout << "| " << 8 - y;
			if (y == 2) {
				if (whose_move == 'w') {
					SetConsoleTextAttribute(handle, 15); //white
					cout << "		White's move!" << endl;
					SetConsoleTextAttribute(handle, 8); //gray
				}
				else {
					SetConsoleTextAttribute(handle, 3); //cyan
					cout << "		Blue's move!" << endl;
					SetConsoleTextAttribute(handle, 8); //gray
				}
			}
			else if (y == 3)
				ErrorGenerator::print();
			else if (y == 4) {
				cout << "		Blue time: ";
				chess_timer.print_time('b');
			}
			else if (y == 5) {
				cout << "		White time: ";
				chess_timer.print_time('w');
			}
			else
				cout << endl;
		}
		cout << "       ----+---+---+---+---+---+---+----" << endl;
		cout << "         A   B   C   D   E   F   G   H" << endl;
	}
	bool is_someone_attacking_the_king(char c) {
		char find_color = (c == 'w') ? 'b' : 'w';
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				if (desk[x][y]->get_figure_color() == find_color) {
					if (desk[x][y]->ñan_a_figure_make_a_move(x, y, king_place[c][0], king_place[c][1], desk)) {
						return true;
					}
				}
			}
		}
		return false;
	}
	bool is_it_possible_to_make_a_rocker(char way) { //way == 'r', that equal right rocker or way == 'l', that equal left rocker
		int y_line = (whose_move == 'w') ? 7 : 0;
		int temp_x = king_place[whose_move][0];
		int temp_y = king_place[whose_move][1];
		if (way == 'l') {
			if (desk[0][y_line]->get_figure_sign() != '#' || desk[4][y_line]->get_figure_sign() != '$' ||
				desk[0][y_line]->get_moved_status() || desk[4][y_line]->get_moved_status())
				return false;
			//gsearch SHAH, change king_place
		}
		else if (way == 'r') {
			if (desk[7][y_line]->get_figure_sign() != '#' || desk[4][y_line]->get_figure_sign() != '$' ||
				desk[7][y_line]->get_moved_status() || desk[4][y_line]->get_moved_status())
				return false;
			//gsearch SHAH
		}
	}
	void move(int x1, int y1, int x2, int y2) {
		char current_figure = desk[x1][y1]->get_figure_sign();

		if (desk[x1][y1]->get_figure_color() != whose_move) {
			ErrorGenerator::set("This figure is not yours, try again!");
			return;
		}
		if (desk[x1][y1]->get_figure_color() == desk[x2][y2]->get_figure_color())
			ErrorGenerator::set("You can't eat your figure!");
		else if (desk[x1][y1]->ñan_a_figure_make_a_move(x1, y1, x2, y2, desk)) {
			Figure *temp = desk[x2][y2]; //Remind a figure
			desk[x2][y2] = desk[x1][y1];
			desk[x1][y1] = new EmptyFigure;
			if (current_figure == '$') {
				king_place[whose_move][0] = x2;
				king_place[whose_move][1] = y2;
			}
			if (is_someone_attacking_the_king(whose_move)) { //Search a SHAH
				ErrorGenerator::set("The king is under attack!");
				delete desk[x1][y1];
				if (current_figure == '$') {
					king_place[whose_move][0] = x1;
					king_place[whose_move][1] = y1;
				}
				desk[x1][y1] = desk[x2][y2];
				desk[x2][y2] = temp;
			}
			else {
				delete temp; // Delete the reminded figure
				if (current_figure == '1' || current_figure == '#' || current_figure == '$') { //change moved status and reborn pawns
					if (current_figure == '1' && (y2 == 0 || y2 == 7)) {
						cout << endl << "Choose your fighter: # ? ! & -> ";
						string new_figure;
						getline(cin, new_figure);
						while (new_figure[0] != '#' && new_figure[0] != '?' && new_figure[0] != '!' && new_figure[0] != '&') {
							cout << endl << "Try again -> ";
							getline(cin, new_figure);
						}
						delete desk[x2][y2];
						if (new_figure[0] == '#')
							desk[x2][y2] = new Rook(whose_move);
						else if (new_figure[0] == '?')
							desk[x2][y2] = new Knight(whose_move);
						else if (new_figure[0] == '!')
							desk[x2][y2] = new Bishop(whose_move);
						else if (new_figure[0] == '&')
							desk[x2][y2] = new Queen(whose_move);
						ErrorGenerator::set("THE PAWN WAS REBORN!");
					}
					else
						desk[x2][y2]->change_moved_status_to_true();
				}
				chess_timer.update_time(whose_move); //update time
				whose_move = (whose_move == 'w') ? 'b' : 'w';
			}
		}
		else {
			ErrorGenerator::set("Invalid movement, try again!");
		}
	}
};
