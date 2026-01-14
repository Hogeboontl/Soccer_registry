# Soccer Registry

A console-based registry system for managing a youth soccer league (ages 4–16). The program supports season management, player registration, searching, editing, and basic statistics, with persistent storage between sessions.

---

## Features

- Start a new season
- Add and edit players
- Search players by multiple criteria
- Display youth category data 
- Persistent data storage between program runs

---

## Program Structure

### Menus
Separate menus are used for:
- Main operations
- Player searching
- Player editing

All menus follow the same interaction pattern.

### Files
- Header file
- Library file (contains most program logic)
- Main file (entry point and UI)

---

## Save File

Player data is stored in `save.txt` to persist information between sessions.

### File Format
season year
number of entries
key of first entry
entry data (space-separated)
key of second entry
...


**Note:** If `save.txt` is edited incorrectly or does not follow this format, the program may fail to load data properly.

---

## Program Startup

- On launch, the program attempts to read `save.txt`.
- If the file does not exist, it is created automatically.
- If no season year is found, the user is prompted to enter one.
- Input is validated to ensure only positive integers are accepted.

---

## Adding a Player

Required inputs:
- First name
- Last name
- Birth year
- Registration status

Validation details:
- Names are checked for capitalization only.  
  Special characters, spaces, or numbers may cause issues due to ASCII-based map ordering.
- Birth year is validated to ensure the player’s age falls within league limits.
- Player category is assigned automatically.
- Registration status accepts only `y` or `n`.

---

## Searching for Players

- A search menu allows filtering by multiple criteria.
- Validation follows the same rules as player creation.
- Category searches are only checked for capitalization, as they require alphanumeric input.

---

## Editing a Player

- Allows modification of all player fields.
- Uses the same validation rules as adding a player.
- Includes a back option so multiple edits can be made without restarting the edit process.

---

## Notes

---


