#include <iostream>
#include "HexBoard.h"

int main() {
    srand (time(NULL));                      //just for testing
#ifdef DEBUG
    const unsigned short board_size = 5;
#else
    const unsigned short board_size = 11;
#endif
	HexBoard board(board_size,'X','O');
	//std::cout << board << std::endl;
	board.play();
	std::cout << std::endl << board << std::endl;
	return 0;
}
