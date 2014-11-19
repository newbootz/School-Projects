#!/usr/bin/env python3

# -------------------------------
# projects/collatz/TestCollatz.py
# Copyright (C) 2014
# Glenn P. Downing
# -------------------------------

"""
To test the program:
    % coverage3 run --branch TestCollatz.py

To obtain coverage of the test:
    % coverage3 report -m
"""

# -------
# imports
# -------

from io       import StringIO
from unittest import main, TestCase

from Collatz import collatz_read, collatz_eval, collatz_print, collatz_solve

# -----------
# TestCollatz
# -----------

class TestCollatz (TestCase) :
    # ----
    # read
    # ----

    def test_read_1 (self) :
        r    = StringIO("1 10\n100 200\n201 210\n900 1000\n")
        i, j = collatz_read(r)
        self.assertEqual(i,  1)
        self.assertEqual(j, 10)

    def test_read_2 (self): # my tests(2) for testing collatz_read
        r    = StringIO("1 1\n")
        i, j = collatz_read(r)
        self.assertEqual(i,1)
        self.assertEqual(j,1)

    # ----
    # eval
    # ----

    def test_eval_1 (self) :
        v = collatz_eval(1, 10)
        self.assertEqual(v, 20)

    def test_eval_2 (self) :
        v = collatz_eval(100, 200)
        self.assertEqual(v, 125)

    def test_eval_3 (self) :
        v = collatz_eval(201, 210)
        self.assertEqual(v, 89)

    def test_eval_4 (self) :
        v = collatz_eval(900, 1000)
        self.assertEqual(v, 174)

    def test_eval_5 (self) : #my tests(5-11) for testing collatz_eval
        v = collatz_eval(1, 1000)
        self.assertEqual(v, 179)

    def test_eval_6 (self):
        v = collatz_eval(1, 10000)
        self.assertEqual(v, 262)

    def test_eval_7 (self):
        v = collatz_eval(5000, 10000)
        self.assertEqual(v, 262)

    def test_eval_8 (self):
        v = collatz_eval(800, 1000)
        self.assertEqual(v, 179)

    def test_eval_9 (self):
        v = collatz_eval(700, 1000)
        self.assertEqual(v, 179)

    def test_eval_10 (self):
        v = collatz_eval(1, 5000)
        self.assertEqual(v, 238)
    def test_eval_11 (self):
        v = collatz_eval(10, 1)
        self.assertEqual(v, 20)


    # -----
    # print
    # -----

    def test_print_1 (self) :
        w = StringIO()
        collatz_print(w, 1, 10, 20)
        self.assertEqual(w.getvalue(), "1 10 20\n")

    def test_print_2 (self) : #my tests(2-3) for testing collatz_print
        w = StringIO()
        collatz_print(w, 1, 1000000, 525)
        self.assertEqual(w.getvalue(), "1 1000000 525\n")

    def test_print_3 (self) :
        w = StringIO()
        collatz_print(w, 1, 10000, 262)
        self.assertEqual(w.getvalue(), "1 10000 262\n")

    # -----
    # solve
    # -----

    def test_solve_1 (self) :
        r = StringIO("1 10\n100 200\n201 210\n900 1000\n")
        w = StringIO()
        collatz_solve(r, w)
        self.assertEqual(w.getvalue(), "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n")

    def test_solve_2 (self) : #my tests(2-5) for testing collatz_solve
        r = StringIO("5000 7000\n1 500\n1 1000\n1 1000\n")
        w = StringIO()
        collatz_solve(r,w)
        self.assertEqual(w.getvalue(), "5000 7000 262\n1 500 144\n1 1000 179\n1 1000 179\n")

    def test_solve_3 (self) :
        r = StringIO("1 5000\n")
        w = StringIO()
        collatz_solve(r,w)
        self.assertEqual(w.getvalue(), "1 5000 238\n")
    def test_solve_4 (self) :
        r = StringIO("800 1000\n700 1000\n600 1000\n")
        w = StringIO()
        collatz_solve(r,w)
        self.assertEqual(w.getvalue(), "800 1000 179\n700 1000 179\n600 1000 179\n")
    def test_solve_5 (self ) :
        r = StringIO("10 1\n")
        w = StringIO()
        collatz_solve(r,w)
        self.assertEqual(w.getvalue(), "10 1 20\n")

# ----
# main
# ----

main()

"""
% coverage3 run --branch TestCollatz.py
FFFF..F
======================================================================
FAIL: test_eval_1 (__main__.TestCollatz)
----------------------------------------------------------------------
Traceback (most recent call last):
  File "TestCollatz.py", line 47, in test_eval_1
    self.assertEqual(v, 20)
AssertionError: 1 != 20

======================================================================
FAIL: test_eval_2 (__main__.TestCollatz)
----------------------------------------------------------------------
Traceback (most recent call last):
  File "TestCollatz.py", line 51, in test_eval_2
    self.assertEqual(v, 125)
AssertionError: 1 != 125

======================================================================
FAIL: test_eval_3 (__main__.TestCollatz)
----------------------------------------------------------------------
Traceback (most recent call last):
  File "TestCollatz.py", line 55, in test_eval_3
    self.assertEqual(v, 89)
AssertionError: 1 != 89

======================================================================
FAIL: test_eval_4 (__main__.TestCollatz)
----------------------------------------------------------------------
Traceback (most recent call last):
  File "TestCollatz.py", line 59, in test_eval_4
    self.assertEqual(v, 174)
AssertionError: 1 != 174

======================================================================
FAIL: test_solve (__main__.TestCollatz)
----------------------------------------------------------------------
Traceback (most recent call last):
  File "TestCollatz.py", line 78, in test_solve
    self.assertEqual(w.getvalue(), "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n")
AssertionError: '1 10 1\n100 200 1\n201 210 1\n900 1000 1\n' != '1 10 20\n100 200 125\n201 210 89\n900 1000 174\n'
- 1 10 1
?      ^
+ 1 10 20
?      ^^
- 100 200 1
+ 100 200 125
?          ++
- 201 210 1
?         ^
+ 201 210 89
?         ^^
- 900 1000 1
+ 900 1000 174
?           ++


----------------------------------------------------------------------
Ran 7 tests in 0.004s

FAILED (failures=5)



% coverage3 report -m
Name           Stmts   Miss Branch BrMiss  Cover   Missing
----------------------------------------------------------
Collatz          18      0      6      0   100%
TestCollatz      33      1      0      0    97%   86
----------------------------------------------------------
TOTAL            51      1      6      0    98%
"""
