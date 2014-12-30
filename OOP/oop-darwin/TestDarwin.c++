#include <stdexcept>
#include <sstream>
#include "gtest/gtest.h"
#define private public
#define protected public
#include "Darwin.h"


using namespace std;
//class Instruction

//control
TEST(Instruction, control_1)
{
	Instruction ins(HOP);
	ASSERT_EQ(ins.is_control(), false);
}
TEST(Instruction, control_2)
{
	 Instruction ins(IF_WALL);
	 ASSERT_EQ(ins.is_control(), true);
}
TEST(Instruction, control_3)
{
	 Instruction ins(GO, 0);
	 ASSERT_EQ(ins.is_control(), true);
}
//print
TEST(Instruction, print_1)
{
	Instruction ins(HOP);
    ostringstream o;
    ins.print(o);
    ASSERT_EQ(strcmp(o.str().c_str(), "hop\n"),0);
}
TEST(Instruction, print_2)
{
	Instruction ins(IF_WALL);
    ostringstream o;
    ins.print(o);
    ASSERT_EQ(strcmp(o.str().c_str(), "if_wall\n") == 0,false);
}
TEST(Instruction, print_3)
{
	Instruction ins(LEFT);
    ostringstream o;
    ins.print(o);
    ASSERT_EQ(strcmp(o.str().c_str(), "left\n") ,0);
}

//class species

//operators

TEST(Species, operator_1)
{
	Species h('h');
	Species r('r');
	ASSERT_EQ(h != r,true);
}
TEST(Species, operator_2)
{
	Species h('h');
	Species r('h');
	ASSERT_EQ(h==r, true);
}
TEST(Species, operator_3)
{
	Species h('b');
	Species r('r');
	ASSERT_EQ(h != r,true);
}

//add

TEST(Species, add_1)
{
	Species f('f');
	f.add_instruction(HOP);
	Instruction i(HOP);
	ASSERT_EQ(f.program.size(), 1);
}
TEST(Species, add_2)
{
	Species f('f');
	f.add_instruction(HOP);
	Instruction ins(HOP);
	ASSERT_EQ(f.program[0].command, ins.command);
}
TEST(Species, add_3)
{
	Species f('f');
	f.add_instruction(HOP);
	Instruction ins(HOP);
	ASSERT_EQ(f.program[0].target,ins.target);
}

//line

TEST(Species, line_1){
	Species s('f');
	s.add_instruction(Instruction(HOP));
	ASSERT_EQ(s.line(0).command,s.program[0].command);
}
TEST(Species, line_2){
	Species s('f');
	s.add_instruction(Instruction(HOP));
	ASSERT_EQ(s.line(0).target,s.program[0].target);
}
TEST(Species, line_3)
{
    Species s('s');
    s.add_instruction(Instruction(HOP));
    s.add_instruction(Instruction(GO, 0));
    ASSERT_EQ(s.line(1).command,Instruction(GO, 0).command);
    ASSERT_EQ(s.line(1).target,Instruction(GO, 0).target);
}
//print

TEST(Species, spec_print_1)
{
	Species s('f');
    s.add_instruction(HOP);
    ostringstream o;
    s.print(o);
    ASSERT_EQ(strcmp(o.str().c_str(), "0. hop\n"),0);
}
TEST(Species, spec_print_2)
{
	Species s('f');
    s.add_instruction(LEFT);
    ostringstream o;
    s.print(o);
    ASSERT_EQ(strcmp(o.str().c_str(), "0. left\n"),0);
}
TEST(Species, spec_print_3)
{
	Species s('f');
    s.add_instruction(HOP);
    s.add_instruction(LEFT,0);
    ostringstream o;
    s.print(o);
    ASSERT_EQ(strcmp(o.str().c_str(), "0. hop\n1. left\n"),0);
}
//print symbol
TEST(Creature, symbol_1)
{
	Creature c(Species('f'));
    ostringstream o;
    c.print_symbol(o);
    ASSERT_EQ(strcmp(o.str().c_str(), "f"),0);
}

TEST(Creature, symbol_2)
{
	Creature c(Species('g'));
    ostringstream o;
    c.print_symbol(o);
    ASSERT_EQ(strcmp(o.str().c_str(), "g"),0);
}
TEST(Creature, symbol_3)
{
	Creature c(Species('h'));
    ostringstream o;
    c.print_symbol(o);
    ASSERT_EQ(strcmp(o.str().c_str(), "h"),0);
}
//changeSpec
TEST(Creature, changeSpec_1)
{
    Creature c1(Species('s'));
    Creature c2(Species('t'));
    c1.changeSpec(c2);
    ASSERT_EQ(c2.species.symbol,c1.species.symbol);
}
TEST(Creature, changeSpec_2)
{
    Creature c1(Species('s'));
    Creature c2(Species('t'));
    c1.changeSpec(c2);
    ASSERT_EQ(c1.pc, 0);
}
TEST(Creature, changeSpec_3)
{
    Creature c1(Species('s'));
    Creature c2(Species('t'));
    c1.changeSpec(c2);
    ASSERT_EQ(c1.pc, 0);
}
//ask
TEST(Creature, ask_1)
{
  	Creature c(Species('s'));
    c.species.add_instruction(HOP);
    Instruction i = c.ask();
    ASSERT_EQ(i.command ,HOP);
}
TEST(Creature, ask_2)
{
  	Creature c(Species('s'));
    c.species.add_instruction(LEFT);
    Instruction i = c.ask();
    ASSERT_EQ(i.command ,LEFT);
}

TEST(Creature, ask_3)
{
  	Creature c(Species('s'));
    c.species.add_instruction(GO);
    Instruction i = c.ask();
    ASSERT_EQ(i.command ,GO);
}
//tell
TEST(Creature, tell_1)
{
	Creature c(Species('f'));
    c.tell(Instruction(HOP), true);
    ASSERT_EQ(c.pc,0);
}
TEST(Creature, tell_2)
{
	Creature c(Species('s'));
    c.pc = 100;
    c.tell(Instruction(GO, 0), true);
    ASSERT_EQ(c.pc,0);
}
TEST(Creature, tell_3)
{
	Creature c(Species('r'));
    c.tell(Instruction(HOP), true);
    ASSERT_EQ(c.pc,0);
}
//printboard
TEST(Darwin, printboard_1)
{
    Darwin d(1,1);
    Creature c(Species('s'));
    d.add_creature(c, NORTH, 0, 0);
    ostringstream o;
    d.print_board(0, o);
    ASSERT_EQ(strcmp(o.str().c_str(), "Turn = 0.\n  0\n0 s\n"),0);
}
TEST(Darwin, printboard_2)
{
    Darwin d(1,1);
    ostringstream o;
    d.print_board(0, o);
    ASSERT_EQ(strcmp(o.str().c_str(), "Turn = 0.\n  0\n0 .\n"),0);
}
TEST(Darwin, printboard_3)
{
    Darwin d(1,1);
    Creature c(Species('s'));
    d.add_creature(c, NORTH, 0, 0);
    ostringstream o;
    d.print_board(0, o);
    ASSERT_EQ(strcmp(o.str().c_str(), "Turn = 0.\n  0\n0 s\n"),0);
}

