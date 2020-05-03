#include <algorithm>
#include <iostream>
#include <memory>
#include "graph.h"
#include "minisat/core/Solver.h"


void *APPROX_VC_3(void *gp)
{
    const Graph &graph_input = *(const Graph *)gp;
    //Graph &graph_input = graph;
    VertexVec &C = *new VertexVec();


    unsigned int k = 0;
    unsigned int low = 0;
    unsigned int high = graph_input.adjacency.size();
    bool res;
    k=(high+low)/2;

    while (low<=high)
    {

        std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
        std::vector<std::vector<Minisat::Lit>> nk_matrix(graph_input.adjacency.size());
        for (unsigned int i = 0; i < graph_input.adjacency.size(); i++)
            for (unsigned int j = 0; j < k; j++) {
                Minisat::Lit l = Minisat::mkLit(solver->newVar());
                nk_matrix[i].push_back(l);
            }
        // first condition
        for (unsigned int i = 0; i < k; i++) {
            Minisat::vec<Minisat::Lit> save_literal;
            for (unsigned int j = 0; j < graph_input.adjacency.size(); j++) {
                save_literal.push(nk_matrix[j][i]);
            }
            solver->addClause(save_literal);
        }

// second condition
        for (unsigned int m = 0; m < graph_input.adjacency.size(); m++)
            for (unsigned int p = 0; p < k; p++)
                for (unsigned int q = p + 1; q < k; q++) {
                    solver->addClause(~nk_matrix[m][p], ~nk_matrix[m][q]);
                }
//third condition
        for (unsigned int m = 0; m < k; m++)
            for (unsigned int p = 0; p < graph_input.adjacency.size(); p++)
                for (unsigned int q = p + 1; q < graph_input.adjacency.size(); q++) {
                    solver->addClause(~nk_matrix[p][m], ~nk_matrix[q][m]);
                }


//forth condition
        for(unsigned v1 = 0 ; v1 < graph_input.adjacency.size(); ++v1) {
            for (auto v2 : graph_input.adjacency[v1]) {
                if(v2 < v1) continue;
                Minisat::vec<Minisat::Lit> edge_lit;
                for (unsigned int w = 0; w < k; w++) {
                    edge_lit.push(nk_matrix[v1][w]);
                    edge_lit.push(nk_matrix[v2][w]);
                }

                solver->addClause(edge_lit);
            }
        }
        res = solver->solve();
        if (res )
        {
            C.clear();
            for ( unsigned int i = 0; i < graph_input.adjacency.size(); i++)
                for ( unsigned int j =0; j < k; j++)
                    if ( Minisat::toInt(solver->modelValue(nk_matrix[i][j])) == 0)
                    {
                        C.push_back(i);
                    }

            high = k-1;
        }
        else {
            solver.reset(new Minisat::Solver());
            low =k+1;
        }
        k = (high+low)/2;
    }
    std::sort( C.begin(), C.end(), std::less<int>());
   /* for (unsigned j=0; j < C.size(); j++){
            std::cout<<C[j];
            if(j + 1 != C.size()){
                std::cout<<' ';
            }
        }
        std::cout<<std::endl;
*/
//std::cout<<"CNF-SAT-VC: ";
//cpuNow();
return &C;


}

