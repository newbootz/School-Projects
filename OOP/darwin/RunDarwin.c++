// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2013
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunCollatz.c++ -o RunCollatz.c++.app
    % valgrind RunDarwin.c++.app > RunDarwin.out

To configure Doxygen:
    doxygen -g
That creates the file Doxyfile.
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include "Darwin.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */
    
    Species food('f');
    food.add_instruction(LEFT);
    food.add_instruction(GO, 0);
    
    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
    
    Species hopper('h');
    hopper.add_instruction(HOP);
    hopper.add_instruction(GO, 0);

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */
    
    Species rover('r');
    rover.add_instruction(IF_ENEMY, 9);
    rover.add_instruction(IF_EMPTY, 7);
    rover.add_instruction(IF_RANDOM, 5);
    rover.add_instruction(LEFT);
    rover.add_instruction(GO, 0);
    rover.add_instruction(RIGHT);
    rover.add_instruction(GO, 0);
    rover.add_instruction(HOP);
    rover.add_instruction(GO, 0);
    rover.add_instruction(INFECT);
    rover.add_instruction(GO, 0);

    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */
    
    Species trap('t');
    trap.add_instruction(IF_ENEMY, 3);
    trap.add_instruction(LEFT);
    trap.add_instruction(GO, 0);
    trap.add_instruction(INFECT);
    trap.add_instruction(GO, 0);
    
    // ----
    // best
    // ---- 
    
    Species best('b');
    best.add_instruction(IF_ENEMY, 9);
    best.add_instruction(IF_EMPTY, 7);
    best.add_instruction(IF_RANDOM, 5);
    best.add_instruction(LEFT);
    best.add_instruction(GO, 0);
    best.add_instruction(RIGHT);
    best.add_instruction(GO, 0);
    best.add_instruction(HOP);
    best.add_instruction(GO, 0);
    best.add_instruction(INFECT);
    best.add_instruction(GO, 0);

    // ----------
    // darwin 8x8
    // ----------
    cout << "*** Darwin 8x8 ***" << endl;
    try {
        /*
        8x8 Darwin
        Food,   facing east,  at (0, 0)
        Hopper, facing north, at (3, 3)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (4, 4)
        Hopper, facing west,  at (4, 3)
        Food,   facing north, at (7, 7)
        Simulate 5 moves.
        Print every grid.
        */

        Darwin d(8, 8);
        const Creature& f1 = Creature(food);
        const Creature& h1 = Creature(hopper);
        const Creature& h2 = Creature(hopper);
        const Creature& h3 = Creature(hopper);
        const Creature& h4 = Creature(hopper);
        const Creature& f2 = Creature(food);
        d.add_creature(f1, EAST, 0, 0);
        d.add_creature(h1, NORTH, 3, 3);
        d.add_creature(h2, EAST, 3, 4);
        d.add_creature(h3, SOUTH, 4, 4);
        d.add_creature(h4, WEST, 4, 3);
        d.add_creature(f2, NORTH, 7, 7);
        d.run(5,1);
        }
        catch(...)
        {
            assert(false);
        }

    // ----------
    // darwin 7x9
    // ----------

    try {
        cout << "*** Darwin 7x9 ***" << endl;
        srand(0);
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        Darwin d(7, 9);
        const Creature& t1 = Creature(trap);
        const Creature& h = Creature(hopper);
        const Creature& r = Creature(rover);
        const Creature& t2 = Creature(trap);
        d.add_creature(t1, SOUTH, 0, 0);
        d.add_creature(h, EAST, 3, 2);
        d.add_creature(r, NORTH, 5, 4);
        d.add_creature(t2, WEST, 6, 8);
        d.run(5,1);
        }
        catch(...)
        {
            assert(false);
        }

    // ------------
    // darwin 72x72
    // without best
    // ------------

    try {
        cout << "*** Darwin 72x72 without Best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        Simulate 1000 moves.
        Print every 100th grid.
        */
        Darwin d(72, 72);
        for(int i = 0; i < 10; ++i){
            int pos = rand() % 5184;
            int dir = rand() % 4;
            const Creature& f = Creature(food);
            d.add_creature(f, dir, (pos/72), (pos%72)); 
        }
        for(int i = 0; i < 10; ++i){
            int pos = rand() % 5184;
            int dir = rand() % 4;
            const Creature& h = Creature(hopper);
            d.add_creature(h, dir, (pos/72), (pos%72)); 
        }
        for(int i = 0; i < 10; ++i){
            int pos = rand() % 5184;
            int dir = rand() % 4;
            const Creature& r = Creature(rover);
            d.add_creature(r, dir, (pos/72), (pos%72)); 
        }
        for(int i = 0; i < 10; ++i){
            int pos = rand() % 5184;
            int dir = rand() % 4;
            const Creature& t = Creature(trap);
            d.add_creature(t, dir, (pos/72), (pos%72)); 
        }
        d.run(1000, 100);
    }
    catch(...)
        {
            cout << "Error darwin 72x72 without Best\n";
        }

    // ------------
    // darwin 72x72
    // with best
    // ------------

    try {
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        10 Best
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print every 100th grid.
        */
       
        Darwin d(72, 72);
        for(int i = 0; i < 10; ++i){
            int pos = rand() % 5184;
            int dir = rand() % 4;
            d.add_creature(Creature(food), dir, (pos/72), (pos%72)); 
        }
        for(int i = 0; i < 10; ++i){
            int pos = rand() % 5184;
            int dir = rand() % 4;
            d.add_creature(Creature(hopper), dir, (pos/72), (pos%72)); 
        }
        for(int i = 0; i < 10; ++i){
            int pos = rand() % 5184;
            int dir = rand() % 4;
            d.add_creature(Creature(rover), dir, (pos/72), (pos%72)); 
        }
        for(int i = 0; i < 10; ++i){
            int pos = rand() % 5184;
            int dir = rand() % 4;
            d.add_creature(Creature(trap), dir, (pos/72), (pos%72)); 
        }
        for(int i = 0; i < 10; ++i){
            int pos = rand() % 5184;
            int dir = rand() % 4;
            d.add_creature(Creature(best), dir, (pos/72), (pos%72)); 
        }
        d.run(1000, 100);
        }
        catch(...)
        {
            cout << "Error darwin 72x72 withBest\n";
        }

}
    