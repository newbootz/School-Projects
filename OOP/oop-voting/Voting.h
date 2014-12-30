#ifndef voting_h
#define voting_h

#include <iostream> 
#include <string>  
#include <vector>

using namespace std;

class Person {
    public:
        std::vector<std::string> ballots;
        std::string name;
        int votes; 
        bool loser;
};
// ------------
// voting_candidates
// --------------
int voting_candidates(istream& r);
// ------------
// voting_names
// --------------
void voting_names(istream& r, vector<Person>& candidates_vector, int candidates);
// ------------
// voting_ballots
// --------------
void voting_ballots(istream& r, vector<Person>& candidates_vector, int candidates);
// ------------
// voting_skip
// ------------
void voting_skip(istream& r);
// ------------
// voting_read
// ------------
bool voting_read (std::istream&, std::vector<Person>&);
// ------------
// voting_recount
// --------------
void voting_recount(vector<Person>& candidates_vector, vector<int>& eliminated_index);
// ------------
// voting_winner
// --------------
bool voting_winner(vector<Person>& candidates_vector, vector<string>& winners, int total_ballot_count, int candidates_vector_len);
// ------------
// voting_process
// ------------
vector<string> voting_process (vector<Person>& candidates_vector) ;
// -------------
// voting_print
// -------------
void voting_print (ostream& w, vector<string>& winners);
// -------------
// voting_solve
// -------------
void voting_solve (istream& r, ostream& w) ;

#endif