#include <iostream>
#include <stdexcept>
#include "Graph.h"

/* returns true of vertex x is connected to vertex y */
bool Graph::is_connected(unsigned short x, unsigned short y) const { 
    return connectivity_matrix.at(x).at(y); 
}

/* adds adge between vertex x and vertex y */
bool Graph::add_edge(unsigned short x, unsigned short y){
    try {
        if(x==y) return false;                           //no self-loop
        if(connectivity_matrix.at(x).at(y)) return false;//already connected
        connectivity_matrix.at(x).at(y) = connectivity_matrix.at(y).at(x) = true;
        nedges+=2;
        return true;
    }
    catch(const std::out_of_range &e){
        return false;
    }
}

/* displaying the graph to ostream*/
void Graph::print_connectivity_matrix(){
    std::cout << "Graph with "<<nvertices<< " vertices:" << std::endl;
    for(int i=0; i<nvertices; i++){
        for(int j=0; j<nvertices; j++){
            std::cout << " " << connectivity_matrix[i][j];
        }
        std::cout << std::endl;
    }
}
