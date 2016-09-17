#include "AI.h"

/* AI is implemented using Monte Carlo simulation */

/* finds the optimum next move for the AI. It returns the x and 
 * y value of the move in the parameter (passed by reference) */
bool AI::calculate_next_move(unsigned short &x, unsigned short &y)
{
    double win_chance, max_chance = 0;
    int max_move;
    refresh_simulation_board();                  //copies the hexboard into the simulation board
    for(int i=0; i<size && sb[i]!=EMPTY; i++){   //place ai move in each empty hex
        sb[i]=AI;
        win_chance = montecarlo_simulate(1000);
        if(win_chance>max_chance){
            max_chance = win_chance;
            max_move = i;
        }
    }
    return true;
}

double montecarlo_simulate(int n)
{
    double chance = 0;
    vector<int> choices;
    return chance;
}
