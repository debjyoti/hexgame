#include "AI.h"

/* AI is implemented using Monte Carlo simulation */

void AI::refresh_simulation_board() //cant we just capture the prev move? TODO
{
    //std::fill(sb.begin(), sb.end(), '.');      //empty the board
    for(int row=0; row<board_ref.board_size; row++){
        for(int col=0; col<board_ref.board_size; col++){
            sb[row*board_ref.board_size+col] = board_ref.matrix[row][col].get_val();
        }
    }
}

/* finds the optimum next move for the AI. It returns the x and 
 * y value of the move in the parameter (passed by reference) */
int AI::calculate_next_move(unsigned short &x, unsigned short &y)
{
    double win_chance, max_chance = 0.0;
    int best_move=0;
    refresh_simulation_board();                  //copies the hexboard into the simulation board
    for(int i=0; i<size && sb[i]=='.'; i++){   //place ai move in each empty hex
        win_chance = montecarlo_simulate(i, 1000);
        if(win_chance>max_chance){
            max_chance = win_chance;
            best_move = i;
        }
    }
    return best_move;
}

double montecarlo_simulate(int pos, int count)
{
    std::vector<char> b = sb;
    b.at(pos) = board_ref.ai_symbol;
    double chance = 0;
    char move = board_ref.player_symbol;
    std::vector<int> simulation_moves;
    //insert X and O alternately in all empty positions
    //populate the simulation_moves vector
    for(int j=0; j<size && b[j]=='.'; j++){ //every empty hex
        move = (move=='X'? 'O': 'X');  //swap move
        b[j]=move;
        simulation_moves.push_back(j);
    }
    for(int i=0; i<count; i++){    //simulation count
        std::random_shuffle(simulation_moves.begin(); simulation_moves.end());
        move = board_ref.player_symbol;        //player moves
        for(auto const& p: simulation_moves){
            b[p] = move;
            move = (move=='X'? 'O': 'X');  //swap move
        }
        bool ai_won=false, player_won=false;
        who_won(b, ai_won, player_won);
        if(ai_won) ai_win_count++;
        else player_win_count++;
    }
    chance = ai_win_count/player_win_count;
    return chance;
}

void who_won(std::vector<char> board, bool &ai_won, bool &player_won)
{
    //implement the union-find algo on board
    ai_won=true;
}
