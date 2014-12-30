// --------
// includes
// --------

#include "Darwin.h"




Darwin::Darwin (  int h,   int w)
:board(h, std::vector< CreatureInf >(w))
{
    width = w;
    height = h;
}

void Darwin::add_creature (const Creature& c,   int d,   int h,   int w) {
    if (height <= h || width <= w) {
        return;
    }
    else if (d < 0) 
    {
        d = 0;
    } else if (3 < d) 
    {
        d = 3;
    }
    board[h][w] = CreatureInf(c, d);
}

void Darwin::print_board (  int turn, std::ostream& o) const
 {
    o << "Turn = " << turn << "." << std::endl << "  ";
    for (  int i = 0; i < width; ++i) 
    {
        o << to_string(i%10);
    }
    o << std::endl;
    for (  int i = 0; i < height; ++i) {
        o << to_string(i%10);
        o << " ";
        for (  int j = 0; j < width; ++j) 
        {
            const CreatureInf& m = board[i][j];
            if (!m.valid) 
            {
                o << ".";
            } else 
            {
                m.creature.print_symbol(o);
            }
        }
        o << std::endl;
    }
    o.flush();
}

void Darwin::run (  int moves,   int step, std::ostream& o) {
    print_board(0, o);
    moves = moves+1;
    for ( int move = 1; move < moves; ++move) 
    {
            for (  int i = 0; i < height; ++i) {
        for (  int j = 0; j < width; ++j) 
        {
            CreatureInf& m = board[i][j];
            
            
            while (m.valid && !(m.turn)) {
                const Instruction& in = m.creature.ask();
                if (!in.is_control())
                {
                    m.turn = true;
                }
                if (in.command == IF_EMPTY) 
                {
                    bool above = false;
                    bool below = false;
                    bool right = false;
                    bool left = false;
                    if(m.direction == WEST && j != 0 && !board[i][j-1].valid)
                    {
                        above = true;
                    }
                    if(m.direction == NORTH && i != 0 && !board[i-1][j].valid)
                    {
                        left = true;
                    }
                    if(m.direction == EAST && j != width - 1 && !board[i][j+1].valid)
                    {
                        below = true;
                    }
                    if(m.direction == SOUTH && i != height - 1 && !board[i+1][j].valid)
                    {
                        right = true;
                    }
                    if (above || left   ||below || right) 
                    {
                        m.creature.tell(in, true);
                    } 
                    else 
                    {
                        m.creature.tell(in, false);
                    }
                } else if (in.command == IF_WALL) {
                    if ((m.direction == WEST && j == 0)    || \
                        (m.direction == NORTH && i == 0)   || \
                        (m.direction == EAST && j == width - 1) || \
                        (m.direction == SOUTH && i == height - 1)) {
                        m.creature.tell(in, true);
                    } else {
                        m.creature.tell(in, false);
                    }
                } else if (in.command == IF_RANDOM) {
                    if ((rand() & 1) == 1) {
                        m.creature.tell(in, true);
                    } else {
                        m.creature.tell(in, false);
                    }
                } 
                else if (in.command == IF_ENEMY) 
                {
                    bool a = check_west(i,j);
                    bool l = check_north(i,j);
                    bool r = check_east(i,j);
                    bool b = check_south(i,j);
                    
                    if (a || l || r  || b) {
                        m.creature.tell(in, true);
                    } 
                    else 
                    {
                        m.creature.tell(in, false);
                    }
                } else if (in.command == GO) {
                    m.creature.tell(in, true);
                } 
                else if (in.command == HOP) 
                {
                    bool w = m.direction == WEST && j != 0 && !board[i][j-1].valid;
                    bool n = m.direction == NORTH && i != 0 && !board[i-1][j].valid;
                    bool e = m.direction == EAST && j != width - 1 && !board[i][j+1].valid;
                    bool s = m.direction == SOUTH && i != height - 1 && !board[i+1][j].valid;
                    m.creature.tell(in, false);
                    if (w) {
                        board[i][j-1] = m;
                        m.valid = false;
                    } 
                    else if (e) {
                        board[i][j+1] = m;
                        m.valid = false;
                    } 
                    else if (n) {
                        board[i-1][j] = m;
                        m.valid = false;
                    } 
                    
                    else if (s) {
                        board[i+1][j] = m;
                        m.valid = false;
                    }
                } 
                else if (in.command == LEFT) {
                    m.creature.tell(in, false);
                    m.direction = (m.direction == WEST ? SOUTH : m.direction - 1);
                } else if (in.command == RIGHT) {
                    m.creature.tell(in, false);
                    m.direction = (m.direction == SOUTH ? WEST : m.direction + 1);
                } 
                else if (in.command == INFECT) {
                    m.creature.tell(in, false);
                    int dir = m.direction;
                    Species ms = m.creature.species;
                    bool infect_1 = dir == WEST && j != 0 && board[i][j-1].valid ;
                    bool infect_2 = dir == NORTH && i != 0 && board[i-1][j].valid;
                    bool infect_3 = dir == EAST && j != width - 1 && board[i][j+1].valid;
                    bool infect_4 = dir == SOUTH && i != height - 1 && board[i+1][j].valid;
                    if (infect_1) 
                    {
                        if(board[i][j-1].creature.species != ms)
                        {
                            board[i][j-1].creature.changeSpec(m.creature);
                        }
                        
                    } 
                    else if (infect_2) 
                    {
                        if(board[i-1][j].creature.species != ms)
                        {
                            board[i-1][j].creature.changeSpec(m.creature);
                        }
                        
                    } 
                    else if (infect_3) 
                    {
                        if(board[i][j+1].creature.species != ms)
                        {
                            board[i][j+1].creature.changeSpec(m.creature);
                        }
                        
                    } 
                    else if (infect_4) 
                    {
                        if(board[i+1][j].creature.species != ms)
                        {
                            board[i+1][j].creature.changeSpec(m.creature);
                        }
                    }
                }
            }
        }
    }
    for (  int i = 0; i < height; ++i) {
        for (  int j = 0; j < width; ++j) {
            board[i][j].turn = false;
        }
    }
    if (move % step == 0) 
    {
        o << endl;
        o << "";
        print_board(move, o);
    }
    }
    o << "";
    o << endl;
    o.flush();
}
