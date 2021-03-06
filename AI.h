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
    AI(HexBoard& hb);                           //constructor

    void calculate_next_move(unsigned short &x, unsigned short &y,
                     unsigned short prev_x, unsigned short prev_y);

  private:
    HexBoard &board_ref;                        //reference to the actual board
    int size;                                   //size of the board
    std::vector<char> sb;                       //simulation board
    std::vector< std::vector<int> > neighbors;  //neighbors

    void get_x_y(int i, unsigned short &x, unsigned short &y) const {
        x=i/board_ref.board_size;
        y=i%board_ref.board_size;
    }

    void update_simulation_board(int x, char val){
        sb[x]=val;
    }

    unsigned short get_base_index(unsigned short x, unsigned short y) const{
        return x*board_ref.board_size + y;
    }

    unsigned short get_base_index(Hex* h) const {
        unsigned short x,y;
        h->get_pos(x,y);
        return get_base_index(x,y);
    }

    double montecarlo_simulate(int pos, int count);

    bool ai_won(std::vector<char> &board);
    
    void print_sim_board() {
        std::cout << "DEBUG: sim board = ";
        for(auto i: sb)
            std::cout << i << " ";
        std::cout << std::endl;
    }
};

#endif
