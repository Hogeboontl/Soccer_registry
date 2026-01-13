#include "soc.h"
#include <iostream>
#include <map>
#include<fstream>
#include<limits>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

void Roster::add_player(){
    string f, l;
    bool r;
    int b;
    cout << "input new players last name: ";
    cin.get();
    getline(cin, l);
    for (char & c : l) c =tolower(c); // lowercases the whole last name so it stays organized nicely, sorry hyphenated names
    l[0] = toupper(l[0]); // capitalizes the first letter of the last name for the search function
    cout << "input new players first name: ";
    getline(cin, f);
    for (char & c : f) c =tolower(c); // for consistency when searching later
    f[0] = toupper(f[0]); 
    bool input_ok = false;
    int birth_year;
    string cat_string;
    do {
        cout << "input new players birth year: ";
        cin >> birth_year;
        if (cin.fail()) { // if the input cannot be converted to an int it will fail
            cout << "invalid input" << endl;
        }
        else {
            input_ok = true;
            int cat_numb = year - birth_year;
            if ( 4 <= cat_numb && cat_numb < 6 ) cat_string = "U6";
            else if ( 6 <= cat_numb && cat_numb < 8) cat_string = "U8";
            else if (8 <= cat_numb && cat_numb < 10) cat_string = "U10";
            else if (10 <= cat_numb && cat_numb < 12) cat_string = "U12";
            else if (12 <= cat_numb && cat_numb < 14) cat_string = "U14";
            else if (14 <= cat_numb && cat_numb < 17) cat_string = "U17";
            else if (cat_numb < 4) {
                cout << "child is too young" << endl;
                input_ok = false;
            }
            else if (cat_numb > 16) {
                cout << "child is too old" << endl;
                input_ok = false;
            }
        }
        cin.clear(); // removes the failure flag
        cin.ignore( numeric_limits<streamsize>::max(), '\n' ); // ensures the rest of the line is ignored- had to google this command
    } while (!input_ok);
    b = birth_year;
    bool more = true;
    char ans;
    while (more) { // while loop prevents them from inputting anything other than yes or no
        cout << "has the new player paid the registration fee? (y/n)";
        cin >> ans;
        switch(ans) {
            case 'y':
            case 'Y':
                r = 1;
                more = false;
                break;
            case 'n':
            case 'N':
                r = 0;
                more = false;
                break;  
            default:
            cout << "invalid answer" << endl;
            cin.ignore( numeric_limits<streamsize>::max(), '\n' );
        }
    }
    Entry e(l,f,b,r, cat_string);
    data.insert(pair<string, Entry> {l+f, e});
}

void Roster::reset() {
    bool more = true;
    bool input_ok = false;
    char ans;
    cin.get(); // removes newline character after input from main
    while (more) { // copy pasted from above to ensure we get a valid answer
        cout << "are you sure you want to start a new season? (y/n) ";
        cin >> ans;
        switch(ans) {
            case 'y':
            case 'Y':
                int y;
                do {
                    cout << "please input the new season year: ";
                    cin >> y;
                    if (cin.fail()) { // if the input cannot be converted to an  int it will fail
                    cout << "invalid input" << endl;
                    }
                    else if (y <= 0) cout << "please input a positive integer" << endl;
                    else {
                        input_ok = true;
                    }
                    cin.clear(); // removes the failure flag
                    cin.ignore( numeric_limits<streamsize>::max(), '\n' ); // ensures the rest of the line is ignored 
                    } while (!input_ok);
                year = y;
                data.clear();
                more = false;
                break;
            case 'n':
            case 'N':
                more = false;
                break;  
            default:
            cout << "invalid answer" << endl;
            cin.ignore( numeric_limits<streamsize>::max(), '\n' );
        }
    }
}

