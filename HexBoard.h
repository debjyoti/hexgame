#ifndef HEXBOARD_H
#define HEXBOARD_H

#include <iostream>  //for ostream
#include <vector>
#include "Hex.h"
class AI;        //forward declaration of class AI required to make it friend

/* HexBoard represents the board where the game is played. */
class HexBoard{

  private:
    std::vector<std::vector<Hex> > matrix;            //Hex Matrix
    unsigned short board_size;                        //if 7x7 board, board_size=7
    unsigned int empty_hex_count;                     //on 7x7 board, count=49 at start.
    char player_symbol;                               //'X'
    char ai_symbol;                                   //'0'

  public:
    HexBoard(unsigned short board_size,               //constructor
          char player_symbol, char ai_symbol);

    bool accept_user_input(                           //prints the hex, and accepts player's move
              unsigned short &x, unsigned short &y);

    bool play();                                      //plays the game till a player wins or draws

    Hex* hex_at(unsigned short x, unsigned short y) { //returns Hex* at x,y position in the board
        return &(matrix.at(x).at(y));                 //throws out-of-range exception
    }

    void print(std::ostream &os=std::cout) const;     //prints the board
    friend std::ostream& operator<<(std::ostream &os, //overloading << for cout
        const HexBoard &hb);
    friend class AI;
};

#endif
