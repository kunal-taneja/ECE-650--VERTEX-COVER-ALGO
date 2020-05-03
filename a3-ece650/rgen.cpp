#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <string>
using namespace std;
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}


unsigned int n_street ( unsigned int n )
{
    std::ifstream urandom("/dev/urandom");

   
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int rand = 3;
    urandom.read((char*)&rand, sizeof(unsigned int));
    rand = rand % (n-2+1) +2;
    urandom.close();
    return (unsigned int) rand;

}

unsigned int n_line_segment (unsigned int n)
{
    
    std::ifstream urandom("/dev/urandom");

    
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int rand = 3;
    urandom.read((char*)&rand, sizeof(unsigned int));
    rand = rand % (n-1+1) + 1;
    urandom.close();
    return (unsigned int) rand;


}

unsigned int n_wait (unsigned int n)
{
    std::ifstream urandom("/dev/urandom");

        if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int time = 3;
    urandom.read((char*)&time, sizeof(unsigned int));
    time = time % (n-5+1) + 5;
    urandom.close();
    return (unsigned int) time;


}

int coord_value (unsigned int n)
{
   
    std::ifstream urandom("/dev/urandom");

   
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int rand = 3;
    urandom.read((char*)&rand, sizeof(int));
    rand = rand % (n+n);
    int out= rand - n ;
    urandom.close();
    return out;


}

void create_street( vector<string> &street , unsigned int s_num)
{
    string name = "street";
    for (unsigned int i=0; i < s_num; i++)
    {
        street.push_back(name);
        name = name +'i';
    }

}

int max_xy( int a1, int a2)
{

    int max1;
    if ( a1 > a2)
    {
        max1 = a1;
        return max1;
    }
    max1 = a2;
    return max1;

}

int min_xy( int a1, int a2)
{

    int min1;
    if ( a1 > a2)
    {
        min1 = a2;
        return min1;
    }

    min1 = a1;
    return min1;

}



bool if_intersect( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    double xnum, xden, xcoor, ynum, yden, ycoor;

    xnum = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4));
    xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));
    xcoor =  xnum / xden;

    ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4);
    yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
    ycoor = ynum / yden;

    int min_x1, min_x2, max_x1, max_x2, min_y1, min_y2, max_y1, max_y2;

    min_x1 = min_xy(x1,x2);
    max_x1 = max_xy(x1,x2);
    min_x2 = min_xy(x3,x4);
    max_x2 = max_xy(x3,x4);
    min_y1 = min_xy(y1,y2);
    max_y1 = max_xy(y1,y2);
    min_y2 = min_xy(y3,y4);
    max_y2 = max_xy(y3,y4);

    if ( min_x1<= xcoor &&  xcoor <= max_x1)
        if ( min_x2 <= xcoor && xcoor <= max_x2)
            if ( min_y1 <= ycoor && ycoor <= max_y1)
                if ( min_y2 <= ycoor && ycoor <= max_y2)
                    return true;
    return false;

}



bool if_add_point ( vector<int> coordinate, int x, int y)
{
    int s = coordinate.size();
    if ( coordinate.empty())
    {

        return true;
    }if ( s == 2)
    {
        if (( x == coordinate[0]) && (y == coordinate[1]) )
        {

            return false;
        }

        return true;
    }
    else
    {
           for (unsigned int i = 0; i < coordinate.size(); i = i + 2){
            if (x == coordinate[i] && y == coordinate[i+1]){
                return false;
            }
        }

        double k1, k2;
        
        if ( x == coordinate[s-2] && x == coordinate[s-4])
            return false;

               if ( (x == coordinate[s-2]) && (x != coordinate[s-4]))
        {
            if ( s == 4)
                return true;
            else
            {
                for ( int i = s-3; i >=2; i = i-2 )
                {
                    if ( if_intersect(x,y,coordinate[s-2],coordinate[s-1],coordinate[i-1],coordinate[i],coordinate[i-3],coordinate[i-2]))
                        return false;

                }

                return true;
            }
        }

        if ( (coordinate[s-4] == coordinate[s-2]) && (x != coordinate[s-2]))
        {
            if ( s == 4)
                return true;
            else
            {
                for ( int i = s-3; i >=0; i = i-2 )
                {
                    if ( if_intersect(x,y,coordinate[s-2],coordinate[s-1],coordinate[i-1],coordinate[i],coordinate[i-3],coordinate[i-2]))
                        return false;

                }

                return true;
            }
        }

        

        k1 = ((y - coordinate[s-1]) / (x-coordinate[s-2]));
        k2 = ((coordinate[s-1]) - coordinate[s-3]) / (coordinate[s-2]-coordinate[s-4]);

        if (k1 == k2)
            return false;

        else
        {

            if ( s == 4)
                return true;
            else
            {
                for ( int i = s-3; i >=0; i = i-2 )
                {
                    if ( if_intersect(x,y,coordinate[s-2],coordinate[s-1],coordinate[i-1],coordinate[i],coordinate[i-3],coordinate[i-2]))
                        return false;

                }

                return true;
            }

        }


    }

}





