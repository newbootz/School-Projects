// ------------------------------
// projects/allocator/Allocator.h
// Copyright (C) 2014
// Glenn P. Downing
// ------------------------------

#ifndef Allocator_h
#define Allocator_h

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstddef>   // ptrdiff_t, size_t
#include <new>       // bad_alloc, new
#include <stdexcept> // invalid_argument

// ---------
// Allocator
// ---------

template <typename T, int N> 
class Allocator {
    public:
        // --------
        // typedefs
        // --------

        typedef T                 value_type; //generic type T

        typedef std::size_t       size_type; 
        typedef std::ptrdiff_t    difference_type; 

        typedef       value_type*       pointer;
        typedef const value_type* const_pointer;

        typedef       value_type&       reference;
        typedef const value_type& const_reference;

    public:
        // -----------
        // operator ==
        // -----------

        friend bool operator == (const Allocator&, const Allocator&) 
        {
            return true;
        }                                              // this is correct

        // -----------
        // operator !=
        // -----------

        friend bool operator != (const Allocator& lhs, const Allocator& rhs) 
        {
            return !(lhs == rhs);
        }

    private:


        // ----
        // data
        // ----

        char a[N]; //number of bytes N

        // -----
        // valid
        // -----

        /**
         * O(1) in space
         * O(n) in time

         * makes sure that our "heap" is always in a proper state
         returns true if sentinnels are valid, false otherwise
         */
       bool valid () const 
       {
            int* p = (int*)a; //beginning of a

            while((char*)p < (a + N - 4)) //keep iterating until the last sentinel
            {
                int block_size = abs(*p); //get the block size by reading value of block's left sentinel
                p =(int*)( ((char* )p) +block_size +4); //go to the right sentinel 
                if(abs(*p) != block_size) //make sure that right and left blocks have same value
                {
                    return false;
                }
                p = (int*)(((char*) p)+4); //go to the sentinel of the next block
            }
            return true; //everything was valid
        }

        // -----
        // view
        // -----
        /**
         * O(1) in space
         * O(1) in time

        returns an integer representation of the value stored at the memory location i
        in our memory
         */
        int& view (int i) 
        {
            return *reinterpret_cast<int*>(&a[i]);
        }
        void set_value(char* p, int v)
        {
             *((int*)(p)) = v;
        }

    public:
        // ------------
        // constructors
        // ------------

        /**
         * O(1) in space
         * O(1) in time

          sets up right and left sentinels to free space (N - 2*sizeof(int) )for this block of memory
          throw a bad_alloc exception, if N is less than sizeof(T) + (2 * sizeof(int))
         */
        Allocator () 
        {
            using namespace std;
            int s_size = (2* sizeof(int));
            if(N < sizeof(T) + s_size) // throw a bad_alloc exception, if N is less than sizeof(T) + (2 * sizeof(int))
            {
                throw bad_alloc();
            }

            int * p = (int*)a; //location of left sentinel
            *p = N - s_size; //set left sentinel to free space
            p = (int*)(a+N-4); //location of right sentinel
            *p = N - s_size; //set right sentinel

            assert(valid());
        }
             
        // Default copy, destructor, and copy assignment
        // Allocator  (const Allocator&);
        // ~Allocator ();
        // Allocator& operator = (const Allocator&);

        // --------
        // allocate
        // --------

