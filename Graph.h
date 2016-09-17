#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph{
  protected:
    unsigned short nvertices;         //number of vertices
    unsigned short nedges;            //number of edges
    std::vector<std::vector<bool> >   //edge matrix
                connectivity_matrix;
  public:
    Graph(unsigned short nvertices)  //constructor (inlined)
    : nvertices(nvertices), nedges(0) {
        connectivity_matrix=
            std::vector<std::vector<bool> >(nvertices,
                         std::vector<bool>(nvertices,false));
    }
    bool is_connected(unsigned short x, unsigned short y) const;
    bool add_edge(unsigned short x, unsigned short y);
    void print_connectivity_matrix();
};

#endif
