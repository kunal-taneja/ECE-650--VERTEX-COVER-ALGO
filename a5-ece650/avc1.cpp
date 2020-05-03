
#include <algorithm>
#include <iostream>
#include <memory>
#include "graph.h"

void *APPROX_VC_1(void *input)
{
    Graph g = *(const Graph *)input; //static cast; type convertion; pointer is 64 btis; for compiler, it knows that input points to a graph type pbject, which is the only difference between those two pointers.
    VertexVec &C = *new VertexVec(); //after "new", output is a address pointing to VertexVec type object


    while(g.num_edges > 0){
        auto v = std::max_element(
                g.adjacency.begin(),g.adjacency.end(),
                [](VertexList &l1, VertexList &l2)->bool{ return l1.size()<l2.size(); } //?
        );
        unsigned i = (unsigned)(v-g.adjacency.begin()); //get the highest degree vertex
        C.push_back(i);
        g.clear(i);
    }
    std::sort( C.begin(), C.end(), std::less<int>());
    //std::cout<<"APPROX-VC-1: ";
  //  cpuNow();
   // cout<<endl;
    return &C;

}

