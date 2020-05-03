#include "graph.h"


void Graph::init(unsigned n){
    adjacency.clear();
    num_edges = 0;
    adjacency.resize(n,{});
}

void Graph::add(Edge e) {
    auto &l1 = adjacency[e.v1];
    auto &l2 = adjacency[e.v2];
    l1.push_back(e.v2);
    l2.push_back(e.v1);
    num_edges ++;
}
