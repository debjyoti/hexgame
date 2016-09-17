#include "SetUnion.h"

//joins two sets s1 and s2
//returns false if already joined, else returns true
bool SetUnion::join(int s1, int s2)
{
    int r1, r2;               //roots of sets
    r1 = root(s1);
    r2 = root(s2);

    if(r1==r2) return false;    //already connected
    
    if(size[r1] >= size[r2]) {   //add smaller set to bigger
        size[r1] = size[r1]+size[r2];
        parent[r2] = r1;
    } else {
        size[r2] = size[r2]+size[r1];
        parent[r1] = r2;
    }
}

//are set s1 and s2 connected?
bool SetUnion::connected(int s1, int s2)
{
    return (root(s1)==root(s2));
}

//recursively find the root of x
int SetUnion::root(int x)
{
    if(parent[x]==x)
        return x;
    else
        return(root(parent[x]));
}
