#include <cstdlib>
#include <vector>  // vector

#include "AbstractCell.h"

using namespace std;

#ifndef Cell_h
#define Cell_h

class Cell
{

	//pointer that this class is wrapper for
	AbstractCell* c_ptr;

public:
	//default constructor
	Cell()
	{
		//printf("Cell default constructor\n");
		FredkinCell fc;
		c_ptr = fc.clone(); 
	}
	//copy constructor
	Cell(const Cell& c)
	{
		//printf("Cell copy constructor\n");
		c_ptr = (*c.c_ptr).clone();
	}
	//prints out a char for the state
	char print()
	{
		//printf("Cell print\n");
		return (*c_ptr).print();
	}
		//changes the state of the cell based on the char input
	void new_state(char symbol)
	{
		//printf("Cell new_state\n");
		FredkinCell* fc = dynamic_cast<FredkinCell*>(c_ptr);
		if(fc != 0 && (symbol =='.' || symbol == '*'))
		{
			
			ConwayCell cc;
			delete c_ptr;
			c_ptr = cc.clone();
		}
		(*c_ptr).new_state(symbol);

	}
	

	//evolves the cell one iteration
	void evolve(int alive_neighbors)
	{
		//printf("Cell evolve\n");
		(*c_ptr).evolve(alive_neighbors);
		FredkinCell* fc = dynamic_cast<FredkinCell*>(c_ptr);
		if(fc != 0 && (*fc).age == 2)
		{
			new_state('*');

		}
	}

	bool neighbors(int change_r, int change_c)
	{
		//printf("Cell neighbors\n");
		//printf("r: %d, c: %d\n",change_r, change_c );
		bool ans = (*c_ptr).neighbors(change_r, change_c);
		//printf("neighbors line 79\n");
		return ans;
	}
	bool liveness()
	{
		//printf("Cell alive\n");
		return (*c_ptr).liveness();
	}

	//
	

	//destructor
	~Cell()
	{
		//printf("Cell destructor\n" );
		delete c_ptr;
	}

};



#endif