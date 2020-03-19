//
// Progect has started at	22:47 
//							19.03.2020
//

#include <iostream>
//#include <vector>
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
	~Figure() {
		cout << "Figure Memory dead!";
	}
	void figure_say_hello() {
		cout << "I'm a ";
		if (color == 'w') {
			cout << "white";
		}
		else {
			cout << "black";
		}
		cout << " figure! Hello!";
	}
};

class ChessDesk {
private:
	char whose_move; //'w' or 'b' equal 'white' or 'black'
	Figure *desk[8][8];

public:
	//Constructor:
	ChessDesk() {
		whose_move = 'w';
		Figure *rook = new Figure('b'); // rook = ladya
		desk[0][7] = rook;
		//Figure *knight = new Figure('w'); //knight = horse
		//desk[1][0] = *knight;
	}
	~ChessDesk() {
		cout << "Desk Memory dead!";
	}

	void print_chess_desk() {
		//Print whose move
		if (whose_move == 'w') {
			cout << "White's move!" << endl;
		}
		else {
			cout << "Black's move!" << endl;
		}
		//print desk
		desk[0][7]->figure_say_hello();
	}
};

int main() {
    cout << "[+] Start program" << endl;
	//Create a desk
	ChessDesk *chess_desk = new ChessDesk;
	chess_desk->print_chess_desk();
	//Figure *rook = new Figure('b');
	//rook->figure_say_hello();

	//Close program on Enter
	if (getchar() == 13) exit(0);
	return 0;
}
