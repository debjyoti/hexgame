#ifndef HEX_H
#define HEX_H

#include <iostream>   //for osstream
#include <vector>

/* Hex class represents each hexagon in the game */
class Hex{

  private:
    char val;                         //value in the hex. empty-hex stores '.'
    unsigned short xpos;              //x position (which column) of this hex in the board
    unsigned short ypos;              //y position (which row) of this hex in the board
    void update_connections(bool l,   //recurcively update the connection flags
            bool r, bool t, bool b);

  public:
    bool left_connected;              //is this hex connected to the left edge of the board?
    bool right_connected;             //is this hex connected to the right edge of the board?
    bool top_connected;               //is this hex connected to the top edge of the board?
    bool bottom_connected;            //is this hex connected to the bottom edge of the board?
    std::vector<Hex*> neighbors;      //list of neighbors (min2, max 6)
    std::vector<Hex*> connections;    //list of neighbors who have same value

    Hex(unsigned short,unsigned short,
        bool, bool, bool, bool);      //constructor

    bool is_empty() const {           //is the hex empty?
        return (val=='.');
    }

    char get_val() const {            //returns the val (will return '.' if empty)
        return val;
    }

    void get_pos(unsigned short &x,
        unsigned short &y) const {    //sets x y position params
        x = xpos;
        y = ypos;
    }

    bool set_val(char v);                  //sets val, and updates connections

    bool is_vertical_connected() const {   //if true, AI wins
        return (top_connected &&
                bottom_connected);
    }

    bool is_horizontal_connected() const { //if true, player wins
        return (left_connected &&
                right_connected);
    }

    void add_neighbor(Hex* h) {            //used in the HexBoard constructor
        neighbors.push_back(h);
    }

    friend std::ostream& operator<<        //overloading << for printing
        (std::ostream &os, const Hex &h);
};

#endif
