
#include <algorithm>
#include <iostream>
#include <memory>
#include "graph.h"

void *APPROX_VC_2(void *input) // ? random pick can cause the more complicated running time maybe we can add a vector of edges
{
    Graph g = *(const Graph *)input;
     // the value of input is the same as that of gp, but they are different variables
    VertexVec &C = * new VertexVec();// new followed by type name; () means call the constructor function. it is put into the heap.

    while (g.num_edges > 0) {
        unsigned v1_pick = 0, v2_pick;
        {
            size_t m;
           // m = rand() % (g.num_edges*2); // change this part to another easier method.

 	m = rand() % (g.num_edges * 2);
	while (g.adjacency[v1_pick].size() <= m) {
                m -= g.adjacency[v1_pick].size();
                ++v1_pick;
            }
            v2_pick = g.adjacency[v1_pick].front();
        }

        C.push_back(v1_pick);
        C.push_back(v2_pick);
        g.clear( v1_pick );
        g.clear( v2_pick );
        /*
        Edges.erase(Edges.begin()+m);
        v1_pick = edge_pick.v1;
        v2_pick = edge_pick.v2;

        for (auto it=Edges.begin(); it != Edges.end(); )
        {
            auto &i=*it;
            if ( i.v1 == edge_pick.v1 || i.v1 == edge_pick.v2 )
                Edges.erase(it);
            else if ( i.v2 == edge_pick.v1 || i.v2 == edge_pick.v2 )
                Edges.erase(it);
            else
                it++;
        }
        */

    }
    std::sort( C.begin(), C.end(), std::less<int>());
//std::cout<<"APPROX-VC-2: ";
//cpuNow();
 //   cout<<endl;

return &C;
}
