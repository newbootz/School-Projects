#include <stdexcept>
#include <sstream>
#include "gtest/gtest.h"
#define private public
#define protected public
#include "Life.h"


using namespace std;

TEST(AbstractCell, a1)
{
    ConwayCell cc;
    ASSERT_TRUE(cc.liveness() == false);
}
TEST(AbstractCell, a2)
{
    FredkinCell fc;
    ASSERT_TRUE(fc.liveness() == false);
}
TEST(AbstractCell, a3)
{
    Cell c;
    ASSERT_TRUE(c.liveness()==false);
}
TEST(ConwayCell, clone_1)
{
    ConwayCell cc;
    AbstractCell* ac = cc.clone();
    ASSERT_TRUE(dynamic_cast<ConwayCell*>(ac) != &cc);
}
TEST(FredkinCell, clone_1)
{
    FredkinCell cc;
    AbstractCell* ac = cc.clone();
    ASSERT_TRUE(dynamic_cast<FredkinCell*>(ac) != &cc);
}
TEST(FredkinCell, ns1)
{
    FredkinCell fc;
    fc.new_state('0');
    ASSERT_TRUE(fc.liveness() == true);
}
TEST(ConwayCell, ns2)
{
    ConwayCell cc;
    cc.new_state('*');
    ASSERT_TRUE(cc.liveness()==true);
}
TEST(FredkinCell, ns3)
{
    FredkinCell fc;
    fc.new_state('0');
    ASSERT_TRUE(fc.liveness());
}
TEST(ConwayCell, ns4)
{
    ConwayCell cc;
    cc.new_state('0');
    ASSERT_TRUE(cc.liveness());
}
TEST(ConwayCell, evolve1)
{
    ConwayCell cc;
    for(int i = 0; i < 5; ++i)
    {
        cc.new_state('*');
        cc.evolve(i);
        if(i == 2 || i == 3)
        {
            ASSERT_TRUE(cc.liveness() == true);
        }
        else
        {
            ASSERT_TRUE(cc.liveness() == false);
        }
        
    }
    
}
TEST(ConwayCell, evolve5)
{
    ConwayCell cc;
    for(int i = 0; i < 5; ++i)
    {
        cc.new_state('.');
        cc.evolve(i);
        if(i == 3)
        {
            ASSERT_TRUE(cc.liveness() == true);
        }
        else
        {
            ASSERT_TRUE(cc.liveness() == false);
        }
        
    }
}
TEST(FredkinCell, evolve2)
{
    FredkinCell fc;
    
    for(int i=0; i < 5; ++i)
    {
        fc.new_state('0');
        fc.evolve(i);
        if(i == 1 || i == 3)
        {
            ASSERT_TRUE(fc.liveness() == true);
        }
        else
        {
            ASSERT_TRUE(fc.liveness() == false);
        }
    }
}
TEST(FredkinCell, evolve3)
{
    FredkinCell fc;
    
    for(int i=0; i < 5; ++i)
    {
        fc.new_state('-');
        fc.evolve(i);
        if(i == 1 || i ==  3)
        {
            ASSERT_TRUE(fc.liveness() == true);
        }
        else
        {
            ASSERT_TRUE(fc.liveness() == false);
        }
    }
}
TEST(Cell, evolve4)
{
    Cell c;
    
    for(int i=0; i < 5; ++i)
    {
        c.new_state('0');
        c.evolve(i);
        if(i == 1 || i ==  3)
        {
            ASSERT_TRUE(c.liveness() == true);
        }
        else
        {
            ASSERT_TRUE(c.liveness() == false);
        }
    }

}
TEST(Cell, evolve6)
{
    Cell c;
    
    for(int i=0; i < 5; ++i)
    {
        c.new_state('-');
        c.evolve(i);
        if(i == 1 || i ==  3)
        {
            ASSERT_TRUE(c.liveness() == true);
        }
        else
        {
            ASSERT_TRUE(c.liveness() == false);
        }
    }
}
TEST(Cell, evolve7)
{
     Cell c;
    
    for(int i=0; i < 5; ++i)
    {
        c.new_state('*');
        c.evolve(i);
        if(i == 2 || i ==  3)
        {
            ASSERT_TRUE(c.liveness() == true);
        }
        else
        {
            ASSERT_TRUE(c.liveness() == false);
        }
    }
}
TEST(Cell, evolve8)
{
       Cell c;
    
    for(int i=0; i < 5; ++i)
    {
        c.new_state('.');
        c.evolve(i);
        if(i ==  3)
        {
            ASSERT_TRUE(c.liveness() == true);
        }
        else
        {
            ASSERT_TRUE(c.liveness() == false);
        }
    }
}
TEST(ConwayCell, print1)
{
    ConwayCell cc;
    cc.new_state('*');
    ASSERT_TRUE(cc.print() == '*');
}
TEST(ConwayCell, print2)
{
    ConwayCell cc;
    ASSERT_TRUE(cc.print() == '.');
}
TEST(FredkinCell, print3)
{
    FredkinCell fc;
    ASSERT_TRUE(fc.print() == '-');
}
TEST(FredkinCell, print4)
{
    FredkinCell fc;
    fc.new_state('0');
    ASSERT_TRUE(fc.print() == '0');
}
TEST(FredkinCell, print5)
{
    FredkinCell fc;
    fc.new_state('9');
    fc.evolve(1);
    ASSERT_TRUE(fc.print() == '+');
}
TEST(Cell, print6)
{
    Cell c;
    ASSERT_TRUE(c.print() == '-');
}
TEST(Cell, print7)
{
    Cell c;
    c.new_state('0');
    ASSERT_TRUE(c.print() == '0');
}
TEST(Cell, print8)
{
    Cell c;
    c.new_state('1');
    c.evolve(1);
    ASSERT_TRUE(c.print() == '*');
}
TEST(ConwayCell, n)
{
    ConwayCell cc;
    ASSERT_TRUE(cc.neighbors(-1,-1));
}
TEST(ConwayCell, n2)
{
    ConwayCell cc;
    ASSERT_TRUE(cc.neighbors(0,1));
}
TEST(ConwayCell, n3)
{
    ConwayCell cc;
    ASSERT_TRUE(cc.neighbors(1,1));
}
TEST(FredkinCell, n4)
{
    FredkinCell cc;
    ASSERT_TRUE(cc.neighbors(-1,-1) == false);
}
TEST(FredkinCell, n5)
{
    FredkinCell cc;
    ASSERT_TRUE(cc.neighbors(0,1) == true);
}
TEST(FredkinCell, n6)
{
    FredkinCell cc;
    ASSERT_TRUE(cc.neighbors(-1,-1) == false);
}
TEST(FredkinCell, n7)
{
     FredkinCell cc;
    ASSERT_TRUE(cc.neighbors(1,1) == false);

}
TEST(Cell, n8)
{
    Cell c;
    ASSERT_TRUE(c.neighbors(-1,-1) == false);
}
TEST(Cell, n9)
{
    Cell c;
    ASSERT_TRUE(c.neighbors(0, 1) == true);
}
TEST(Cell, n10)
{
    Cell c;
    ASSERT_TRUE(c.neighbors(1,1) == false);
}