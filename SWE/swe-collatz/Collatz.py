#!/usr/bin/env python3

# ---------------------------
# projects/collatz/Collatz.py
# Copyright (C) 2014
# Glenn P. Downing
# ---------------------------

# ------------
# collatz_read
# ------------

def collatz_read (r) :
    """
    read two ints
    r is a reader
    return a list of the two ints, otherwise a list of zeros
    """
    s = r.readline()
    if s == "" :
        return []
    a = s.split()
    return [int(v) for v in a]

# ------------
# collatz_eval
# ------------

def collatz_eval (i, j) :
    """
    i is the beginning of the range, inclusive
    j is the end       of the range, inclusive
    return the max cycle length in the range [i, j]
    """
    # <your code>
    
    cache = [None] * 1000001 #allows direct indexing starting at 1
    try:

        assert(i <= j) #make sure that i is the start, and j is end

        start = i
        end = j
    except:
        if(j < i): #need to pass arguments in correct order
            end = i
            start = j

    if(start < (end>>1)): #if first half of map to second half of the range, cut range in half for less work
        start = (end>>1)

   
    max_clength = 0 #keeps track of highest cycle length
    
    current_num = start #keeps track of the current number whose cycle length being calculated
    
    while ( current_num <= end): #loops through the range calculating cycle lenghts
        
        n = current_num #make a copy of current number for calculations
        clength = 1
        
        while ( 1 < n): #keep calculating until n is 1
            assert (1 < n)
            if((n < 1000001) and (cache[n] != None)): #checks if this value is in the cache
                clength+=(cache[n] - 1)
                n = 1
            elif (n % 2) == 0: #for even n simply divide by 2
                n = (n >> 1)
                clength += 1
           
            else :  #for odd n, 3n +1 / 2 
                n = n + (n>>1) +1
                clength += 2        
        
        if(max_clength < clength): #check if the cycle length for this number is the new max cycle length
            max_clength = clength
        
        cache[current_num] = clength #save the cycle length for this number in cache
        current_num+=1 #cycle length for this number calculated calculating the next one now, increment 

    assert ( 0 < max_clength)

    return max_clength

# -------------
# collatz_print
# -------------

def collatz_print (w, i, j, v) :
    """
    print three ints
    w is a writer
    i is the beginning of the range, inclusive
    j is the end       of the range, inclusive
    v is the max cycle length
    """
    w.write(str(i) + " " + str(j) + " " + str(v) + "\n")

# -------------
# collatz_solve
# -------------

def collatz_solve (r, w) :
    """
    read, eval, print loop
    r is a reader
    w is a writer
    """
    while True :
        a = collatz_read(r)
        if not a :
            return
        i, j = a

        if(i < j): #need to pass arguments in correct order
            start = i
            end = j
        else:
            start = j
            end = i
 
        v = collatz_eval(start, end)
        collatz_print(w, i, j, v)
