#include <algorithm>   //random shuffle
#include <cassert>
#include "AI.h"
#include "SetUnion.h"

//constructor
AI::AI(HexBoard& hb)
    : board_ref(hb),
      size(hb.board_size*hb.board_size)
{
    sb = std::vector<char>(size, '.');         //empty board

    //populate the neighbors matrix
    neighbors = std::vector<std::vector<int>>(size);
    for(int row=0; row<hb.board_size; row++){
        for(int col=0; col<hb.board_size; col++){
            int pos = get_base_index(row, col);
            if(col<hb.board_size-1){                                       //not right edge
                neighbors.at(pos).push_back(pos+1);                        //hex to the right
                if(row>0){
                    neighbors.at(pos).push_back(                           //hex to the top right
                        get_base_index(row-1, col+1));
                }
            }
            if(row<hb.board_size-1){                                          //not the bottom edge
                neighbors.at(pos).push_back(
                        get_base_index(row+1, col));                   //hex to the bottom
            }
            /*  not adding these 2 neighbors to reduce redundancy
            if(col>0){                                                     //not the left edge
                hex_at(row,col)->add_neighbor(hex_at(row,col-1));          //hex to the left
                if(row<board_size-1){
                    hex_at(row,col)->add_neighbor(hex_at(row+1,col-1));    //hex to the bottom left    
                }
            }
            if(row>0){                                                     //not the top edge    
                hex_at(row,col)->add_neighbor(hex_at(row-1,col));          //hex to the top    
            }
            */
        }
    }
}

/* Finds the optimum next move for the AI. It returns the x and 
 * y value of the move in the parameter (passed by reference)
 * It is implemented using Monte Carlo simulation */
void AI::calculate_next_move(unsigned short &x, unsigned short &y,
                     unsigned short prev_x, unsigned short prev_y)
{
    double win_chance, max_chance = 0.0;
    int best_move=0;
    //refresh_simulation_board();
    update_simulation_board(get_base_index(prev_x, prev_y),
                                board_ref.player_symbol);
    for(int i=0; i<size; i++){   //place ai move in each empty hex
        if(sb[i]!='.') continue;
        win_chance = montecarlo_simulate(i, 1000);
        if(win_chance>max_chance){
            max_chance = win_chance;
            best_move = i;
        }
    }
    get_x_y(best_move, x, y);
    update_simulation_board(get_base_index(x, y),
                                        board_ref.ai_symbol);
    print_sim_board();
}

double AI::montecarlo_simulate(int pos, int count)
{
    std::vector<char> b = sb;           //copy of simulation board
    b.at(pos) = board_ref.ai_symbol;    //place ai_move at pos

    std::vector<int> simulation_moves;  //all the simulation moves (even-pl, odd-AI)
    //populate the simulation_moves vector with all empty positions
    for(int j=0; j<size; j++){
        if(b[j]=='.'){ //every empty hex
            simulation_moves.push_back(j);
        }
    }

    double chance = 0;                  //stores the probability of win
    char move_sym = board_ref.player_symbol;//next move symbol
    int win_count=0;                    //number of wins

    for(int i=0; i<count; i++){         //simulation count
        //randomly shuffle the simulation vector
        std::random_shuffle(simulation_moves.begin(), simulation_moves.end());
        for(auto const& pos: simulation_moves){  //fill the entire board
            b[pos] = move_sym;                   //make simulation move
            move_sym = (move_sym=='X'? 'O': 'X');//swap move symbol for next move
        }
        if(ai_won(b)) win_count++;                //check if ai won
    }
    chance = (double)win_count/count;
    std::cout << "DEBUG: chance = "<< chance << std::endl;
    return chance;
}

bool AI::ai_won(std::vector<char> &board)
{
    SetUnion s(size+2);  //last 2 for top and bottom
    int top_connect = size;  //2nd last field (note that it starts from 0
    int bottom_connect = size+1;  //last field
    for(int i=0; i<size; i++){
        char c = board.at(i);
        assert(c!='.'); //board should not have empty hex at this stage TODO: remove
        if(c=='O'){
            if(i<board_ref.board_size)         //this hex is on the top edge
                s.join(i,top_connect);         //join this hex to top_connect
            else if(i>=board_ref.board_size*(board_ref.board_size-1)) //this hex is on bottom edge
                s.join(i, bottom_connect);
            for(int n: neighbors.at(i)){       //loop through the neighbors
                if(board[n]==c){               //neighbor has same value
                    s.join(i,n);               //join this set with neighbors
                }
            }
        }
    }
    if(s.connected(top_connect, bottom_connect))
        return true;
    else
        return false;
}

/*
void AI::refresh_simulation_board() //cant we just capture the prev move? TODO
{
    //std::fill(sb.begin(), sb.end(), '.');      //empty the board
    for(int row=0; row<board_ref.board_size; row++){
        for(int col=0; col<board_ref.board_size; col++){
            sb[row*board_ref.board_size+col] = board_ref.matrix[row][col].get_val();
        }
    }
}
*/
