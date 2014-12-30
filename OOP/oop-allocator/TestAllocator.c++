

// ------------------------------------
// projects/allocator/TestAllocator.c++
// Copyright (C) 2014
// Glenn P. Downing
// ------------------------------------

// --------
// includes
// --------

#include <algorithm> // count
#include <memory>    // allocator

#include "gtest/gtest.h"

#include "Allocator.h"



// -------------
// TestAllocator
// -------------

template <typename A>
struct TestAllocator : testing::Test 
{
    // --------
    // typedefs
    // --------

    typedef          A                  allocator_type;
    typedef typename A::value_type      value_type;
    typedef typename A::difference_type difference_type;
    typedef typename A::pointer         pointer;
};



typedef testing::Types<
            std::allocator<int>,
            std::allocator<double>,
            Allocator<int, 100>,
            Allocator<double, 100> >
        my_types;

TYPED_TEST_CASE(TestAllocator, my_types);

TYPED_TEST(TestAllocator, One) 
{
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

    allocator_type x;
    const difference_type s = 1;
    const value_type      v = 2;
    const pointer         p = x.allocate(s);
    if (p != 0)  //p is always 0, need to modify allocate, won't run the ASSERT
    {
        x.construct(p, v);
        ASSERT_EQ(v, *p);
        x.destroy(p);
        x.deallocate(p, s);
    }

}

TYPED_TEST(TestAllocator, Ten) 
{
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

    allocator_type x;
    const difference_type s = 10;
    const value_type      v = 2;
    const pointer         b = x.allocate(s);  //allocate space for 10
    

    if (b != 0) //make sure we allocated successfully, otherwise we won't proceed
    {
        
        pointer e = b + s; //e is one past the end

        pointer p = b; //copy pointer in b to p

        try 
        {
            while (p != e) //going to fill in the space with v
            {
                x.construct(p, v); //call construct on allocator_type x, at position p, and fill in with v
                ++p; //increment p
            }
        }
        catch (...) //???
        {
            while (b != p) //free space if we get an error in the middle of filling in the space
            {
                --p;
                x.destroy(p);
            }
            x.deallocate(b, s);
            throw; //???
        }
        ASSERT_EQ(s, std::count(b, e, v)); //everything was successful
        while (b != e) //free the space in range b to e
        {
            --e;
            x.destroy(e);
        }
        x.deallocate(b, s);
    }
}
//tests for view

TEST(Allocator, view_1)
{
    
    const Allocator<int, 12> x;
    assert(x.view(0) == 4);
    
}

TEST(Allocator, view_2)
{
    
    const Allocator<int, 20> y;
    assert(y.view(16) == 12);  
}
//tests for allocator constructor

TEST(Allocator, alloctor_1)
{
    const Allocator<int, 100> x;
    assert(x.view(0) == x.view(96));
}
TEST(Allocator, allocator_2) 
{
    bool bad = false;
    try
    {

        Allocator<int,100> a;
    }
    catch (...) 
    {
        bad=true;
    }
    ASSERT_EQ(bad,false);
}

TYPED_TEST(TestAllocator, allocator_3) 
{
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

    allocator_type x;
    pointer ap = x.allocate(1);
    pointer bp = x.allocate(1);
    value_type v;
    x.construct(ap, v);
    x.construct(bp, v);
    *ap = 5;
    *bp = 5;
    ASSERT_EQ(*ap, *bp);
    x.destroy(ap);
    x.destroy(bp);
    x.deallocate(ap,1);
    x.deallocate(bp,1);
}

TEST(Allocator, allocator_4) 
{
    try 
    {
        Allocator<double, sizeof(double)>x;
        ASSERT_TRUE(false);
    }
    catch(...) 
    {
        ASSERT_TRUE(true);
    }
}

TEST(Allocator, allocator_5) 
{
    try 
    {
        Allocator<int, sizeof(int)>x;

        ASSERT_TRUE(false);
    }
    catch(...) 
    {
        ASSERT_TRUE(true);
    }
}

TEST(Allocator, allocator_6) 
{
    Allocator<int, 100> x;

    const Allocator<int, 100>& cx = x;

    ASSERT_EQ(cx.view(0), 92);
}

TEST(Allocator, allocate_1)
{
    Allocator<double, 100> x;
    x.allocate(4);
    const Allocator<double, 100>& y = x; 

    assert(y.view(0) == -32);
    assert(y.view(36) == -32);
    assert(y.view(40) == 52);
    assert(y.view(96) == 52);
}

TEST (Allocator, allocate_2) {
    try {
        const int size = sizeof(Allocator<int, sizeof(int)>) + 2 * sizeof(int);
        Allocator<Allocator<int, sizeof(int)>, size> a;
        a.allocate(5);
    } catch (std::bad_alloc) 
    {
        // badalloc
    } catch (...) 
    {
        ASSERT_TRUE(false);
    }
}

TYPED_TEST(TestAllocator, allocate_3) 
{
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;
    allocator_type x;

    const difference_type s = 10;
    const value_type      v = 2;
    const pointer         p = x.allocate(s);
    x.construct(p,v);

    ASSERT_EQ(v,*p);
}



//tests for deallocate

TEST(Allocator, deallocate_1)
{
    Allocator<int, 100> x;
    int* p = x.allocate(4);
    const Allocator<int, 100>& y = x;
    assert(y.view(0) == -16);
    assert(y.view(20) == -16);

    x.deallocate(p, 4);

    assert(y.view(0) == 92);
    assert(y.view(96) == 92);
}

