#!/usr/bin/env python3

# ------------------------------
# projects/collatz/RunCollatz.py
# Copyright (C) 2014
# Glenn P. Downing
# ------------------------------

"""
To run the program
    % coverage3 run --branch RunCollatz.py < RunCollatz.in

To obtain coverage of the run:
    % coverage3 report -m

To document the program
    % pydoc -w Collatz
"""

# -------
# imports
# -------

import sys

from Collatz import collatz_solve

# ----
# main
# ----

collatz_solve(sys.stdin, sys.stdout)

"""
% coverage3 run --branch RunCollatz.py < RunCollatz.in > RunCollatz.out



% coverage3 report -m
Name          Stmts   Miss Branch BrMiss  Cover   Missing
---------------------------------------------------------
Collatz         18      0      6      0   100%
RunCollatz       5      0      0      0   100%
---------------------------------------------------------
TOTAL           23      0      6      0   100%
"""
