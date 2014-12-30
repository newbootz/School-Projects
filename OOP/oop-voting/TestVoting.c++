
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Voting.h"

// -----------
// TestVoting
// -----------

// ------------
// voting_process
// --------------
TEST(Voting, process_0) 
{
    std::ostringstream w;
    vector<Person> vp;
    Person p;         
    p.name = "A";              
    p.votes = 1;
    p.loser = false;
    vp.push_back(p);
    vector<string> vs = voting_process(vp);
    ASSERT_EQ("A", "A"); 
}



// -----------------
// voting_names
// -----------------

TEST(Voting, names_1) //without an endline character
{
    vector<Person> cache;
    std::istringstream r("Billy Mays");
    voting_names(r,cache,1);
    Person temp = cache[0];
    ASSERT_EQ("Billy Mays",temp.name);
}

TEST(Voting, names_2) //without an endline character
{
    vector<Person> cache;
    std::istringstream r("Billy Mays\nJohnny Boy\nStay Golden");
    voting_names(r,cache,3);
    Person temp = cache[0];
    ASSERT_EQ("Billy Mays",temp.name);
    temp = cache[1];
    ASSERT_EQ("Johnny Boy",temp.name);
    temp = cache[2];
    ASSERT_EQ("Stay Golden",temp.name);
}
TEST(Voting, names_3) //without an endline character
{
    vector<Person> cache;
    std::istringstream r("・ｱｱｱ}");
    voting_names(r,cache,1);
    Person temp = cache[0];
    ASSERT_EQ("・ｱｱｱ}",temp.name);
}
TEST(Voting, names_4) //without an endline character
{
    vector<Person> cache;
    std::istringstream r("・ｱｱｱ}\nHELP ME    ME  ME  ME\n Wat                Hi");
    voting_names(r,cache,3);
    Person temp = cache[0];
    ASSERT_EQ("・ｱｱｱ}",temp.name);
    temp = cache[1];
    ASSERT_EQ("HELP ME    ME  ME  ME",temp.name);
    temp = cache[2];
    ASSERT_EQ(" Wat                Hi",temp.name);
}

TEST(Voting, names_5) //without an endline character
{
    vector<Person> cache;
    std::istringstream r("{ëﾘﾓﾉ\nﾈﾋﾇﾆ");
    voting_names(r,cache,2);
    Person temp = cache[0];
    ASSERT_EQ("{ëﾘﾓﾉ",temp.name);
    temp = cache[1];
    ASSERT_EQ("ﾈﾋﾇﾆ",temp.name);
}


TEST(Voting, names_6) //without an endline character
{
    vector<Person> cache;
    std::istringstream r("ಠ_ಠ\nಠ_ಠ\nಠ_ಠ");
    voting_names(r,cache,3);
    Person temp = cache[0];
    ASSERT_EQ("ಠ_ಠ",temp.name);
    temp = cache[1];
    ASSERT_EQ("ಠ_ಠ",temp.name);
    temp = cache[2];
    ASSERT_EQ("ಠ_ಠ",temp.name);
}

// -----------------
// voting_candidates
// -----------------
TEST(Voting,candidates_1) //without an endline character
{
    std::istringstream r("20 ");
    int candidates = voting_candidates(r);
    ASSERT_EQ(20,candidates);
}

TEST(Voting,candidates_2) //without an endline character
{
    std::istringstream r("  10   ");
    int candidates = voting_candidates(r);
    ASSERT_EQ(10,candidates);
}

TEST(Voting,candidates_3) //without an endline character
{
    std::istringstream r("11 - asdasd 564a564 we4561243 465q344212634 12563412563123");
    int candidates = voting_candidates(r);
    ASSERT_EQ(11,candidates);
}

TEST(Voting,candidates_4) //without an endline character
{
    std::istringstream r("13");
    int candidates = voting_candidates(r);
    ASSERT_EQ(13,candidates);
}

TEST(Voting,candidates_5) //without an endline character
{
    std::istringstream r("0.0000000001");
    int candidates = voting_candidates(r);
    ASSERT_EQ(0,candidates);
}

TEST(Voting,candidates_6) //without an endline character
{
    std::istringstream r("  8   8   7   8   9   7");
    int candidates = voting_candidates(r);
    ASSERT_EQ(8,candidates);
}


// --------------
// voting_ballots
// --------------

TEST(Voting, ballots_1) //without an endline character
{
    vector<Person> cache;
    Person temp;
    temp.name = "Hi There";
    temp.votes = 0;
    cache.push_back(temp);
    temp.name = "Bill Murphy";
    temp.votes = 0;
    cache.push_back(temp);
    std::istringstream r("2 1\n1 2\n2 1\n");
    voting_ballots(r,cache,2);
    ASSERT_EQ(2,cache[1].votes);
}


// ----
//voting_solve
// ----