int main (int argc, char **argv) {

    std::string svalue, nvalue, lvalue, cvalue;
    unsigned int s_value = 10, n_value = 5, l_value = 5, c_value = 20;
    int c;
    int s_num, l_num, x_cord, y_cord;
    unsigned int w_sed;

    vector<string> street; 
    vector<int> n_street_line;
    vector<int> coordinate;

    opterr = 0;

    
    while ((c = getopt(argc, argv, "s:n:l:c:")) != -1) {
        switch (c) {
            case 's':
                svalue = optarg;
                s_value = std::atoi(svalue.c_str());
                if (s_value < 2)
                {
                    cerr << "Error: the number is too small (after s)"<<endl;
                    exit(1);
                }

                break;
            case 'n':
                nvalue = optarg;
                n_value = std::atoi(nvalue.c_str());
                if (n_value < 1)
                {
                    cerr << "Error: the number is too small (after n)"<<endl;
                    exit(1);
                }

                break;
            case 'l':
                lvalue = optarg;
                l_value = std::atoi(lvalue.c_str());
                if (l_value < 5)
                {
                    cerr << "Error: the number is too small (after l)"<<endl;
                    exit(1);
                }

                break;
            case 'c':
                cvalue = optarg;
                c_value = std::atoi(cvalue.c_str());
                if (c_value < 1)
                {
                    cerr << "Error: the number is too small (after c)"<<endl;
                    exit(1);
                }

                break;

            case '?':
                if (optopt == 's') {
                    std::cerr << "Error: option -" << optopt
                              << " requires an argument." << std::endl;
                    break;
                }
                else if (optopt == 'n') {
                    std::cerr << "Error: option -" << optopt
                              << " requires an argument." << std::endl;
                    break;
                }
                else if (optopt == 'l') {
                    std::cerr << "Error: option -" << optopt
                              << " requires an argument." << std::endl;
                    break;
                }
                else if (optopt == 'c') {
                    std::cerr << "Error: option -" << optopt
                              << " requires an argument." << std::endl;
                    break;
                }

                else
                    std::cerr << "Error: unknown option: " << optopt << std::endl;
                    break;

        }


    }

    while (true)
    {




        if ( !street.empty())
        {
            for(std::vector<string>::iterator it = street.begin(); it != street.end(); it++)
            {
                cout<<"r "<<'"'<<*it<<'"'<<endl;

            }

            street.clear();
          n_street_line.clear();

        }


        s_num = n_street(s_value);

        create_street(street, s_num);


        for (int j = 0; j < s_num; j++)
        {
            l_num = n_line_segment(n_value);
            n_street_line.push_back(l_num);

        }

        int index = 0;

        for (unsigned int mk = 0; mk < n_street_line.size(); mk++)
        {
            coordinate.clear();    
            int times = 0;
            int error = 0;
            while ( times < n_street_line[mk]+1 )
            {
                x_cord = coord_value(c_value);
                y_cord = coord_value(c_value);
                if (if_add_point(coordinate, x_cord, y_cord))
                {
                    coordinate.push_back(x_cord);
                    coordinate.push_back(y_cord);
                    times++;
                    error = 0;
                }

                else
                {

                    if ( error == 25)
                    {
                        cerr<<"Error: failed to generate valid input for 25 simultaneous attempts"<<endl;
                        exit(1);   
                    }

                    error++;
                }


            }


             string a_output;
            a_output = string("a \"") + street[index] + "\" ";

            for (unsigned int mk = 0; mk < coordinate.size(); mk = mk+2)
            {
                string a,b;
                if (coordinate[mk]<0){
                  a = "-"+patch::to_string(coordinate[mk]*(-1));
                } else {
                  a = patch::to_string(coordinate[mk]);
                }
                if (coordinate[mk+1]<0){
                  b = "-"+patch::to_string(coordinate[mk+1]*(-1));
                } else {
                  b = patch::to_string(coordinate[mk+1]);
                }
                a_output = a_output + '('+ a + ','+ b +')';
            }

            cout<<a_output<<endl;

            index++;
        }

        
            cout<<'g'<<endl;
            w_sed = n_wait(l_value);
            usleep(w_sed*1000000);

        }

return 0;
}










