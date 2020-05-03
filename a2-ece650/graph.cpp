#include "graph.h"
#include "iostream"


void graph::clear_graph(){

    for (auto &i:adjaceny_matrix)
        for(auto &j : i)
            j=INDEFINITE;
    path.clear();
}

void graph::init_graph(unsigned int v_num)
{
    adjaceny_matrix.clear();
    path.clear();
    gv_num = v_num;
    adjaceny_matrix.resize(gv_num);
    for (auto &i:adjaceny_matrix)
    {
        i.resize(gv_num,INDEFINITE);
    }
}


void graph::link(unsigned int v1, unsigned int v2)
{
    if (v1 >= adjaceny_matrix.size()|| v2 >= adjaceny_matrix[0].size())
        throw " Vertex out of range";
    else  if (v1 == v2)
	throw " Self loops not allowed";
    else
    {
        adjaceny_matrix[v1][v2] = 1;
        adjaceny_matrix[v2][v1] = 1;
    }
}


void graph::shortest_path(unsigned int Source, unsigned int Destination) {
    if (Source >= gv_num || Destination >= gv_num)
    {
        throw " Vertex out of range";
    }
   // else if (Source == Destination)
//	throw " No path specified for self loops";

    unsigned int new_dist;
    unsigned int flag[gv_num];

    unsigned int dist[gv_num];
    path.clear();


    for (unsigned int i = 0; i < gv_num; i++) {
        flag[i] = 0;

        dist[i] = adjaceny_matrix[Source][i];
    }


    flag[Source] = 1;
    dist[Source] = 0;

    for (unsigned int i = 1; i < gv_num; i++) {

        unsigned int min = INDEFINITE;
        unsigned int k = 0;
        for (unsigned int j = 0; j < gv_num; j++) {
            if (flag[j] == 0 && dist[j] < min) {
                min = dist[j];
                k = j;
            }
        }

        flag[k] = 1;


        for (unsigned int j = 0; j < gv_num; j++) {
            new_dist = (adjaceny_matrix[k][j] == INDEFINITE ? INDEFINITE : (min + adjaceny_matrix[k][j]));
            if (flag[j] == 0 && (new_dist < dist[j])) {
                dist[j] = new_dist;

            }
        }
    }


    if (dist[Destination] == INDEFINITE)
    {
        throw " No path exists between these vertices";
    }

    unsigned int vertex = Destination;
    while (dist[vertex] > 0) {
        path.push_back(vertex);
        for(size_t i = 0; i<gv_num; ++i)
        {
            if(adjaceny_matrix[vertex][i] < INDEFINITE &&
               dist[i] + adjaceny_matrix[vertex][i] == dist[vertex])
            {
                vertex = i;
                break;
            }
        }
    }
    path.push_back(vertex);


    for (auto mk = path.rbegin(); mk != path.rend(); mk++)
    {
        std::cout << *mk;
        if (mk != path.rend() - 1) {
            std::cout << "-";
        } else
            std::cout << "\n";
    }
}

