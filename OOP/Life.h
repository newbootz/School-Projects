 #include <cstdlib>
 #include <fstream>  // endl, istream, ostream
 #include <string>    // strings for names
 #include <vector>    // vector
 #include <typeinfo>

 #include "Cell.h"
 #include "AbstractCell.h"



template<typename T>
class Life
{
    //int for number of columns and rows
    int cols;
    int rows;
    //output stream
    ofstream& o;
    //cells alive
    int num_cells;
    vector< vector<T> > life_grid;
    //grid with count of surrounding cells that are alive
    vector< vector<int> > life_count;

public:
	
	//methods and Life constructor 
	void step(int turns);
	void update_neighbors();
	void print_grid(int generation);
  Life(ifstream& r, ofstream& w);
	

};


