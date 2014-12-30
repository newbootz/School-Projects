
// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2014
// Glenn P. Downing
// -------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <fstream>
#include "Cell.h"
#include "AbstractCell.h"
#include "Life.c++"

// ----
// main
// ----

int main () {
    using namespace std;
    //ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // -----------------
    // Conway Cell 21x13
    // -----------------

    cout << "*** Life<ConwayCell> 21x13 ***" << endl;
    /*
    Simulate 12 evolutions.
    print_grid every grid (i.e. 0, 1, 2, 3, ... 12)
    */
    try
    {
        ifstream in_file;
        in_file.open("RunLife21x13cc.in");
        ofstream out_file;
        out_file.open("RunLife21x13cc.out");

        Life<ConwayCell> life(in_file, out_file);
        life.print_grid(0);
        for(int i = 0; i < 12; i++)
        {
            life.step(1);
            life.print_grid(i+1);
        }
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
   

    // -----------------
    // Conway Cell 20x29
    // -----------------

    cout << "*** Life<ConwayCell> 20x29 ***" << endl;
    /*
    Simulate 28 evolutions.
    print_grid every 4th grid (i.e. 0, 4, 8, ... 28)
    */
    try
    {
        ifstream in_file;
        in_file.open("RunLife20x29cc.in");
        ofstream out_file;
        out_file.open("RunLife20x29cc.out");

        Life<ConwayCell> life(in_file, out_file);
        life.print_grid(0);
        for(int i = 0; i < 28; i++)
        {
            life.step(1);
            if((i+1)%4 == 0)
            {
                life.print_grid(i+1);
            }
            
        }
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
   

    // ------------------
    // Conway Cell 109x69
    // ------------------

    cout << "*** Life<ConwayCell> 109x69 ***" << endl;
    /*
    Simulate 283 evolutions.
    print_grid the first 10 grids (i.e. 0, 1, 2, ... 9).
    print_grid the 283rd grid.
    Simulate 40 evolutions.
    print_grid the 323rd grid.
    Simulate 2177 evolutions.
    print_grid the 2500th grid.
    */

    try
    {
        ifstream in_file;
        in_file.open("RunLife109x69cc.in");
        ofstream out_file;
        out_file.open("RunLife109x69cc.out");

        Life<ConwayCell> life(in_file, out_file);
        life.print_grid(0);
        for(int i = 0; i < 2501; i++)
        {
            life.step(1);
            if((i+1) < 10)
            {
                life.print_grid(i+1);
            }
            if((i+1) == 283)
            {
                life.print_grid(i+1);
            }
            if((i+1) == 323)
            {
                life.print_grid(i+1);
            }
            if((i+1) == 2500)
            {
                life.print_grid(i+1);
            }
            
        }
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
    
    // ------------------
    // Fredkin Cell 20x20
    // ------------------

    cout << "*** Life<FredkinCell> 20x20 ***" << endl;
    /*
    Simulate 5 evolutions.
    print_grid every grid (i.e. 0, 1, 2, ... 5)
    */

    try
    {
        ifstream in_file;
        in_file.open("RunLife20x20fc.in");
        ofstream out_file;
        out_file.open("RunLife20x20fc.out");

        Life<FredkinCell> life(in_file, out_file);
        life.print_grid(0);
        for(int i = 0; i < 5; i++)
        {
            life.step(1);
            life.print_grid(i+1);
        }
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
   

    // ----------
    // Cell 20x20
    // ----------

    cout << "*** Life<Cell> 20x20 ***" << endl;
    /*
    Simulate 5 evolutions.
    print_grid every grid (i.e. 0, 1, 2, ... 5)
    */


    /*
      read RunLife0.in
      print_grid grid.
      Simulate 5 moves.
      print_grid every grid.
    */
try
{
    ifstream in_file;
    in_file.open ("RunLife20x20c.in");
    ofstream out_file;
    out_file.open ("RunLife20x20c.out");

    Life<Cell> life(in_file, out_file);
    life.print_grid(0);
    for(int i = 0; i < 5; i++)
    {
      life.step(1);
      life.print_grid(i + 1);
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
 

    return 0;}