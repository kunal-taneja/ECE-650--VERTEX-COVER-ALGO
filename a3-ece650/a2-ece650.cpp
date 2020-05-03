#include <iostream>
#include <sstream>
#include "graph.h"
using std::toupper;


int main(int argc, char **argv) {

    char user_input;
    int v_num,Source,Destination;
    string edg_input;
    char pre_input = ' ';
    graph graph_input;
    string line;
    // read from stdin until EOF
	while (getline(cin, line)) {
        istringstream input(line);
        while (input >> user_input) {
	    user_input=(toupper(user_input));

            try {
                switch (user_input)
                {
                    case 'V' :
                        if (pre_input == 'V')
                        {
                            throw " V must be followed by E only ";
                        }
                        else
                        {
                            input >> v_num;
			    if(v_num<0)
				{
					throw " Invalid number of vertices ";
				}
                            graph_input.init_graph(v_num);
                            std::cout<<"V "<<v_num<<std::endl;
                            pre_input = 'V';
                            break;
                        }


		    case 'E' :
                    {

                        if ( pre_input == 'E')
                        {
                            throw "V and E always occur together ";
                        }
                        else
                        {
			    pre_input = 'E';
                            graph_input.clear_graph();
                            input >> edg_input;
                            istringstream input_edg(edg_input);
                            std::cout<<"E "<<edg_input<<std::endl;
                            char edg_char;
                            unsigned int v1,v2,elem_v;
                            input_edg >> edg_char;
                            while (edg_char != '}') {
                                input_edg >> edg_char;
                                if (edg_char == '}')  break;
                                input_edg >> elem_v;

                                v1 = elem_v;
                                input_edg >> edg_char;

                                input_edg >> elem_v;

                                v2 = elem_v;
                                graph_input.link(v1, v2);
                                input_edg >> edg_char;

                                input_edg >> edg_char;
                            }

			break;}
}

                    case 'S':
		    {
                        input >>Source;
                        input >>Destination;
                        graph_input.shortest_path(Source, Destination);

                        break;
                    }

                }
            }

            catch (const char* err) {
               std::cerr << "Error:" << err << endl;
            }

        }
   }

    return 0;
}