void Roster::search(){
    cin.get(); 
    vector<int> choices;
    string input;
    search_results = data;
    if (data.size() == 0) {
        cout << "no players in current season" << endl;
        return;
    }
    cout << "select criteria to search by (input the numbers with spaces inbetween then press enter, or leave blank to go back)" << endl;
    cout << "1. last name \n" << "2. first name \n" << "3. keyword \n" << "4. year of birth \n" << "5. registration status \n" << "6. league category \n";
    // I preferred allowing the user to choose the combination of criteria they wanted upfront, because stepping through each one
    // becomes time consuming both for me and the user.
    getline(cin, input); // because of this design choice, we need all of their inputs at once
    for (char c : input) {
        if (isdigit(c)) { // had to google this command- ensures the input is an integer
            choices.push_back(c - '0'); // Subtracting the ASCII values results in the correct integer number- had to google this trick too
        }
    }
    bool exit_loop = false;
    for (int criteria : choices) { 
        if (exit_loop) break; // will break the range based loop if the search is empty, so you don't have to go through all specifications
        switch(criteria) {
            case 1: { // fully working unless sorting is messed up by hyphens or special characters
                string l;
                cout << "Input the first letter(s) of the last name (e.g., 'S', 'Sm', 'Smith'; leave blank for all): ";
                getline (cin, l);
                if (l.empty()) {} // do nothing, we just want the whole map back
                else {
                    for (char & c : l) c =tolower(c); 
                    l[0] = toupper(l[0]); //capitalizes the input so that the map and input names will always match in ASCII
                    map <string, Entry>::iterator l_bound = search_results.lower_bound(l); // points to map.begin if no character is specificed
                    // since every name with a character after the input will be higher than it
                    // The input value is included in this bound but not the upper bound command so we need to use this one.
                    l.back()++;// increments the last character in the upper_bound so that it points to everything after the characters we want.
                    map <string, Entry>::iterator u_bound = search_results.lower_bound(l);
                    if (u_bound != search_results.begin()){ // erases everything before l_bound but not including l_bound
                        search_results.erase(search_results.begin(),l_bound);
                    }
                    if (l_bound != search_results.end()){ // erases  u_bound and everything after
                        search_results.erase((u_bound),search_results.end()); 
                    }
                }
                if (search_results.empty()) {
                        cout << "No matches found." << endl;
                        exit_loop = true;
                    }
                    break;
                }
            case 2: { // I have it only check first letters because that seems the most user friendly
            // most people wouldn't search for the name smith with "th" and if they want to search using the first letters they would need to remember to capitalize
                string f;
                cout << "Input the first letter(s) of the first name (e.g., 'T', 'Th', 'Thomas'; leave blank for all):  ";
                getline(cin, f);
                if (f.empty()) {}
                else {
                    for (char & c : f) c =tolower(c); 
                    f[0] = toupper(f[0]); 
                        for (auto i = search_results.begin(); i != search_results.end();) {
                            if (i->second.fname.substr(0,f.length()) != f ) {
                                i = search_results.erase(i); // erase returns an iterator to the next object while also erasing the current one
                            }
                            else i++;
                        }
                }
                 if (search_results.empty()) {
                        cout << "No matches found." << endl;
                        exit_loop = true;

                    }
                break;
                }
            case 3: { 
                // just in case they do want to search for smith with 'th" although they also get last names too. I don't really like this function
                string keyword;
                cout << "input any letter(s) to search for in last and first names (leave blank for all and check capitalization): ";
                getline(cin, keyword);
                if (keyword.empty()) {}
                else {
                    for (auto i = search_results.begin(); i != search_results.end();) {
                        if (i->second.fname.find(keyword) == string::npos && i->second.lname.find(keyword) == string::npos) {
                            i = search_results.erase(i); 
                        }
                        else i++;
                    }
                }
                 if (search_results.empty()) {
                        cout << "No matches found." << endl;
                        exit_loop = true;

                    }
                break;
                }
            case 4: {
                int birth_year;
                bool input_ok;
                do {
                    cout << "please input a birth year to search by (input 0 to skip): ";
                    cin >> birth_year;
                    if (cin.fail()) { 
                        cout << "invalid input" << endl;
                    }
                    else {
                        input_ok = true;
                    }
                    cin.clear(); 
                    cin.ignore( numeric_limits<streamsize>::max(), '\n' );  
                } while (!input_ok);
                if (birth_year != '0') {
                    for (auto i = search_results.begin(); i != search_results.end();) {
                        if (i->second.byear != birth_year) {
                            i = search_results.erase(i); 
                            }
                        else i++;
                    }
                }
                    if (search_results.empty()) {
                    cout << "No matches found." << endl;
                    exit_loop = true;
                    }
            break;
            }
            case 5: {
                bool r;
                bool more = true;
                char ans;
                while (more) { 
                    cout << "has player(s) paid registration fee? (y/n) (use 's' to skip): ";
                    cin >> ans;
                    if (ans == 's' || ans == 'S') {
                        more = false;
                        break;
                    }
                    switch(ans) {
                        case 'y':
                        case 'Y':
                             r = true;;
                            more = false;
                            break;
                        case 'n':
                        case 'N':
                               r = false;
                            more = false;
                            break;  
                        default:
                        cout << "invalid answer" << endl;
                        cin.ignore( numeric_limits<streamsize>::max(), '\n' );
                        }
                    }
                    if (ans != 's' && ans != 'S') {
                        for (auto i = search_results.begin(); i != search_results.end();) {
                            if (i->second.reg != r) {
                                i = search_results.erase(i); 
                            }
                            else i++;
                        }
                    }
                    if (search_results.empty()) {
                    cout << "No matches found." << endl;
                    exit_loop = true;
                    }
                break;
                }
            case 6: 
                string cat;
                cout << "input player category (U6, U8, U10, U12, U14, U17) (u stands for under) (leave blank to skip): ";
                getline(cin,cat);
                if (cat.empty());
                else {
                    cat[0] = toupper(cat[0]); // in case they don't capitalize it. 
                    // I can't think of any good way to add error checking.
                    for (auto i = search_results.begin(); i != search_results.end();) {
                        if (i->second.category != cat) {
                            i = search_results.erase(i); 
                            }
                        else i++;
                    }
                    if (search_results.empty()) {
                        cout << "No matches found." << endl;
                        exit_loop = true;
                    }
                }
            break;          
        }
    }
}

