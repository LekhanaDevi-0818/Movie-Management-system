Movie Management System

This is a C++ console-based Movie Management System that organizes and manages movies within different categories. It supports movie addition, deletion, search, and display, with efficient handling through linked data structures and a binary search for optimized lookups.




Features
- Add Movie Categories
  
- Add Movies in Sorted Order
  
- Binary Search for Movies
  
- Delete Movie Categories
  
- Delete Movies by Release Date
  
- Display All Categories and Movies
  
- Technologies Used




Language: C++

Data Structures: Doubly Linked List (for categories), Circular Doubly Linked List (for movies)
Algorithms: Binary Search on doubly linked list



System Design
Class: Movie
Represents a movie with:
m_name: Movie name
m_date: Release date
left, right: Pointers to adjacent movies (used in doubly circular linked list)
Class: movie_Category

Represents a movie category (like Action, Comedy, etc.) that holds:
Moviename: Name of the category
ML_Head, ML_Tail: Pointers to the first and last movies
prev, next: Pointers to adjacent categories
Methods:
adding_Movie(): Inserts movie in sorted order
Movie_binarySearch(): Searches a movie using binary search
Movie_Ind(): Returns the index of a movie
print_movies_categories(): Displays all movies in a category
Class: M_Categories

Manages all movie categories:
head_prev: Points to the first category
Methods:
adding_Category(): Adds a new movie category
removing_Category(): Removes a category and all its movies
searching_movieName(): Finds a category by name
searching_movie(): Searches for a movie across all categories
deleting_movies(): Deletes all movies released before a specific date

How It Works
The main() function demonstrates the functionality:
Adds 3 categories: Children, Action, Comedy
- Adds movies into each category
- Displays all categories with movies
- Searches for "Barbie"
- Deletes the "Children" category
- Tries searching for "Barbie" again
  
Sample Output
Children:
Movie name:- Barbie; date: 10-21-2001
Movie name:- Harry Potter; date: 11-14-2001
Movie name:- Lion King; date: 06-24-1994
Action:
Movie name:- MI-5; date: 05-08-2005
Movie name:- Rocky; date: 11-27-1976
Movie name:- Taken; date: 02-27-2008
Comedy:
Movie name:- Harold & Kumar; date: 07-30-2024
Movie name:- Jerry McGuire; date: 12-13-1996
Movie name:- Tuxedo; date: 09-27-2002

Barbie is in the list
After removing children category Barbie is in the list

Notes
The movie insertion ensures no duplicates and keeps the list sorted. Binary search is used for quick retrieval.
Memory is manually managed (free() used for deletion). Minimal input validation; intended for academic/demo purposes.

Future Enhancements
Add GUI support
Save/load from files
Enhanced error handling
Advanced filters (e.g. by date range, genre, etc.)
