#!/usr/bin/env python3


# -------
# imports
# -------

"""
To test the program:
    % coverage3 run --branch TestNetflix.py

To obtain coverage of the test:
    % coverage3 report -m
"""


import math
from io       import StringIO
from unittest import main, TestCase

from Netflix import netflix_read, netflix_eval, netflix_print, netflix_solve, sqre_diff, rmse

# -----------
# TestNetflix
# -----------

class TestNetflix (TestCase) :

	# ----
    # read
    # ----
    def test_read_1 (self) : #movie number with next line
        r    = StringIO("2043:\n")
        movie_1 = netflix_read(r)
        self.assertEqual(movie_1,  -2043)

    def test_read_2 (self) : #customer number with next line
        r    = StringIO("2043\n")
        cust_1 = netflix_read(r)
        self.assertEqual(cust_1,  2043)

    def test_read_3 (self) : #movie number without next line
        r    = StringIO("2043:")
        movie_1 = netflix_read(r)
        self.assertEqual(movie_1,  -2043)

    def test_read_4 (self) : #movie number without next line 
        r    = StringIO("462685")
        cust_1 = netflix_read(r)
        self.assertEqual(cust_1,  462685)


    # ----
    # eval
    # ----
    
    def test_eval_1 (self) :
        movie_number = 7464
        customer_list = [1417435,2312054] #two customers
        customer_data = {"1417435" : 2.65, "2312054" : 4.65}
        movie_data = {"7464": [2.65, 1.0, 200]}
        actual_ratings = {"7464-1417435": 4, "7464-2312054": 4 }
        rmse_data = [0.0, 0]
        print_data = []

        netflix_eval(movie_number, customer_list, customer_data, movie_data, actual_ratings, rmse_data, print_data)
    
        self.assertEqual(print_data[0], "7464:") #movie number
        self.assertEqual(print_data[1], 1.6) #first prediction
        self.assertEqual(print_data[2], 3.7) #second prediction
        self.assertEqual(rmse_data[1], 2) #customer count for rmse

    def test_eval_2 (self) :
        movie_number = 7464
        customer_list = [1417435,2312054, 1417435,2312054] # four customers
        customer_data = {"1417435" : 2.65, "2312054" : 4.65}
        movie_data = {"7464": [2.65, 1.0, 200]}
        actual_ratings = {"7464-1417435": 4, "7464-2312054": 4 }
        rmse_data = [0.0, 0]
        print_data = []

        netflix_eval(movie_number, customer_list, customer_data, movie_data, actual_ratings, rmse_data, print_data)
        
        self.assertEqual(print_data[0], "7464:") #movie number
        self.assertEqual(print_data[1], 1.6) #first prediction
        self.assertEqual(print_data[2], 3.7) #second prediction
        self.assertEqual(print_data[1], 1.6) #third prediction
        self.assertEqual(print_data[2], 3.7) #fourth prediction
        self.assertEqual(rmse_data[1], 4) #customer count for rmse

    def test_eval_3 (self):
        movie_number = 0
        customer_list = [1417435,2312054] #two customers
        customer_data = {"1417435" : 2.65, "2312054" : 4.65}
        movie_data = {"7464": [2.65, 1.0, 200]}
        actual_ratings = {"7464-1417435": 4, "7464-2312054": 4 }
        rmse_data = [0.0, 0]
        print_data = []

        netflix_eval(movie_number, customer_list, customer_data, movie_data, actual_ratings, rmse_data, print_data)
    
        self.assertEqual(print_data[0], "0:") #movie number
        self.assertEqual(rmse_data[1], 0) #customer count for rmse

    def test_eval_4 (self) :
        movie_number = 7464
        customer_list = [10101 , 101010] #two customers
        customer_data = {"1417435" : 2.65, "2312054" : 4.65}
        movie_data = {"7464": [2.65, 1.0, 200]}
        actual_ratings = {"7464-1417435": 4, "7464-2312054": 4 }
        rmse_data = [0.0, 0]
        print_data = []

        netflix_eval(movie_number, customer_list, customer_data, movie_data, actual_ratings, rmse_data, print_data)
    
        self.assertEqual(print_data[0], "7464:") #movie number
        self.assertEqual(rmse_data[1], 0.0) #customer count for rmse

    
    # ----
    # print
    # ----
    def test_print_1 (self) :
        w = StringIO()
        print_data = ["2043:", 1.5, "4014:", 2.5] #two sets
        rms_error = .9999
        netflix_print(w, print_data, rms_error)
        self.assertEqual(w.getvalue(), "2043:\n1.5\n4014:\n2.5\nRMSE:0.9999\n")

    def test_print_2 (self): #one set
        w = StringIO()
        print_data = ["2043:", 1.5, 4.5]
        rms_error = .8501
        netflix_print(w, print_data, rms_error)
        self.assertEqual(w.getvalue(), "2043:\n1.5\n4.5\nRMSE:0.8501\n")

    def test_print_3 (self): #no predictions
        w = StringIO()
        print_data = ["2043:"]
        rms_error = .8501
        netflix_print(w, print_data, rms_error)
        self.assertEqual(w.getvalue(), "2043:\nRMSE:0.8501\n")

    def test_print_4 (self) : #no movie number
        w = StringIO()
        print_data = [1.5, 4.5]
        rms_error = .8501
        netflix_print(w, print_data, rms_error)
        self.assertEqual(w.getvalue(), "1.5\n4.5\nRMSE:0.8501\n")
   
    # ----
    # solve
    # ----
    def test_solve_1 (self) :
        r = StringIO("2043:\n1417435\n2312054") #one set
        w = StringIO()
        netflix_solve(r, w)
        self.assertEqual(w.getvalue(), "2043:\n3.6\n4.6\nRMSE:2.5807\n")

    def test_solve_2 (self) :
        r = StringIO("2043:\n1417435\n2312054\n2043:\n1417435\n2312054") #two sets
        w = StringIO()
        netflix_solve(r, w)
        self.assertEqual(w.getvalue(), "2043:\n3.6\n4.6\n2043:\n3.6\n4.6\nRMSE:2.5807\n")

    def test_solve_3 (self) : #
        r = StringIO("2043:\n1417435\n2312054\n2043:\n1417435\n2312054\n2043:") #two sets and an incomplete
        w = StringIO()
        netflix_solve(r, w)
        self.assertEqual(w.getvalue(), "2043:\n3.6\n4.6\n2043:\n3.6\n4.6\n2043:\nRMSE:2.5807\n")

    def test_solve_4 (self): 
        r = StringIO("")
        w = StringIO()
        netflix_solve(r,w)
        self.assertEqual(w.getvalue(),"RMSE:0.0\n")


    # ----
    # sqre_diff
    # ----
    def test_sqre_diff_1(self) :
        sqrd = sqre_diff(1, 2)
        self.assertEqual(sqrd, 1)

    def test_sqre_diff_2(self) :
        sqrd = sqre_diff(2, 2)
        self.assertEqual(sqrd, 0)

    def test_sqre_diff_3(self) :
        sqrd = sqre_diff(0, 2)
        self.assertEqual(sqrd, 4)

    # ----
    # rmse
    # ----
    def test_rmse_1(self) :
        data = [1, 1]
        rms_error = rmse(data)
        self.assertEqual(rms_error, 1)

    def test_rmse_2(self) :
        data = [4, 2]
        rms_error = rmse(data)
        self.assertEqual(rms_error, math.sqrt(2))

    def test_rmse_3 (self) :
        data = [5, 2]
        rms_error = rmse(data)
        self.assertEqual(rms_error, math.sqrt(5/2))



# ----
# main
# ----
main()

