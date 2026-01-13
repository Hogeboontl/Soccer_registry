# Soccer_registry

overview:
    This program intends to act as a registry for a youth soccer league (from ages 4 to 16). With this goal in mind, it includes the features for starting a new season, adding a player, searching for players, 
    displaying stats, printing names and editing player data. 

program specifications:
    the program has a main file that acts as the main view of the program and gives the user access to a menu. From here, the program will execute whatever function is dictated by the menu. 
    There are also menus for editing a player and for the search view, and these function similarly to the main view. 
    All of the player data is contained in a map with the key being a string with the combined last and first name of the player. The value of the map is an object called entry which just combines
    all of the necessary data for that player(first and last name, birthday, registration and category). A vector of Entries was a possible alternative but sorting the vector would have been more work then just using a map. The program is split into a header, 
    library and main file. The library contains all of the functions called and is by far the largest file.
    The program is highly modular, as almost all features are contained within their own function. Any self explanatory or non major feature is excluded from this document.
    Between sessions, the program stores the data in a file titled save.txt that looks like this: 

    year
    number of entries
    the key of the first entry 
    all of the data contained within the entry object seperated by spaces
    key to second entry
    etc.

program start up:
    On program start up, it will call a function to read from a file titled save.txt that stores previous inputs to the program. If the file isn't present, it will create it.
    if the user messes with the save file and doesn't put data in the correct format, it will not read in correctly.
    After checking for the file, it will check to see if there is a year, if there isn't one, it makes the user input the current season.  
    it error checks and will only accept positive integer values before a character that would fail the error check. 

starting a new season:
    The function for starting a new season asks for confirmation before clearing data. This is error checked and only a y or n input will work. The season year is error checked just
    like in the start up function.

adding a player:
    Adding a player involves inputting a first and last name, as well as a birth year and registration status into the function.
    
    The names are only checked for capitilization and any special characters, spaces or integers will cause the search function and possibly others to fail
    due to the sorting of maps relying on ASCII value comparisons. (I think error checking these could be implemented at a later date, it would just require a little more effort).

    The birth year is error checked to make sure the age will fall into the bounds of the league as well as error checked for non integer characters. It will also automatically input the 
    players category

    The registration status is error checked for any non y/n answers.

searching for player(s):
    Searching for players opens a menu that allows you select every criteria you want to search for. It will only read digits in and will do so even if characters are between them.
    It is error checked in the same capacity that adding a player is.
    Searching via category is only error checked for capitilization since it requires a string with both a letter and numbers.

editing a player:
    Editing a player allows the user to change all of the criteria in the add player function. It follows all the same error checking. It has a back feature so that the user can edit as much as they want
    instead of having to reopen the edit function.

Printing:
    Using the print in the main function results in the names of all players getting printed to a chosen file sorted by category and then alphabetically. Using it in the search menu
    results in only those present in the search getting printed. The print function will create a file if it is not present. It does not error check the file.
