#!/usr/bin/env python3


"""
To run the program
    % coverage3 run --branch RunNetflix.py < RunNetflix.in

To obtain coverage of the run:
    % coverage3 report -m

To document the program
    % pydoc -w Netflix
"""

# -------
# imports
# -------

import sys

from Netflix import netflix_solve

# ----
# main
# ----

netflix_solve(sys.stdin, sys.stdout)