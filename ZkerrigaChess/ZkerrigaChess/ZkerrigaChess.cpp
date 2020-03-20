//
// Progect has started at	22:47 
//							19.03.2020
//

#include <iostream>
#include "FigureClasses.h"
#include "DeskClass.h"
using namespace std;

int main() {
	//Create a desk
	ChessDesk *chess_desk = new ChessDesk;
	chess_desk->print_chess_desk();

	//Close program on Enter
	if (getchar() == 13) exit(0);
	return 0;
}
