#ifndef AI_H
#define AI_H

#include "HexBoard.h"
#include <vector>

/* AI(artificial intelligence) class represents the computer player
 * of the game. The only public method exposed is calculate_next_move.
 * It is a friend class of HexBoard.
 * The AI is implemented using Monte Carlo simulation*/
class AI {
  public:
    AI(HexBoard& hb)                            //constructor
    : board(hb),
      size(hb.board_size*hb.board_size) {}

    bool calculate_next_move(unsigned short &x, unsigned short &y);

  private:
    HexBoard &board;                            //reference to the actual board
    int size;                                   //size of the board
    vector<int> sb;                             //simulation board

    unsigned short get_base_index(unsigned short x, unsigned short y) const{
        return x*board.board_size + y;
    }

    unsigned short get_base_index(Hex* h) const {
        unsigned short x,y;
        h->get_pos(x,y);
        return get_base_index(x,y);
    }
};

#endif
