#ifndef darwin_h
#define darwin_h

// --------
// includes
// --------

#include <string>   // string
#include <cstring>  // strcmp
#include <vector>   // vector
#include <iostream> // cout
#include <ostream>  // ostream
#include <sstream>  // ostringstream
#include <utility>  // pair
#include <cstdlib>  // rand
#include <cassert>  // assert

// --------
// globals
// --------

#define HOP 0
#define LEFT 1
#define RIGHT 2
#define INFECT 3
#define IF_EMPTY 4
#define IF_WALL 5
#define IF_RANDOM 6
#define IF_ENEMY 7
#define GO 8

#define WEST 0
#define NORTH 1
#define EAST 2
#define SOUTH 3

// --------
// structs
// --------
using namespace std;
struct Instruction {
      int command;
      int target;
    
    //Instruction constructor
    Instruction (  int c,   int t =0)
    : command(c), target(t) {}
       
    //check if instruction is control command
    bool is_control () const {
    if (command != IF_EMPTY && command != IF_WALL && command != IF_RANDOM && command != IF_ENEMY && command != GO)
        return false;
    return true;
}
    //print instruction to ostream
     void print (std::ostream& o = std::cout) const {
    if (is_control()) {
        o << to_string(target);
        std::string co = "";
        switch(command)
        {
            case IF_EMPTY:
                co = "if_empty";
                break;
            case IF_WALL:
                co = "if_wall";
                break;
            case IF_RANDOM:
                co = "if_random";
                break;
            case IF_ENEMY:
                co = "if_enemy";
                break;
            default:
                break;
        }
        o << co << " " << std::endl;
        o.flush();
    } 
    else 
    {
        std::string co = "";
        switch(command)
        {
            case HOP:
                co = "hop";
                break;
            case LEFT:
                co = "left";
                break;
            case RIGHT:
                co = "right";
                break;
            case INFECT:
                co = "infect";
                break;
            default:
                break;
        }
        o << co << std::endl;
        o.flush();
    }
}
};

// --------
// classes
// --------

class Species {
    public:
        char symbol;
    private:
        std::vector<Instruction> program;
    public:
        //species default constructor, sets default values for species symbol and program
         Species() {}
        
        //species nondefault constructor, sets symbol
         Species (char s)
        : symbol(s) {}
        
        //compares species symbol and program to see if theyre the same species
         bool operator== (const Species& that) const {
            if (symbol != that.symbol || size() != that.size())
                return false;
            return true;
        }
         bool operator!= (const Species& that) const {
           if (symbol == that.symbol && size() == that.size())
                return false;
            return true;
        }
        
        //add instruction to the progam vector
         void add_instruction (const Instruction& i) {
            program.push_back(i);
        }
        void add_instruction (  int c,   int t = 0) {
            program.push_back(Instruction(c, t));
        }
        //clear the program vector
        void clear_program () {
            program.clear();
        }
        
        //returns size of program, number of instructions
         std::vector<Instruction>::size_type size() const{
            return program.size();
        }
         //index into progam for a particular line/instruction
        const Instruction& line (std::vector<Instruction>::size_type n) const {
            try {
                return program.at(n);
            } catch (...) {
                throw;
            }
        }
        //print species to ostream
         void print (std::ostream& o = std::cout) const 
         {
            for (  int i = 0; i < program.size(); ++i) 
            {
                o << to_string(i);
                o << ". ";
                o.flush();
                program[i].print(o);
            }
        }
};

class Creature {
    public:
        Species species;
    private:
          int pc;
    public:
        //creature default constructor, sets species and pc to default
         Creature () {}
        //constructor, specify the species, sets pc to default
        Creature (const Species& s)
        : species(s), pc(0) {}
        
        //print creature to ostream
         void print_symbol (std::ostream& o = std::cout) const {
            o << species.symbol;
        }
        //infect another creature, make it the same species
        void changeSpec (const Creature& c) {
            species = c.species;
            pc = 0;
        }
        
        //return current instruction of pc
        const Instruction& ask () const {
            return species.line(pc);
        }
           
        //update pc
        void tell (const Instruction& i, bool reply) 
        {
            if (! reply || ! i.is_control()) 
            {
                ++pc;
                
            } else {
                pc = i.target;
            }
            if (species.size()<= pc) {
                pc = 0;
            }
        }
};

class Darwin {
    private:
        struct CreatureInf 
        {
            Creature creature;
              int direction;
            bool valid;
            bool turn;
            
        //sets CreatureInf direction, validity, and creature
        CreatureInf ()
        : valid(false) 
        {}
            
        //specifies direction of creature
         CreatureInf (const Creature& c,   int d)
        : creature(c), direction(d), valid(true), turn(false) {}
        };
        
          int height;
          int width;
        
        std::vector< std::vector< CreatureInf > > board;
    public:
       //creates grid of specified height and width, 10x10 default
        Darwin (  int = 10,   int = 10);
       
        //add creature to baord,specify direction and location of the creature
        void add_creature (const Creature&,   int,   int,   int);
        
       //prints board to ostream for this turn number
        void print_board (int, std::ostream& = std::cout) const;

      //runs game prints board for each phase
        void run (  int,   int = 1, std::ostream& = std::cout);
        //given creaturedirection and board location, determines if there's a creature of different species
        bool check_direction(int real, int dir, int i, int j)
        {
            CreatureInf& m = board[i][j];
            if(real == dir)
            {
                if(real == WEST && j != 0 && board[i][j-1].valid )
                {
                    return board[i][j-1].creature.species != m.creature.species;
                }
                if(real == EAST && j != width - 1 && board[i][j+1].valid)
                {
                    return  board[i][j+1].creature.species != board[i][j].creature.species;
                }
                if(real == NORTH && i != 0 && board[i-1][j].valid )
                {
                    return  board[i-1][j].creature.species != m.creature.species;
                }
                if(real == SOUTH && i != height - 1 && board[i+1][j].valid)
                {
                    return  board[i+1][j].creature.species != m.creature.species;
                }
                return false;
            }
            return false;
        }
        //check directions given current creature location
        bool check_west(int i, int j)
        {
            CreatureInf& m = board[i][j];
            return check_direction(m.direction, WEST, i, j);
        }
        
        bool check_north(int i, int j)
        {
            CreatureInf& m = board[i][j];
            return check_direction(m.direction, NORTH, i, j);

        }
        bool check_east(int i, int j)
        {
            CreatureInf& m = board[i][j];
            return check_direction(m.direction, EAST, i, j);
        }
        bool check_south(int i, int j)
        {
            CreatureInf& m = board[i][j];
            return check_direction(m.direction, SOUTH, i, j);
        }
};

#endif