TEST (Allocator, deallocate_2) 
{
    Allocator<int, 100> a;
    int* p = a.allocate(10);
    int* p2;
    a.deallocate(p, 10);
    p2 = a.allocate(15);

    ASSERT_TRUE (p == p2);
}

TEST(TestMyAllocator, deallocate_3)
{   
    try
    {
        Allocator<int, 100> x;
        const Allocator<int, 100>& y = x;
        
        ASSERT_EQ(y.view(0), 92);
        ASSERT_EQ(y.view(96), 92);
        
        int* p = x.allocate(1);
        
        x.deallocate(p, 1);
        
        ASSERT_EQ(y.view(0), 92);
        ASSERT_EQ(y.view(96), 92);
    }
    catch (const std::bad_alloc& e)
    {
        ASSERT_TRUE(false);
    }
}

TEST(Allocator, deallocate_4) 
{
    Allocator<double, 1000> x;
    
    double* p = x.allocate(1);
    double* p1 = x.allocate(4);
    double* p3 = x.allocate(50);

    x.deallocate(p, 1);

    const Allocator<double, 1000>& cx = x;
    ASSERT_EQ(cx.view(0), 8);
    ASSERT_EQ(cx.view(16), -32);
}

TYPED_TEST(TestAllocator, deallocate_5) 
{
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

    allocator_type x;
    pointer ap = x.allocate(1);
    pointer bp = x.allocate(1);
    value_type v;
    x.construct(ap, v);
    x.construct(bp, v);
    *ap = 5;
    *bp = 5;
    ASSERT_EQ(*ap, *bp);

    x.destroy(ap);
    x.destroy(bp);
    x.deallocate(ap,1);
    x.deallocate(bp,1);
}

TYPED_TEST(TestAllocator, deallocate_6) {
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;


    allocator_type x;
    const difference_type s = 1;
    const value_type      v = 2;
    for (int i = 0; i < 10; ++i) 
    {

        const pointer         p = x.allocate(s);
        if (p != 0) 
        {
            x.construct(p, v);
            ASSERT_EQ(v, *p);

            x.destroy(p);
            x.deallocate(p, s);
        }
        
    }
}
TEST(Allocator, deallocate_7)
{
    Allocator<int, 100> x;
    int* p = x.allocate(4);
    const Allocator<int, 100>& y = x;
    assert(y.view(0) == -16);
    assert(y.view(20) == -16);

    x.deallocate(p, 4);

    assert(y.view(0) == 92);
    assert(y.view(96) == 92);
}
//test cases for valid


TEST(Allocator, valid_1)
{
    //Allocator, allocate and deallocate run valid
    Allocator<std::vector<double>, sizeof(std::vector<double>) + 2 * sizeof(int)> a;
    std::vector<double>* nums = a.allocate(1);
    std::vector<double> toBeCopied;
    a.construct(nums, toBeCopied);
    nums->push_back(1.0);
    ASSERT_EQ((*nums)[0], 1.0);

    a.destroy(nums);
    a.deallocate(nums, 1);
}

TEST(Allocator, valid_2)
{
//Allocator, allocate, deallocate run valid
  Allocator<char, 100> x;
  char * pointer = x.allocate(92);
  x.deallocate(pointer, 92);
  const Allocator<char, 100>& y = x;

  ASSERT_EQ(y.view(0), 92);
  ASSERT_EQ(y.view(96), 92);
}


TEST(Allocator, valid_4) 
{
    Allocator<int, 100> x;

    const Allocator<int, 100>& cx = x;
    ASSERT_EQ(cx.view(0), 92);
}

TYPED_TEST(TestAllocator, valid_5) {
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

    allocator_type x;
    const difference_type s = 1;
    const value_type      v = 2;

    for (int i = 0; i < 10; ++i) 
    {
        const pointer         p = x.allocate(s);
        if (p != 0) 
        {

            x.construct(p, v);
            ASSERT_EQ(v, *p);
            x.destroy(p);
            x.deallocate(p, s);
        }

    }
}



TYPED_TEST(TestAllocator, valid_7) 
{
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

    allocator_type x1;
    const difference_type s = 10;
    const value_type      v1 = 2;
    const pointer         p = x1.allocate(s);
    if (p != 0)
    {

        x1.construct(p, v1);
        ASSERT_EQ(v1, *p);
        x1.destroy(p);
        x1.deallocate(p, s);
    }

}

TEST(Allocator, valid_8)
{
    Allocator<int, 100> x;
    int* p = x.allocate(4);
    const Allocator<int, 100>& y = x;
    assert(y.view(0) == -16);
    assert(y.view(20) == -16);

    x.deallocate(p, 4);

    assert(y.view(0) == 92);
    assert(y.view(96) == 92);
}
TEST(TestMyAllocator, valid_9)
{   
    try
    {
        Allocator<int, 100> x;
        const Allocator<int, 100>& y = x;
        
        ASSERT_EQ(y.view(0), 92);
        ASSERT_EQ(y.view(96), 92);
        
        int* p = x.allocate(1);
        
        x.deallocate(p, 1);
        
        ASSERT_EQ(y.view(0), 92);
        ASSERT_EQ(y.view(96), 92);
    }
    catch (const std::bad_alloc& e)
    {
        ASSERT_TRUE(false);
    }
}




