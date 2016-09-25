#include <stdexcept>  //for runtime_error
#include <iomanip>    //for setw
#include "HexBoard.h"
#include "AI.h"

/* HexBoard constructor */
HexBoard::HexBoard(unsigned short board_size,
    char player_symbol, char ai_symbol)
    : board_size(board_size),
      player_symbol(player_symbol),
      ai_symbol(ai_symbol)
{
    bool left_connected, right_connected, 
         top_connected, bottom_connected;
    empty_hex_count=board_size*board_size;
    /* create all the hex */
    for(int row=0; row<board_size; row++){           //for each row, create vector of Hex (temp)
        std::vector<Hex> temp;
        if(row==0) top_connected=true;               //top row is top_connected from start
        else top_connected=false;
        if(row==board_size-1) bottom_connected=true; //bottom row is bottm_connected from start
        else bottom_connected=false;
        for(int col=0; col<board_size; col++){       //for each column in the row, create Hex and add to temp
           if(col==0) left_connected=true;           //left column is left connected from start
           else left_connected=false;
           if(col==board_size-1) right_connected=true;//right column is right connected from start
           else right_connected=false;
           temp.emplace_back(row, col,left_connected,//create the Hex and add to temp
            right_connected, top_connected, bottom_connected);
        }
        matrix.push_back(temp);                      //add the row(temp vector) to the matrix
    }
    //set up the neighbours (to be done only after matrix is completely created)
    for(int row=0; row<board_size; row++){
        for(int col=0; col<board_size; col++){
            if(col<board_size-1){                                          //not right edge
                hex_at(row,col)->add_neighbor(hex_at(row,col+1));          //hex to the right
                if(row>0){
                    hex_at(row,col)->add_neighbor(hex_at(row-1,col+1));    //hex to the top right
                }
            }
            if(row<board_size-1){                                          //not the bottom edge
                hex_at(row,col)->add_neighbor(hex_at(row+1,col));          //hex to the bottom
            }
            if(col>0){                                                     //not the left edge
                hex_at(row,col)->add_neighbor(hex_at(row,col-1));          //hex to the left
                if(row<board_size-1){
                    hex_at(row,col)->add_neighbor(hex_at(row+1,col-1));    //hex to the bottom left    
                }
            }
            if(row>0){                                                     //not the top edge    
                hex_at(row,col)->add_neighbor(hex_at(row-1,col));          //hex to the top    
            }
        }
    }
}

/* prompts player to input his move. Checks if move is valid.
 * It also prints the board before prompting user */
bool HexBoard::accept_user_input(unsigned short &x, unsigned short &y)
{
    print();
    while(1){
        std::cout << "your turn (x y):";
        std::cin >> x >> y;
        --x; --y;            //decrement to make it start from 0 instead of 1
        try{
            if(hex_at(x,y)->is_empty()){  //might throw out-of-range error
                break;
            } else {
                std::cout << "(" <<x+1<<","<<y+1<<") is already occupied.\n";
            }
        }
        catch(const std::out_of_range& e){
            std::cout << "Input out of range. Please insert values between"
                " 1 and "<< board_size << ". e.g: 1 2 ("<< e.what() <<")"<< std::endl;
        }
    }
    return true;
}

/* Writes the hexboard to ostream os in ascii-art :)
 * os is cout by default (refer .h file) */
 //TODO: create GUI
void HexBoard::print(std::ostream &os) const
{
    int space_count =0;                           //how many spaces to pad at left
    for(unsigned short i=1; i<=board_size; i++)   //print the column index in header
        std::cout << std::setw(4) << std::left << i ;
    std::cout << std::endl;
    for(unsigned short row=0; row<board_size;     //loop each row in the board
            row++){
        for(unsigned short col=0; col<board_size; //loop each col in the board
                col++){
            os << matrix[row][col];               //print the hex
            if(col<board_size-1){                 //print " - " between hexes
                os << " - ";
            }
        }
        std::cout << " " << row+1 << " ";         //print row-num for better gameplay
        os << std::endl;
        if(row < board_size-1){                   //print " \ / \ / ..." between rows
            ++space_count;                        //slant it towards right
            os << std::string(space_count, ' ');  //prints space_count spaces
            for(int i=0; i<board_size-1; i++){    //print \ / between columns
                os << "\\ / " ;                   //double backslash for escaping 
            }
            os << "\\";                           //print \ for last column
            os << std::endl;
            ++space_count;
            os << std::string(space_count, ' ');  //print spaces padding in next row
        }
    }
}

/* overloaded operator << for printing. invokes print method */
std::ostream& operator<< (std::ostream &os, const HexBoard &hb)
{
    hb.print(os);
    return os;
}


/* plays the game till a player wins or the game is draw.
 * returns false for draw, true for win
 * Prof says that it can never end in draw though.*/
bool HexBoard::play()
{
    unsigned short user_x, user_y, my_x, my_y;
    AI ai(*this);
    std::cout << "How To Play:\n You need to connect the board from left to right.\n";
    while(1){
        if(empty_hex_count==0) return false;           //if count becomes 0, no more hex left. Game Draw.
        accept_user_input(user_x, user_y);             //get player's move
        hex_at(user_x,user_y)->set_val(player_symbol); //make the move om the board
        empty_hex_count--;                             //decrement hex count
        if(hex_at(user_x,user_y)->is_horizontal_connected()){   //check exit condition
            std::cout << "Player Won!!!\n";
            return true;
        }
        if(empty_hex_count==0) return false;
        ai.calculate_next_move(my_x, my_y, user_x,     //get ai move
                                           user_y);
        hex_at(my_x,my_y)->set_val(ai_symbol);         //make the move on the board
        empty_hex_count--;                                //decrement the hex count
        if(hex_at(my_x,my_y)->is_vertical_connected()){   //check exit condition
            std::cout << "AI won!!!\n";
            return true;
        }
    }
}
