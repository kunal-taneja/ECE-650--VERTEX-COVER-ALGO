#include <iostream>
#include <sstream>
#include "graph.h"
#include "minvc.h"

using std::toupper;

int main(int argc, char **argv)
{
    Graph &graph_input = *new Graph();
    char user_input;
    string line;
    unsigned int v_num = 0;
    string edg_input;
    char pre_input = ' ';

    while (getline(cin, line)) {
        istringstream input(line);
        while (input >> user_input) {
            user_input=(toupper(user_input));
	    try
	    {
            switch (user_input)
            {
                case 'V' :
                    if (pre_input == 'V')
                    {
                        cerr << "Error: V must be followed by E only.\n";
                        break;
                    }
                    else
                    {
                        input >> v_num;

			if(v_num <= 0)
				{
					throw " Invalid number of vertices ";
				}	
				
                        graph_input.init(v_num);
                        pre_input = 'V';

                        break;
			
			//else
			//throw "Invalid number of vertices ";

                    }


                case 'E' :
                {
                    unsigned int flagE = 0;
                    if ( pre_input == 'E')
                    {
                        cerr << "Error: V and E always occur together.\n ";
                        break;
                    }
                    else
                    {
                        input >> edg_input;
                        istringstream input_edg(edg_input);
                        char edg_char;
                        unsigned int elem_v = 0;
                        unsigned int v1;
                        unsigned int v2;

                        input_edg >> edg_char;

                        while (edg_char != '}') {
                            input_edg >> edg_char;
                            if (edg_char == '}')
                            {
                                flagE = 1;
                                break;
                            }
                            else
                            {

                                input_edg >> elem_v;
                                v1 = elem_v;
                                input_edg >> edg_char;

                                input_edg >> elem_v;
                                v2 = elem_v;

                                input_edg >> edg_char;
                                input_edg >> edg_char;
                                if (v1 >= v_num || v2 >= v_num)
                                {
                                    cerr << "Error: Vertex out of range.\n";
				    graph_input.adjacency.clear();
                                    break;
                                }
                                graph_input.add({v1,v2});
  

                            }

                        }
                        if(flagE == 1)
                        {
                            pre_input = 'E';
                            break;
                        }
			Min_Vc(graph_input);
                        pre_input = 'E';
                        break;

                    }
                }

            }
}
		catch (const char* err) {
                cerr << "Error:" << err << endl;
		}
        }

    }
return 0;
}
