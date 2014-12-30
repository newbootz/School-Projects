// --------
// includes
// --------

#include <cassert>  // assert
#include <sstream>  // istringstream
#include <limits>   // numeric_limits
#include <iostream> 

#include "Voting.h"

using namespace std;
int const some_big_number = 1000000;  //const used for determining min and max
// ------------
// voting_candidates
// --------------
int voting_candidates(istream& r)
{
    int candidates; //read in the number of candidates for this set
    r >> candidates;
    if (!r)
    {
        return false;
    }
    return candidates;
}
// ------------
// voting_names
// --------------
void voting_names(istream& r, vector<Person>& candidates_vector, int candidates)
{
    for (int i = 0; i < candidates; ++i)  //read in all the candidate names
    {                                     //add them to our vector list of candidates
        Person p;                         //as a person object
        getline(r, p.name);
        p.votes = 0;
        p.loser = false;
        candidates_vector.push_back(p);
    }

}
// ------------
// voting_ballots
// --------------
void voting_ballots(istream& r, vector<Person>& candidates_vector, int candidates)
{
     while (true) //keep reading ballot, exit if blank line
     {
        string line = "";
        getline(r, line);

        if (line == "") 
        {
            break;
        }

        istringstream ballot(line, istringstream::in); //create a stream of the ballot
        int c_number = 0;
        ballot >> c_number; //extract candidate numbers from the ballot
        int index = c_number-1;
        candidates_vector[index].ballots.push_back(line); //index into the candidate and add the ballot
        candidates_vector[index].votes+=1; //inc votes for this candidate
    }
}
// ------------
// voting_skip
// ------------
void voting_skip(istream& r) //skips new line chars
{
    string newline;
    getline(r, newline);
}
// ------------
// voting_read
// ------------
bool voting_read (istream& r, vector<Person>& candidates_vector) //reads the set and stores number of candidates, candidate names, ballots
{
    int candidates = voting_candidates(r);
    voting_skip(r); //skip newline
    voting_names(r,candidates_vector,candidates); //read and store candidate names
    voting_ballots(r,candidates_vector,candidates); //read and store ballots

    return true;
}
// ------------
// voting_recount
// --------------
void voting_recount(vector<Person>& candidates_vector, vector<int>& eliminated_index)
{
    int elim_index_len = eliminated_index.size();
    for ( int i = 0; i < elim_index_len; ++i) //iterate through losers indices and update their loser flag
    {
                int c_number =eliminated_index[i];
                candidates_vector[c_number].loser = true; 
                int ball_length = candidates_vector[c_number].ballots.size();
                for( int j = 0; j < ball_length; ++j) //iterate through this losers ballot, giving this persons votes 
                {
                    istringstream ballot_stream(candidates_vector[c_number].ballots[j],istringstream::in); //make stream of ballot line
                    int nextValid = -1;
                    ballot_stream >> nextValid;
                    while (candidates_vector[nextValid - 1].loser) 
                    {
                        ballot_stream >> nextValid;
                    }
                    candidates_vector[nextValid - 1].ballots.push_back(candidates_vector[c_number].ballots[j]);
                    candidates_vector[nextValid - 1].votes+=1;
                }
                candidates_vector[c_number].votes = 0; //remove their votes
                candidates_vector[c_number].ballots.clear();
    }
}
bool voting_winner(vector<Person>& candidates_vector, vector<string>& winners, int total_ballot_count, int candidates_vector_len)
{
     for (int m = 0; m < candidates_vector_len; m++) //check to see if theres any winners
        {
            if (candidates_vector[m].votes > (total_ballot_count / 2)) //winner defined by having more than 50% of the votes
            {
                 winners.push_back(candidates_vector[m].name); //add person to the winners vector and print
                return true;
            }
        }


    return false;
}
// ------------
// voting_process
// --------------
vector<string> voting_process (vector<Person>& candidates_vector) 
{
    vector<string> winners;
    vector<string> eliminated; 
    vector<int> eliminated_index; //the indices to the candidates in candidate_vector that are eliminated

    
    int total_ballot_count = 0;//count the overall total number of ballots for this set
    int k=0;
    int candidates_vector_len = candidates_vector.size();

    while(k < candidates_vector_len) 
    {
        total_ballot_count += candidates_vector[k].votes;
        k+=1;
    }
    
    while (true) 
    {
        int min = 1000000;
        int max = 0;
        //check to see if someone has won
        bool someone_won=voting_winner(candidates_vector,winners,total_ballot_count,candidates_vector_len);
        if(someone_won)
        {
             return winners;
        }
        
        for (int i = 0; i < candidates_vector_len; ++i) //loop through candidates to see who's now eliminated
        {
            Person p = candidates_vector[i];
            if (! candidates_vector[i].loser)
            {

                if (p.votes < min)  //have a new min amount of votes
                {
                    min = p.votes; //set new min, clear vectors, they are now eliminated
                    //since there is a new overall min, we clear lists and add this person to them
                    eliminated.clear();
                    eliminated.push_back(p.name);//add to eliminated list
                    //we are keeping eliminated list with names and index list with indices to the candidates list
                    eliminated_index.clear(); //clear index list
                    eliminated_index.push_back(i); //add them to the new index list
                } 
                else if (p.votes == min) //this person has votes equal to min, they are eliminated
                {
                    //this person has equal votes to the min, add them to the eliminated lists
                    eliminated.push_back(p.name);
                    eliminated_index.push_back(i);
                }
                if (p.votes > max) //person has new max amount of votes
                {
                    //keep track of the max, will use this incase there's a tie
                    max = p.votes;
                }
            }
        }
        
        if (min == max) //there is a tie, we have winners
        {
            winners = eliminated;
            return winners;
        } 
        else 
        {
            //we are going to give the loser's votes to someone who
            //isn't eliminated yet
            voting_recount(candidates_vector,eliminated_index);
        }
    }  
    return winners;
}

// -------------
// voting_print
// -------------

void voting_print (ostream& w, vector<string>& winners) //iterate through winners and print their names
{
    int i=0;
    int winners_size  = winners.size();
    while(i < winners_size)
    {
        w << winners[i] << endl;
        i+=1;
    }
}

// -------------
// voting_solve
// -------------
void voting_solve (istream& r, ostream& w) 
{
    int sets = 0; //read number of sets
    vector<Person> cache; //declare a cache to hold people objects and their info
    r >> sets;

    if (!r) //empty file,exit program
    {
        return;
    }
    
   voting_skip(r); //skip newlines
   voting_skip(r);
   int s = 0;
    while(s < sets && voting_read(r,cache)) //read i number of sets, and process each
    {
        vector<string> winners = voting_process(cache); //process this batch of candidates
        if (s != 0)
        {
            w << endl;
        }
        voting_print(w, winners); //print the winners
        cache.clear(); 
        s+=1;
    }
}
