#include <vector>
using namespace std;
class graph {


#define INDEFINITE   (~(0x1<<31))
private:
    unsigned int gv_num;
    vector<vector<unsigned int>> adjaceny_matrix;
    vector<unsigned> path;

public:
    void clear_graph();
    void init_graph(unsigned int v_num);
    void link(unsigned int v1, unsigned int v2);
    void shortest_path(unsigned int Source, unsigned int Destination);
};
