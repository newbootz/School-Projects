
#include "Life.h"

template<typename T>
Life<T>::Life(ifstream& r, ofstream& w):
o(w)
{
	//printf("Life constructor\n");

	
	//set rows, and cols
	r >> rows;
	r >> cols;
	//create a row rowI, of size cols, filled with 0
	vector<int> rowI(cols, 0);
	//make a row rowT, of size cols, filled with object type T
	vector<T> rowT(cols, T());
	life_count = vector < vector<int> >(rows, rowI);
	life_grid = vector< vector<T> > (rows, rowT);
	
	char next;
	num_cells = 0;
	for(int i=0; i < rows; ++i)
	{
		for(int j=0; j< cols; ++j)
		{
			//reading the grid, one char at a time into next
			r >> next;
			//save it into the grid
			life_grid[i][j].new_state(next);
		}
	}
	update_neighbors();

}
template<typename T>
void Life<T>::update_neighbors()
{
	//printf("Life update_neighbors\n");

	//set neighbor count of all cells to zero
	for(int i = 0; i < rows; ++i)
	{
		for(int j = 0; j < cols; ++j)
		{
			life_count[i][j] = 0;
		}
	}
	num_cells = 0;
	//iterate through all the cells
	for(int i = 0; i < rows; ++i)
	{
		for(int j = 0; j < cols; ++j)
		{
			//if this cell is alive, increment num_cells and set neighbor count
			if(life_grid[i][j].liveness())
			{
				++num_cells;
				//check all neighbors and increase their count

				if((i-1>= 0) && (j-1 >= 0) && life_grid[i -1][j -1].neighbors(-1,-1))
				{
					//-1,-1
					++life_count[i -1][j -1];
				}
				if(j-1 >= 0 && life_grid[i + 0][j -1].neighbors(0,-1))
				{
					//0,-1
					++life_count[i + 0][j -1];
				}
				if((i+1 < rows) && (j-1 >= 0) && life_grid[i + 1][j -1].neighbors(1,-1))
				{
					//1,-1
					++life_count[i + 1][j -1];
				}

				if((i-1 >= 0) && (j+1 < rows) && life_grid[i -1][j +1].neighbors(-1,1))
				{
					//-1,1
					++life_count[i -1][j +1];
				}
				if((i+1 < rows) && (j+1 < cols) && life_grid[i + 1][j +1].neighbors(1,1))
				{
					//1,1
					++life_count[i + 1][j +1];
				}
				if(j+1 < cols && life_grid[i + 0][j +1].neighbors(0,1))
				{
					//0,1
					++life_count[i + 0][j +1];
				}
				if(i-1 >= 0 && life_grid[i -1][j +0].neighbors(-1,0))
				{
					//-1,0
					++life_count[i -1][j +0];
				}
				if(i+1 < rows && life_grid[i + 1][j +0].neighbors(1,0))
				{
					//1,0
					++life_count[i + 1][j +0];
				}
				
			}
		}
	}
}
template<typename T>
void Life<T>::step(int t)
{
	//evolve the cells, 't' times
	for(int x = 0; x < t; ++x)
	{
		for(int i =0; i < rows; ++i)
		{
			for(int j = 0; j < cols; ++j)
			{
				//evolve this cell
				life_grid[i][j].evolve(life_count[i][j]);
			}
		}
		//update neighbors for this generation
		update_neighbors();
	}
}
template<typename T>
void Life<T>::print_grid(int generation)
{
	//prints generation and num_cells
	o << "Generation = " << generation << ", num_cells = " << num_cells << "." << endl;
	//go through grid and print each cell
	for(int i = 0; i < rows; ++i)
	{
		for(int j = 0; j < cols; ++j)
		{
			o << life_grid[i][j].print();
		}
		o << endl;
	}
	o << endl;
}





