        /**
         * O(1) in space
         * O(n) in time
         * after allocation there must be enough space left for a valid block
         * the smallest allowable block is size minimum_space <sizeof(T) + (2 * sizeof(int))>
         * choose the first block that fits
         * throw a bad_alloc exception, if allocation fails
         */
        
pointer allocate (size_type n) 
 {
    using namespace std;
    char* p = a; //get beginning of array
    int sentinels_size = (2 * sizeof(int)); //size of two sentinels (left, and right)
    int minimum_space = sizeof(T) + sentinels_size; //left over space must be at least the minimum_space size
    int requested_bytes = n*sizeof(T); //calculate number of bytes for this allocation   
    char* eos = a+N-4; //last sentinel address

    while(p < eos)//loop until the last sentinel
    {
        
        int sent_val = *((int*)p); //get the value of this sentinel
        if(requested_bytes +sentinels_size <= sent_val) //check if there's enough space to hold n bytes plus sentinels
        {   
            
            if(requested_bytes +minimum_space <= sent_val) //check if there's enough left over space for another free block
            {
                int free_space = (sent_val- requested_bytes) - sentinels_size; //calculate leftover space after allocation
                char* end = p+ sent_val+4; //get right sentinel address, save it as "end"

                *((int*)p) = -1*requested_bytes; //set left sentinel to indicate its being used
                p= p+ requested_bytes +4;
                *((int*)p) = -1*requested_bytes; //set the right sentinel to indicate its being used

                *((int*)end) = free_space; //set the right sentinel of free block to new calculated free space size

                end = p+4;//left sentinel address of free block
                *((int*)end) = free_space; //set to new calculated free space size
                
                assert(valid());
                return (pointer)(p- requested_bytes); //return beginning of new allocated block
                
            }
            else //not enough leftover to form another block, just give them everything thats left
            {
                int size = *((int*)p); 
                *((int*)p)= (-1*size); //set the right most sentinel of free block as being used

                *((int*)(p+size+4)) = (-1*size);//same thing for the left most sentinel
                assert(valid());
                return ((pointer)(p+4)); //return the beginning address of this new allocation
            }
        }
        else
        {
            p = p + abs( *((int*)p) )+sentinels_size;//Can't allocate at this block(being used or too small),move on to next block
        }
        
    }
    if( *((int*)eos) == (int)n*sizeof(T) ) //this block with sentinels fits exactly, zero space left over
    {
        set_value(eos - requested_bytes - 4, -1*requested_bytes); //set the left sentinel
        set_value(eos, -1*requested_bytes); //set the right sentinel
        assert(valid());
        return ((pointer) (eos - requested_bytes)); //return address of beginning of allocation
    }
    assert(valid());
    throw bad_alloc(); //couldn't allocate block of this size
    return 0; 
 }
         
        // ---------
        // construct
        // ---------

        /**
         * O(1) in space
         * O(1) in time

         * construct is putting value v into memory 
         where p is pointing, by invoking copy constructor

         */
        void construct (pointer p, const_reference v) 
        {
            new (p) T(v);                            // this is correct and exempt
            assert(valid());                     // from the prohibition of new
        }                           

        // ----------
        // deallocate
        // ----------

        /**
         * O(1) in space
         * O(1) in time
         * after deallocation adjacent free blocks must be coalesced

        *Deallocates block of memory at address p, changes sentinels to
        indicated free block, then checks coalesces adjacent free blocks 
        of memory
         */
  
         void deallocate (pointer p, size_type ) {
            char* ls = ((char*)(p))-4; // get the address of left sentinel of this block
            int lsv = *((int*)ls); //get the value of this sentinel
            lsv = -1*lsv; //make positive value
            set_value(ls,lsv); //make the sentinel positive (will indicate free block now)
            char* rs = ((char*)(p))+lsv; //go to address of right block
            set_value(rs,lsv); //set sentinel to indicate its free now
            if((a+4) < ls) //location of this sentinel is not at the beginning of memory, could have neighbor to left
            {
                char* left = ls-4; //check left of this freed block
                if(0 < *((int*)left)) //if its also free, coalesce
                {
                    char* l = left;
                    char* r = ls;
                    char* p = l; 
                    int rv = *((int*)r);
                    int lv = *((int*)l);
                    int new_size = rv + 8 + lv;
                    p = p - lv -4;
                    set_value(p, new_size);
                    p = p+ *((int*)p) +4;
                    set_value(p, new_size);
                }
            }
            
            if(rs < (a+N-4)) //location of sentinel is not at the very end of memory, could have neighbor to right
            {
                char* right = rs +4;
                if(0 < *((int*)right)) //check right of this sentinel, if free, coalesce
                {
                    char* l = rs;
                    char* r = right;
                    char* p = l; 
                    int rv = *((int*)r);
                    int lv = *((int*)l);
                    int new_size = rv + 8 + lv;
                    p = p - lv -4;
                    set_value(p, new_size);
                    p = p+ *((int*)p) +4;
                    set_value(p, new_size);
                }
            }
            assert(valid());
        }

        // -------
        // destroy
        // -------

        /**
         * O(1) in space
         * O(1) in time
         * throw an invalid_argument exception, if pointer is invalid

        *Destroys the allocator object and any objects that may be in it
         */
        void destroy (pointer p) 
        {
            p->~T();               // this is correct
            assert(valid());
        }

        // -------
        // view
        // -------
        /**
         * O(1) in space
         * O(1) in time

        this view method is called by valid, returns
        const of value at position i
         */
        const int& view (int i) const 
        {
            return *reinterpret_cast<const int*>(&a[i]);
        }


        };

#endif // Allocator_h
