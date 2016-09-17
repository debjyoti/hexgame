#include "Hex.h"

//constructor
Hex::Hex(unsigned short x, unsigned short y, bool l, bool r, bool t, bool b)
     : val('.'), xpos(x), ypos(y), left_connected(l),
        right_connected(r), top_connected(t), bottom_connected(b) {}

/* Sets the val
   and updates all connections (booleans and connections vector) */
bool Hex::set_val(char v) {
    val = v;
    //loop through neighbors to find connections
    for(Hex* n: neighbors){
        if(n->get_val()==v){                               //yay! same value
            if(n->left_connected)   left_connected=true;   //upgrade the connected flags as per neighbors
            if(n->right_connected)  right_connected=true;
            if(n->top_connected)    top_connected=true;
            if(n->bottom_connected) bottom_connected=true;
		    connections.push_back(n);                      //add in the connections vector
		    n->connections.push_back(this);                //vice versa
        }
    }
    /*update connections
    e.g. if left neighbor was left-connected, and top neighbor was top_connected
         top neighnor will become left_connected and left will become top_connected */
    for(Hex* c: connections){
        c->update_connections(left_connected,right_connected,  //recursively updates all connections
                              top_connected,bottom_connected);
    }
    return true;
}

/* Updates connection flags and (private method)
   recursively updates all connections (in vector) */
void Hex::update_connections(bool l, bool r, bool t, bool b){
    bool change_con = false;    //tracks if any change is done.. if not, no need of recursion
    if(l && !left_connected){   //l is true (left connected), and this Hex is not already left connected
        left_connected=true;
        change_con = true;
    }
    if(r && !right_connected){  //r is true (right connected), and this Hex is not already right connected
        right_connected=true;
        change_con = true;
    }
    if(t && !top_connected){    //t is true (top connected), and this Hex is not already top connected
        top_connected=true;
        change_con = true;
    }
    if(b && !bottom_connected){ //b is true (bottom connected), and this Hex is not already bottom connected
        bottom_connected=true;
        change_con = true;
    }
    if(change_con){             //either one of the above changes occured. so propagate the change 
        for(Hex* c: connections){   //to all connections
            c->update_connections(left_connected,right_connected,top_connected,bottom_connected);
        }
    }
}

/* Overloaded << operator for printing the Hex - prints the val only */
std::ostream& operator<< (std::ostream &os, const Hex &h)
{
    os << h.val;
    return os;
}