void Roster::search_view(bool & more) {
    bool search_more = true;
    char ans2;
     map <string, Entry>::iterator curitr = search_results.begin();
    while (search_more) {
        if (search_results.empty()) return;
        cout << static_cast<char>(12);
        cout << "player name: " << curitr->second.lname << " " <<  curitr->second.fname << endl; //normal display stuff
        cout << "player Y.O.B: " << curitr->second.byear << endl;
        cout << "player category " << curitr->second.category << endl;
        cout << "player registration status: ";
        if (curitr->second.reg == true) cout << "paid" << endl;
        else cout << "unpaid" << endl;
        cout << "search result " << (distance(search_results.begin(), curitr) + 1) << " out of " << distance(search_results.begin(),search_results.end()) << endl;
        cout << "----------------------------------------------" << endl;
        cout << "next (n) || previous (p) || exit search results (x)|| edit(e) || search (s) || quit(q) || search print(o) " << endl;
        cin >> ans2;
        switch(ans2) {
            case 'n':
            case 'N':
                curitr++;
                if (curitr == search_results.end() )curitr = search_results.begin();
                break;
            case 'p':
            case 'P':
                if (curitr == search_results.begin()) {
                    curitr = (search_results.end());
                     curitr--;
                    }
                else curitr--;
                break;
            case 'x':
            case 'X':
                search_more = false;
                 break;
            case 'q':
            case 'Q':
                exit();
                search_more=false;
                more = false;
                break;
            case 's':
            case 'S':
                    search();
                    curitr = search_results.begin();
                    break;
            case 'e':
            case 'E':
                edit(curitr);
                 break;
            case 'o':
            case 'O':
                search_print();
                break;
            default:
                cout << "invalid command" << endl;
                cin.ignore( numeric_limits<streamsize>::max(), '\n' );
                 break;
                    }
             }
}

