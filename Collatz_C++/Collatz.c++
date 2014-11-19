// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <utility>  // make_pair, pair

#include "Collatz.h"

// ------------
// collatz_read
// ------------

std::pair<int, int> collatz_read (std::istream& r) {
    int i;
    r >> i;
    if (!r)
        return std::make_pair(0, 0);
    int j;
    r >> j;
    return std::make_pair(i, j);}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) 
{
    // <your code> 
    
    int start; //declare variables
    int end;
    int max_clength;
    int current_num;
    int n;
    int clength;
    int cache[1000001] = {0}; //initiate cache
   
    if(i <= j)  //start needs to be less than end
    {
        start = i;
        end = j;
    }
    else
    {
        end = i;
        start = j;
    }
    assert(start <= end); //assert that start is less than or equal to end
    
    max_clength = 0; //keeps track of the max cycle length in a range

    current_num = start; //keeps track of current number whose cycle length is being calculated

    while( current_num <= end) //keep calculating cycle lengths until we reach end of range
    {
        n = current_num;
        clength = 1;

        while(1 < n)
        {
            assert(1 < n);
		
        if( (n < 100001) && (cache[n] != 0) ) //check if clength is in cache for that number, if it is use it
	    {
		  clength+=( cache[n] -1 );
		  n = 1;
	    }
            else if( n%2 == 0 )  //even case, n/2
            {
                n = (n>>1);
                clength +=1;
            }
            else // odd case, 3n+1 / 2
            {
                n = n + (n>>1) +1;
                clength += 2;
            }
        }

        if(max_clength < clength) //check if its the new highest clength
        {
            max_clength = clength;
        }
	    cache[current_num] = clength; //save this clength in the cache
        current_num += 1; //move to next number in range

    }
    assert(0 < max_clength);
    return max_clength;
}

// -------------
// collatz_print
// -------------

void collatz_print (std::ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (std::istream& r, std::ostream& w) {
    while (true) {
        const std::pair<int, int> p = collatz_read(r);
        if (p == std::make_pair(0, 0))
            return;
        const int i = p.first;
        const int j = p.second;
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
