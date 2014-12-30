#!/usr/bin/env python3

import json
import math
# ------------
# netflix_read
# ------------
def netflix_read (r) :
	"""
	reads in probe.txt
	through stdin r
	identifies movie numbers
	from customer numbers and
	returns them as such

	"""
	line = r.readline()
	
	if(line == "" or line == "\n"): #nothing to do for blank line
		return

	if ":" in line : #movie number, take off colon, return as negative to indicate its a movie
		return int(line.replace(":", "")) *-1
		
	else:
		return int(line) #return the number



# ------------
# netflix_eval
# ------------
def netflix_eval(movie_number, customer_list, customer_data, movie_data, actual_ratings, rmse_data, print_data):
	"""
	Takes in movie and customer data
	to make a prediction for customer 
	ratings for particular movie
	then calculates rmse based on actual ratings
	"""

	print_data.append(str(movie_number)+":") #add movie number into list of stuff to print out
	try:
		movie_avg = movie_data[str(movie_number)][0] #get movie average for this movie_number from movie_data cache


		for customer_number in customer_list: #for this movie, will make prediction for each customer
			try:
				customer_avg = customer_data[str(customer_number)] #get customer rating average from cache for this customer
				
				answer = actual_ratings[str(movie_number)+"-"+str(customer_number)] #get the correct rating from actual_ratings cache

				prediction = 3.65 + (movie_avg - 3.65) + (customer_avg - 3.65) #make prediction with this algo
				prediction = round(prediction,1) #round the prediction to one decimal place
				rmse_data[0]+=sqre_diff(answer, prediction) #save sum of square difference in rmse data and print data
				print_data.append(prediction)
				rmse_data[1]+= 1
			except:
				pass
		
		#rmse_data[1]+=(len(customer_list)) #save the customer count too
	except:
		#Ignore this movie or customer because it doesn't exist
		return
	

# ------------
# netflix_print
# ------------
def netflix_print(w, print_data, rms_error):
	"""
	given print data and rmse, prints 
	this information to stdout w
	"""
	for line in print_data:
		w.write(str(line)+"\n")
	rmse_line = "RMSE:"+str(round(rms_error, 4))+"\n"
	w.write(rmse_line)

# ------------
# netflix_solve
# ------------
def netflix_solve (r, w) :
	"""
	reads in input r 
	loads caches
	reads input, then evaluates
	outpus to w 
	"""

	rmse_data = [0,0] #sum of differences, customer count

	customer_average_ratings = {} #import customer, movie data, answers, and save it in dictionaries
	movie_average_ratings = {}
	actual_ratings = {}
	print_data = []  #save all the stuff that will be printed in the end (movie number, predictions, rmse)
	rms_error = 0

	with open("/u/mukund/netflix-tests/bryan-customer_cache.json", "r") as f: #customer cache
		customer_average_ratings = json.load(f)

	with open("/u/mukund/netflix-tests/frankc-movie_cache.json", "r") as f: #movie cache
		movie_average_ratings = json.load(f)

	with open("/u/mukund/netflix-tests/osl62-AnswerCache.json", "r") as f: #answer cache
		actual_ratings = json.load(f)





	set_ready = False #indicates if we have a set of data(movie_number, customer_list) ready to process
	movie_info = False 
	customer_info = False

	movie_number = 0 
	customer_list = [] #list to hold customer numbers that need prediction for particular movie
	
	while (True) :

		number = netflix_read(r) #read line from probe.txt
		
		if not number: # if the line is blank, check to see if we have set of data ready
			if(set_ready):
				netflix_eval(movie_number, customer_list, customer_average_ratings, movie_average_ratings, actual_ratings, rmse_data, print_data) #process this set
			break

		if(number < 0): #movie numbers will be negative, check if we have a set of data ready, and set flags
			if(customer_info): #if we read a movie number from before and have customer info, we have a set ready
				netflix_eval(movie_number, customer_list, customer_average_ratings, movie_average_ratings, actual_ratings, rmse_data, print_data) #process set
				customer_info = False #empty the customer_list
				customer_list = []
			movie_number = number * -1 #save new movie number
			movie_info = True

		else: #customer number, add it to the list and set flags
			customer_list.append(number)
			customer_info = True
			if(movie_info):
				set_ready = True

	rms_error = rmse(rmse_data) #calculate rmse
	netflix_print(w, print_data, rms_error) #print movie numbers/predictions and rmse

def sqre_diff (x, y) : #calculates square difference of two numbers
    """
    calculates square difference
    of two numbers x and y
    """
    return (x - y) ** 2

def rmse(rmse_data) : #calculates rmse given sum of difference and number of elements
    """
    given sum of square differences
    and customer count calculates
    rmse for this data set
    """
    try:
    	result = math.sqrt(rmse_data[0]/rmse_data[1])

    except:
    	result = 0.0

    return result



			

