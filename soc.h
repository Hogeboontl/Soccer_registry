#include <iostream>
#include <map>
#include <fstream>
using namespace std;

class Entry{
public:
friend class Roster; // allows functions of roster to access entries.
Entry(string l, string f, int b, bool r, string c) {lname = l; fname = f; byear = b; reg = r; category = c; }
private:
string fname, lname, category;
bool reg;
int byear;
};

class Roster{
public:
void add_player();
void number_of_players() {cout << data.size();}
void display_year() {cout << year;}
void reset(); // starts a new season
void search(); 
void search_view(bool &);
void edit(map <string, Entry>::iterator);
void exit();
void read_in();
void display();
void main_print();
void search_print();
private:
map <string, Entry> data;
int year;
map <string, Entry> search_results;
};