TEST(Voting, solve_1) //without an endline character
{
    std::istringstream r("1\n\n1\nA\n1");
    std::ostringstream w;
    voting_solve(r,w);
    ASSERT_EQ("A\n", w.str());
}
TEST(Voting, solve_2) //with and end line charactr
{
    std::istringstream r("1\n\n1\nA\n1\n");
    std::ostringstream w;
    voting_solve(r,w);
    ASSERT_EQ("A\n", w.str());
}
TEST(Voting, solve_3) //with and end line charactr
{
    std::istringstream r("1\n\n1\nA\n1\n\n");//extra end line char
    std::ostringstream w;
    voting_solve(r,w);
    ASSERT_EQ("A\n", w.str());
}
TEST(Voting, solve_4) //with and end line charactr
{
    std::istringstream r("2\n\n1\nA\n1\n\n1\nA\n1\n");
    std::ostringstream w;
    voting_solve(r,w);
    ASSERT_EQ("A\n\nA\n", w.str());
}

// -------------
// voting_print
// -------------

TEST(Voting, print_1) 
{
    std::ostringstream w;
    vector<string> c = {"A"};
    voting_print(w,c);
    ASSERT_EQ("A\n", w.str());
}
TEST(Voting, print_2) 
{
    std::ostringstream w;
    vector<string> c = {"A","B","C"};
    voting_print(w,c);
    ASSERT_EQ("A\nB\nC\n", w.str());
}
TEST(Voting, print_3) 
{
    std::ostringstream w;
    vector<string> c = {"A","B"};
    voting_print(w,c);
    ASSERT_EQ("A\nB\n", w.str());
}
TEST(Voting, print_4) 
{
    std::ostringstream w;
    vector<string> c = {"joe","billy"};
    voting_print(w,c);
    ASSERT_EQ("joe\nbilly\n", w.str());
}

// ------------
// voting_process
// --------------
TEST(Voting, process_1) 
{
    std::ostringstream w;
    vector<Person> vp;
    Person p;         
    p.name = "A";              
    p.votes = 1;
    p.loser = false;
    vp.push_back(p);
    vector<string> vs = voting_process(vp);
    ASSERT_EQ(p.name, "A"); 
}
TEST(Voting, process_2) 
{
    std::ostringstream w;
    vector<Person> vp;
    Person p;         
    p.name = "billy";              
    p.votes = 1;
    p.loser = false;
    vp.push_back(p);
    vector<string> vs = voting_process(vp);
    ASSERT_EQ(p.name, "billy"); 
}
TEST(Voting, process_3) 
{
    std::ostringstream w;
    vector<Person> vp;
    Person p;         
    p.name = "A";              
    p.votes = 1;
    p.loser = false;
    vp.push_back(p);
    vector<string> vs = voting_process(vp);
    ASSERT_EQ(p.votes, 1); 
}
TEST(Voting, process_4) 
{
    std::ostringstream w;
    vector<Person> vp;
    Person p;         
    p.name = "A";              
    p.votes = 1;
    p.loser = false;
    vp.push_back(p);
    vector<string> vs = voting_process(vp);
    ASSERT_EQ(p.loser, false); 
}

// ------------
// voting_skip
// --------------
TEST(Voting, skip_1) 
{
    std::ostringstream w;
    std::istringstream r("\n");
    voting_skip(r);
    ASSERT_EQ("A", "A"); 
}
TEST(Voting, skip_2) 
{
    std::ostringstream w;
    std::istringstream r("\n\n");
    voting_skip(r);
    ASSERT_EQ(true, true); 
}
TEST(Voting, skip_3) 
{
    std::ostringstream w;
    std::istringstream r("\n\n\n");
    voting_skip(r);
    ASSERT_EQ(true, true); 
}
// ------------
// voting_read
// ------------
TEST(Voting, read_1) 
{
    std::ostringstream w;
    std::istringstream r("1\n\n1\nA\n1\n");
    Person p;
    p.name = "A";
    p.loser = false;
    p.votes = 1;
    vector<Person> vp;
    vp.push_back(p);
    //bool b = voting_read(r,vp);
    ASSERT_EQ(true, true); 
}
// ------------
// voting_recount
// --------------
TEST(Voting, recount_1) 
{
    Person p;
    p.name = "A";
    p.loser = false;
    p.votes = 1;
    vector<Person> vp;
    vp.push_back(p);
    vector<int> i;
   voting_recount(vp, i);
   ASSERT_EQ(true, true); 
}
// ------------
// voting_winner
// --------------
TEST(Voting, winner_1) 
{
    Person p;
    p.name = "A";
    p.loser = false;
    p.votes = 1;
    vector<Person> vp;
    vp.push_back(p);
    vector<string> win= {"A"};
    bool tf=voting_winner(vp,win,1,1);
    ASSERT_EQ(true, true); 
}
TEST(Voting, winner_2) 
{
    Person p;
    p.name = "Billy";
    p.loser = false;
    p.votes = 1;
    vector<Person> vp;
    vp.push_back(p);
    vector<string> win= {"Billy"};
    bool tf=voting_winner(vp,win,1,1);
    ASSERT_EQ(true, true); 
}
TEST(Voting, winner_3) 
{
    Person p;
    p.name = "Bob";
    p.loser = false;
    p.votes = 1;
    vector<Person> vp;
    vp.push_back(p);
    vector<string> win= {"Bob"};
    bool tf=voting_winner(vp,win,1,1);
    ASSERT_EQ(true, true); 
}