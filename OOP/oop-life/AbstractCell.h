/*
AbstractCell.h
*/
#include <cstdlib>
#include <string.h>
#include <vector>  // vector
#ifndef AbstractCell_h
#define AbstractCell_h

#include <iostream>

class AbstractCell
{

protected:
	bool alive;

public:
	virtual bool neighbors(int r, int c)=0;
	virtual char print() = 0;
	virtual void new_state(char c)=0;
	virtual void evolve(int alive_neighbors) = 0;
	virtual AbstractCell* clone()=0;

	bool liveness()
	{
		return alive;
	}
};

class ConwayCell : public AbstractCell
{
public:
	//default constructor
	ConwayCell()
	{
		//printf("ConwayCell constructor\n");
		alive = false;
	}
	//copy constructor
	ConwayCell(const ConwayCell* const other) //why is it a const pointer ?
	{
		//printf("ConwayCell copy constructor\n");
		alive = (*other).alive;
	}
	void new_state(char c) 						
	{
		//printf("Conway new_state\n");
		if('.' == c)
		{
			alive = false;
		}
		else
		{
			alive = true;
		}
	}
	AbstractCell* clone()
	{
		//printf("ConwayCell clone\n");
		return new ConwayCell(this);
	}
	void evolve(int alive_neighbors)
	{
		//printf("Conway evolve\n");
		//bring back to life if has exactly 3 neighbors
		if(!alive)
		{
			if(alive_neighbors == 3)
				alive = true;
		}
		//else it dies if has less than 2, more than 3
		else
		{
			if(alive_neighbors < 2 || alive_neighbors > 3)
				 alive = false;
		}
	}
	//print out the ConwayCell
	char print()
	{
		//printf("ConwayCell print\n");
		if(alive)
		{
			return '*';
		}
		else
		{
			return '.';
		}
	}
	bool neighbors(int cr, int cc)
	{
		//printf("Conway neighbors\n");
		return true;
	}

	

};



class FredkinCell : public AbstractCell
{
public:
	int age;

	//default constructor
	FredkinCell():
	age(0)
	{
		//printf("FredkinCell constructor\n");
		 alive = false;
	}
	//copy constructor
	FredkinCell(const FredkinCell* const other):
	 age((*other).age)
	{
		//printf("FredkinCell copy constructor\n");
		 alive = (*other).alive;
	}
	void new_state(char c)
	{
		//printf("Fredkin new_state\n");
		alive = false;
		if(c!='-' && '0'<= c && c <= '9')
		{
			alive = true;
			age = c - '0';
		}

	}
	//return copy of this object
	AbstractCell* clone()
	{
		//printf("Fredkin clone\n");
		return new FredkinCell(this);
	}
	void evolve (int alive_neighbors)
	{
		//printf("Fredkin evolve changed\n" );
		bool temp = alive;
		if((!alive) && (alive_neighbors ==1 || alive_neighbors == 3))
		{
			//printf("brought back to life\n");
			alive = true;
		}
		else if(alive && (alive_neighbors == 0 || alive_neighbors == 2 || alive_neighbors == 4))
		{
			//printf("this cell died\n");
			alive = false;
		}
		if(temp && alive)
		{
			++age;
		}
	}
	char print()
	{
		//printf("FredkinCell print\n");
		if(alive)
		{
			//age less than ten is ascii number, greater is just a +
			if(age < 10)
			{
				return '0' + age;
			}
			else
			{
				return '+';
			}
		}
		else
		{
			return '-';
		}
	}
	bool neighbors(int r, int c)
	{
		//printf("FredkinCell neighbors\n");
		return r ==0 || c == 0;
	}


};

#endif



