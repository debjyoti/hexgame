#include <algorithm>   //random shuffle
#include "AI.h"

/* AI is implemented using Monte Carlo simulation */

/* finds the optimum next move for the AI. It returns the x and 
 * y value of the move in the parameter (passed by reference) */
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

bool AI::ai_won(std::vector<char> board)
{
    //implement the union-find algo on board : TODO
    return true;
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
