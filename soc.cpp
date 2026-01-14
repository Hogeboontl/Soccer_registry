#include "soc.h"
#include <iostream>
#include <map>
#include <limits>
using namespace std;

int main(){
    bool more = true;
    char ans;
    Roster myrost;
    myrost.read_in();
    while (more) {
    cout << static_cast<char>(12);
    cout << "the season of ";    
    myrost.display_year();
    cout << " has ";
    myrost.number_of_players();
    cout << " players" << endl << "what would you like to do? " << endl;
    cout <<  "------------------------------------------------------" << endl;
    cout << "start new season (n) || add player (a) || quit (q) || search (s) || display stats (d) || print (p)" << endl;
    cout << "------------------------------------------------------" << endl;
    cin >> ans;
    switch (ans) {
        case 'a':
        case 'A':
            myrost.add_player();
            break;
        case 'n':
        case 'N':
            myrost.reset();
            break;
        case 'q':
        case 'Q': 
            myrost.exit();
            more = false;
            break;
        case 's':
        case 'S':{
            myrost.search();
            myrost.search_view(more);
            break;
        }
        case 'd':
        case 'D':
            myrost.display();
            break;
        case 'p':
        case 'P':
            myrost.main_print();
            break;
        default:
        cout << "invalid command" << endl;
        cin.ignore( numeric_limits<streamsize>::max(), '\n' );
        break;
    }
    }
}