void Roster::edit( map <string, Entry>::iterator current_iterator){
    bool more_edits = true;
    char ans3;
    while (more_edits) {
        cout << static_cast<char>(12);
        cout << "what would you like to edit on the selected player?" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "last name (L)|| first name(f)|| year of birth(y) || registration status (r)|| go back (b) ||" << endl;
        cout << "----------------------------------------------" << endl;
        cin >> ans3;
        switch(ans3) {
            case 'l':
            case 'L': {
                string l;
                string old_key = current_iterator->first; // stores the old key
                cout << "input players new last name (leave blank to make no edit): ";
                cin.get();
                getline(cin, l);
                if (!l.empty()) {
                    for (char & c : l) c =tolower(c); // keeps it consistent
                    l[0] = toupper(l[0]);
                    string new_key = l +  current_iterator->second.fname; // makes a new key
                    if (new_key != old_key) {
                        current_iterator ->second.lname = l; // changes the entry to reflect the changes
                        Entry updated_entry =  current_iterator ->second; // makes it entry so it can get paired and added
                        data.erase(old_key);
                        search_results.erase(old_key);
                        if (data.find(new_key) == data.end()){ // checks to make sure the new key isn't already present
                            search_results.insert({new_key,updated_entry});
                            data.insert({new_key, updated_entry});
                            cout << "last name updated successfully" << endl;
                            current_iterator = search_results.find(new_key); // moves the iterator to where it needs to be
                        }
                        else cout << "error, person already exists in register." << endl;
                    }
                    else cout << "no changes made" << endl;
                }
                break;
                }
            case 'f':
            case 'F':{
                string f;
                string old_key = current_iterator->first;
                cout << "input players new first name (leave blank to make no edit): ";
                cin.get();
                getline(cin,f);
                if (!f.empty()) {
                    for (char & c : f) c =tolower(c); 
                    f[0] = toupper(f[0]);
                    string new_key = f +  current_iterator->second.lname;
                    if (new_key != old_key) {
                        current_iterator ->second.fname = f; 
                        Entry updated_entry =  current_iterator ->second; //this is necessary so that data gets an entry input
                        data.erase(old_key);
                        search_results.erase(old_key);
                        if (data.find(new_key) == data.end()){ // checks to make sure the new key isn't already present
                            search_results.insert({new_key,updated_entry});
                            data.insert({new_key, updated_entry});
                            cout << "first name updated successfully" << endl;
                        }
                        else cout << "error, person already exists in register." << endl;
                    }
                    else cout << "no changes made" << endl;
                    current_iterator = search_results.find(new_key);
                }
                break;
                }
            case 'y':
            case 'Y': {
                string key = current_iterator ->first;// key should always be valid, so no worries about creating a new player on accident
                int birth_year;
                string cat_string;
                bool input_ok = false;
                do {
                    cout << "input updated birth year (input 0 to go back): ";
                    cin >> birth_year;
                    if (birth_year == 0) break;
                    if (cin.fail()) { 
                        cout << "invalid input" << endl;
                    }
                    else {
                        input_ok = true;
                        int cat_numb = year - birth_year;
                        if ( 4 <= cat_numb && cat_numb < 6 ) cat_string = "U6";
                        else if ( 6 <= cat_numb && cat_numb < 8) cat_string = "U8";
                        else if (8 <= cat_numb && cat_numb < 10) cat_string = "U10";
                        else if (10 <= cat_numb && cat_numb < 12) cat_string = "U12";
                        else if (12 <= cat_numb && cat_numb < 14) cat_string = "U14";
                        else if (14 <= cat_numb && cat_numb < 17) cat_string = "U17";
                        else if (cat_numb < 4) {
                            cout << "new birth year makes child too young" << endl;
                            input_ok = false;
                        }
                        else if (cat_numb > 16) {
                            cout << "new birth year makes child too old" << endl;
                            input_ok = false;
                        }
                    }
                    cin.clear(); 
                    cin.ignore( numeric_limits<streamsize>::max(), '\n' ); 
                } while (!input_ok);
                current_iterator->second.byear = birth_year;
                current_iterator->second.category = cat_string;
                data.at(key) = current_iterator->second;
                cout << "birth year successfully updated" << endl;
                break;
            }
            case 'r':
            case 'R': {
                bool more = true;
                char ans;
                bool r;
                string key = current_iterator ->first;
                while (more) { 
                    cout << "has the player paid the registration fee? (y/n) (use b to go back): ";
                    cin >> ans;
                    if (ans == 'b' || ans == 'B') {
                        more = false;
                        break;
                    }
                    switch(ans) {
                        case 'y':
                        case 'Y':
                            r = 1;
                            more = false;
                            break;
                        case 'n':
                        case 'N':
                            r = 0;
                            more = false;
                            break;  
                        default:
                        cout << "invalid answer" << endl;
                        cin.ignore( numeric_limits<streamsize>::max(), '\n' );
                    }
                }
                current_iterator->second.reg = r;
                data.at(key) = current_iterator->second;
                cout << "registration updated sucessfully" << endl;
                break;
                }
            case 'b':
            case 'B':
                more_edits = false;
                break;
            default:
                cout << "invalid command" << endl;
                cin.ignore( numeric_limits<streamsize>::max(), '\n' );
                break;

        }

    }
}

