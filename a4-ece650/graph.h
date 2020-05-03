#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <set>
#include <list>

struct Edge{
    unsigned v1,v2;
};

typedef std::vector<unsigned> VertexVec;
typedef std::list<unsigned > VertexList;
typedef std::vector<VertexList> AdjList;

struct Graph{
    std::size_t num_edges;
    AdjList adjacency;

    void init(unsigned num_vertices);
    void add(Edge e);
    void clear(unsigned v);
};

#endif
