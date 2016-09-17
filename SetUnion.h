#ifndef SETUNION_H
#define SETUNION_H

#include <vector>
#include <numeric> //for iota

/* SetUnion class implements the union-find algorithm, which is 
 * used to check if simulation board is connected.
 * Reference: Section6.1.3 - Steven Skiena Algo Book */

class SetUnion {

  public:
    //constructor
    SetUnion(int count): n(count) {
        parent = std::vector<int>(n);                 //parent = self
        std::iota(parent.begin(), parent.end(), 0);   //set 0..count
        size = std::vector<int>(n,1);                 //size = 1 for all
    }

    bool join(int s1, int s2);                        //join set s1 and s2

    bool connected(int s1, int s2);                   //is s1 and s2 connected?

  private:
    int n;                     //number of elements in Set
    std::vector<int> parent;   //parent element
    std::vector<int> size;     //number of elements in subtree

    int root(int x);           //recursively finds root parent
};

#endif