void Roster::exit() {
    ofstream out("save.txt");
    out << year << endl;
    out << data.size() << endl;
    for (auto & entry : data){
            out << entry.first << endl;
            out << entry.second.lname << " " << entry.second.fname;
            out << " " << entry.second.reg << " " <<  entry.second.category << " " << entry.second.byear << endl;
        }
    }

void Roster::read_in(){
    ifstream in("save.txt");
    if (in.fail()) {
        in.close();
        ofstream out("save.txt"); //makes a save file that is empty, so that the user does not need to rerun the program
        out.close();
        in.open("save.txt");
    }
    in >> year;
    if (in.fail()) {
        bool input_ok = false;
        int y;
        do {
            cout << "please input the season year: ";
            cin >> y;
            if (cin.fail()) { // if the input cannot be converted to an  int it will fail
                cout << "invalid input" << endl;
                }
            else if (y <= 0) cout << "please input a positive integer" << endl;
            else {
                    input_ok = true;
                    year = y;
                    return;
                }
            in.clear(); // removes the failure flag
            cin.ignore( numeric_limits<streamsize>::max(), '\n' ); // ensures the rest of the line is ignored 
        } while (!input_ok);
    }
    int file_size, birth_year;
    in >> file_size;
    string f,l,cat, key;
    bool registered;
    for (int i = 0; i < file_size; i++) {
        in >> key;
        in >> l >> f >> registered >> cat >> birth_year;
        Entry e( l, f, birth_year, registered, cat);
        data.insert({key, e});
    }
    in.close();
}

void Roster::display() {
    char ans;
    bool more = true;
    while (more) {
        cout << "------------------------------------" << endl;
        vector<int> category_count(6,0); // the count for all the categories
        vector<string> categories = {"U6", "U8", "U10", "U12", "U14", "U17"};
        int number_reg = 0; //total number registered
        for (auto const & term : data){
            const Entry & e = term.second;
            if (e.reg == true) { // checks for all paid players
                number_reg++;
                for( int i = 0; i < categories.size(); i++){ // finds the category and adds to it
                    if (categories[i] == e.category) category_count[i]++;
                    break;
                }
            }
        }
        cout << "total number of players: " << data.size() << endl;
        for (int i = 0; i < categories.size(); i++){
            cout << "number of players who have paid in category " << categories[i] << " is: " << category_count[i] << endl;
        }
        cout << "------------------------------------" << endl;
        cout << "press b to go back" << endl;
        cin >> ans;
        switch(ans) {
            case 'b':
            case 'B':
                more = false;
                break;
            default:
            cout << "invalid input" << endl;
            cin.ignore( numeric_limits<streamsize>::max(), '\n' );
            break;
        }
    }
}

void Roster::main_print() {
    cout << "please input the name of a file to write to: "; // shouldn't need a fail state since it will create the file if not present
    ofstream out;
    char filename [80] ; 
    cin >> filename;
    out.open (filename);
    vector<string> categories = {"U6", "U8", "U10", "U12", "U14", "U17"};
    for (string category : categories){
        out << "players in category " << category << ":" << endl;
        for (auto const & term : data){
             const Entry & e = term.second;
             if (e.category == category){
                out << e.lname << " " << e.fname << endl;
             }
        }

    }
    cout << "print successful" << endl;
}

void Roster::search_print(){ // copied from above but uses search results instead of data
    cout << "please input the name of a file to write to: "; 
    ofstream out;
    char filename [80]; 
    cin >> filename;
    out.open (filename);
    vector<string> categories = {"U6", "U8", "U10", "U12", "U14", "U17"};
    for (string category : categories){
        out << "players in category " << category << ":" << endl;
        for (auto const & term : search_results){
             const Entry & e = term.second;
             if (e.category == category){
                out << e.lname << " " << e.fname << endl;
             }
        }

    }
    cout << "print successful" << endl;
}