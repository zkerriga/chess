//
// Progect has started at	10:05 
//							20.03.2020
//

//pawn = пешка
//knight = конь
//rook = ладья
//bisop = слон
//queen = ферзь
//king = король

#pragma once
#include <iostream>

#include "ErrorGenerator.h"
using namespace std;

class Figure {
private:
	char color;

public:
	//Constructor:
	Figure() {
		color = 'w';
	}
	Figure(char c) {
		color = c;
	}
	virtual ~Figure() {
		//cout << "[+] Figure dead!" << endl;
	}
	char get_figure_color() {
		return color;
	}
	void change_figure_color(char c) {
		color = c;
	}
	virtual char get_figure_sign() {
		return ' ';
	}
	virtual bool сan_a_figure_make_a_move(int x1, int y1, int x2, int y2, Figure *desk[8][8]) {
		return false;
	}
	virtual void change_moved_status_to_true() {}
};

class Rook : public Figure {
public:
	Rook(char c) {
		change_figure_color(c);
	}
	~Rook() {
		ErrorGenerator::set("Rook dead!");
	}
	virtual char get_figure_sign() {
		return '#';
	}
	virtual bool сan_a_figure_make_a_move(int x1, int y1, int x2, int y2, Figure *desk[8][8]) { //take a valid x,y!!!
		if (x1 == x2) {
			int delta = (y2 > y1) ? 1 : -1;
			for (int y = y1 + delta; y != y2; y += delta) {
				if (desk[x1][y]->get_figure_sign() != ' ') {
					return false;
				}
			}
			return true;
		}
		else if (y1 == y2) {
			int delta = (x2 > x1) ? 1 : -1;
			for (int x = x1 + delta; x != x2; x += delta) {
				if (desk[x][y1]->get_figure_sign() != ' ') {
					return false;
				}
			}
			return true;
		}
		else
			return false;
	}
};

class Knight : public Figure {
public:
	Knight(char c) {
		change_figure_color(c);
	}
	~Knight() {
		ErrorGenerator::set("Knight dead!");
		//cout << "[+] Knight dead!" << endl;
	}
	virtual char get_figure_sign() {
		return '?';
	}
	virtual bool сan_a_figure_make_a_move(int x1, int y1, int x2, int y2, Figure *desk[8][8]) { //take a valid x,y!!!
		if ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) == 5)
			return true;
		else
			return false;
	}
};

class Bishop : public Figure {
public:
	Bishop(char c) {
		change_figure_color(c);
	}
	~Bishop() {
		ErrorGenerator::set("Bishop dead!");
		//cout << "[+] Bishop dead!" << endl;
	}
	virtual char get_figure_sign() {
		return '!';
	}
	virtual bool сan_a_figure_make_a_move(int x1, int y1, int x2, int y2, Figure *desk[8][8]) { //take a valid x,y!!!
		if (x2 - x1 == y2 - y1 || x2 - x1 == y1 - y2) {
			int dy = (y2 > y1) ? 1 : -1;
			int dx = (x2 > x1) ? 1 : -1;
			int steps = (x2 > x1) ? x2 - x1 : x1 - x2;
			for (int i = 1; i < steps; i++) {
				if (desk[x1 + i * dx][y1 + i * dy]->get_figure_sign() != ' ')
					return false;
			}
			return true;
		}
		else
			return false;
	}
};

class Queen : public Figure {
public:
	Queen(char c) {
		change_figure_color(c);
	}
	~Queen() {
		ErrorGenerator::set("Queen dead!");
		//cout << "[+] Queen dead!" << endl;
	}
	virtual char get_figure_sign() {
		return '&';
	}
	virtual bool сan_a_figure_make_a_move(int x1, int y1, int x2, int y2, Figure *desk[8][8]) { //take a valid x,y!!!
		if (x2 - x1 == y2 - y1 || x2 - x1 == y1 - y2) {
			int dy = (y2 > y1) ? 1 : -1;
			int dx = (x2 > x1) ? 1 : -1;
			int steps = (x2 > x1) ? x2 - x1 : x1 - x2;
			for (int i = 1; i < steps; i++) {
				if (desk[x1 + i * dx][y1 + i * dy]->get_figure_sign() != ' ')
					return false;
			}
			return true;
		}
		else if (x1 == x2) {
			int delta = (y2 > y1) ? 1 : -1;
			for (int y = y1 + delta; y != y2; y += delta) {
				if (desk[x1][y]->get_figure_sign() != ' ') {
					return false;
				}
			}
			return true;
		}
		else if (y1 == y2) {
			int delta = (x2 > x1) ? 1 : -1;
			for (int x = x1 + delta; x != x2; x += delta) {
				if (desk[x][y1]->get_figure_sign() != ' ') {
					return false;
				}
			}
			return true;
		}
		else
			return false;
	}
};

class King : public Figure {
public:
	King(char c) {
		change_figure_color(c);
	}
	~King() {
		ErrorGenerator::set("What?! You couldn't do that!!!");
		//cout << "[+] King dead!" << endl;
	}
	virtual char get_figure_sign() {
		return '$';
	}
	virtual bool сan_a_figure_make_a_move(int x1, int y1, int x2, int y2, Figure *desk[8][8]) { //take a valid x,y!!!
		if ((x2 - x1 >= -1 && x2 - x1 <= 1) && (y2 - y1 >= -1 && y2 - y1 <= 1))
			return true;
		else
			return false;
	}
};

class Pawn : public Figure {
private:
	bool moved;
public:
	Pawn(char c) {
		change_figure_color(c);
		moved = false;
	}
	~Pawn() {
		ErrorGenerator::set("Pawn dead!");
		//cout << "[+] Pawn dead!" << endl;
	}
	virtual void change_moved_status_to_true() {
		moved = true;
	}
	virtual char get_figure_sign() {
		return '1';
	}
	virtual bool сan_a_figure_make_a_move(int x1, int y1, int x2, int y2, Figure *desk[8][8]) { //take a valid x,y!!!
		int delta = (get_figure_color() == 'w') ? -1 : 1;
		if (x1 == x2 && y2 == y1 + delta && desk[x1][y2]->get_figure_sign() == ' ')
			return true;
		else if (!moved && x1 == x2 && y2 == y1 + delta * 2 && desk[x1][y2]->get_figure_sign() == ' ' && desk[x1][y1 + delta]->get_figure_sign() == ' ')
			return true;
		else if ((x2 - x1 == -1 || x2 - x1 == 1) && y2 == y1 + delta && desk[x2][y2]->get_figure_sign() != ' ')
			return true;
		else
			return false;

	}
};

class EmptyFigure : public Figure {
public:
	EmptyFigure() {
		change_figure_color(' ');
	}
	~EmptyFigure() {}
};