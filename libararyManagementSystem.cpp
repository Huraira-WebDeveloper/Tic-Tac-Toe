//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <algorithm>
//#include <limits>
//#include <cctype>
//
//using namespace std;
//
//// ================== Helper Functions ==================
//void clearScreen() {
//    cout << "\033[2J\033[1;1H";  // ANSI escape codes for clearing screen
//}
//
//void pressEnterToContinue() {
//    cout << "\nPress Enter to continue...";
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
//    cin.get();
//}
//
//// ================== Book Class ==================
//class Book {
//private:
//    string ISBN;
//    string title;
//    string author;
//    bool isAvailable;
//
//public:
//    Book(string isbn = "", string t = "", string a = "")
//    : ISBN(isbn), title(t), author(a), isAvailable(true) {}
//
//    // Getters
//    string getISBN() const { return ISBN; }
//    string getTitle() const { return title; }
//    string getAuthor() const { return author; }
//    bool isAvailableStatus() const { return isAvailable; }
//
//    // Book status management
//    void markBorrowed() { isAvailable = false; }
//    void markReturned() { isAvailable = true; }
//
//    void display() const {
//        cout << " ISBN:      " << ISBN << "\n"
//             << " Title:     " << title << "\n"
//             << " Author:    " << author << "\n"
//             << " Status:    " << (isAvailable ? "Available" : "Borrowed") << "\n";
//    }
//};
//
//// ================== User Class ==================
//class User {
//private:
//    int userID;
//    string name;
//    vector<string> borrowedBooks;
//
//public:
//    User(int id = 0, string n = "")
//    : userID(id), name(n) {}
//
//    // Getters
//    int getID() const { return userID; }
//    string getName() const { return name; }
//    const vector<string>& getBorrowedBooks() const { return borrowedBooks; }
//
//    // Book management
//    void borrowBook(const string& isbn) {
//        borrowedBooks.push_back(isbn);
//    }
//
//    void returnBook(const string& isbn) {
//        borrowedBooks.erase(
//            remove(borriedBooks.begin(), borrowedBooks.end(), isbn),
//            borrowedBooks.end()
//        );
//    }
//
//    void display() const {
//        cout << " User ID:   " << userID << "\n"
//             << " Name:      " << name << "\n"
//             << " Borrowed:  " << borrowedBooks.size() << " books\n";
//    }
//};
//
//// ================== Library Class ==================
//class Library {
//private:
//    vector<Book> books;
//    vector<User> users;
//    const string BOOKS_FILE = "books.dat";
//    const string USERS_FILE = "users.dat";
//
//    // Helper function for input validation
//    string getNonEmptyInput(const string& prompt) {
//        string input;
//        while(true) {
//            cout << prompt;
//            getline(cin, input);
//            
//            // Remove leading/trailing whitespace
//            input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
//            
//            if(!input.empty()) return input;
//            cout << "Input cannot be empty! Please try again.\n";
//        }
//    }
//
//public:
//    Library() { loadData(); }
//    ~Library() { saveData(); }
//
//    // ========== Data Persistence ==========
//    void loadData() {
//        // Implementation for loading books and users from files
//    }
//
//    void saveData() {
//        // Implementation for saving books and users to files
//    }
//
//    // ========== Book Operations ==========
//    void addBook() {
//        clearScreen();
//        cout << "=== Add New Book ===\n";
//        
//        string isbn = getNonEmptyInput("Enter ISBN: ");
//        string title = getNonEmptyInput("Enter title: ");
//        string author = getNonEmptyInput("Enter author: ");
//
//        // Check for duplicate ISBN
//        if(findBook(isbn)) {
//            cout << "\nError: Book with this ISBN already exists!\n";
//            pressEnterToContinue();
//            return;
//        }
//
//        books.emplace_back(isbn, title, author);
//        cout << "\nBook added successfully!\n";
//        pressEnterToContinue();
//    }
//
//    Book* findBook(const string& isbn) {
//        auto it = find_if(books.begin(), books.end(),
//            [&isbn](const Book& b) { return b.getISBN() == isbn; });
//        return (it != books.end()) ? &(*it) : nullptr;
//    }
//
//    void displayAllBooks() {
//        clearScreen();
//        cout << "=== Book Catalog ===\n";
//        
//        if(books.empty()) {
//            cout << "No books available in the library.\n";
//            pressEnterToContinue();
//            return;
//        }
//
//        for(const auto& book : books) {
//            book.display();
//            cout << "--------------------\n";
//        }
//        pressEnterToContinue();
//    }
//
//    // ========== User Operations ==========
//    void addUser() {
//        clearScreen();
//        cout << "=== Add New User ===\n";
//        
//        int id;
//        string name;
//        
//        while(true) {
//            cout << "Enter user ID (numbers only): ";
//            if(cin >> id) break;
//            cout << "Invalid input! Please enter numbers only.\n";
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//        }
//        cin.ignore();  // Clear input buffer
//        
//        name = getNonEmptyInput("Enter user name: ");
//
//        // Check for duplicate user ID
//        if(findUser(id)) {
//            cout << "\nError: User ID already exists!\n";
//            pressEnterToContinue();
//            return;
//        }
//
//        users.emplace_back(id, name);
//        cout << "\nUser added successfully!\n";
//        pressEnterToContinue();
//    }
//
//    User* findUser(int userID) {
//        auto it = find_if(users.begin(), users.end(),
//            [userID](const User& u) { return u.getID() == userID; });
//        return (it != users.end()) ? &(*it) : nullptr;
//    }
//
//    // ========== Transaction Operations ==========
//    void borrowBook() {
//        clearScreen();
//        cout << "=== Borrow a Book ===\n";
//        
//        int userID;
//        cout << "Enter your user ID: ";
//        cin >> userID;
//        
//        User* user = findUser(userID);
//        if(!user) {
//            cout << "\nError: User not found!\n";
//            pressEnterToContinue();
//            return;
//        }
//
//        string isbn;
//        cout << "Enter ISBN of book to borrow: ";
//        cin >> isbn;
//        
//        Book* book = findBook(isbn);
//        if(!book) {
//            cout << "\nError: Book not found!\n";
//            pressEnterToContinue();
//            return;
//        }
//
//        if(!book->isAvailableStatus()) {
//            cout << "\nError: Book is already borrowed!\n";
//            pressEnterToContinue();
//            return;
//        }
//
//        book->markBorrowed();
//        user->borrowBook(isbn);
//        cout << "\nBook borrowed successfully!\n";
//        pressEnterToContinue();
//    }
//
//    // Similar implementation for returnBook()
//};
//
//// ================== Menu System ==================
//void displayMainMenu() {
//    clearScreen();
//    cout << "=== Library Management System ===\n"
//         << "1. Add New Book\n"
//         << "2. List All Books\n"
//         << "3. Add New User\n"
//         << "4. Borrow a Book\n"
//         << "5. Return a Book\n"
//         << "6. Exit\n"
//         << "Enter your choice: ";
//}
//
//int main() {
//    Library library;
//    int choice;
//
//    do {
//        displayMainMenu();
//        while(!(cin >> choice)) {
//            cout << "Invalid input! Please enter a number (1-6): ";
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//        }
//        cin.ignore();  // Clear input buffer
//
//        switch(choice) {
//            case 1: library.addBook(); break;
//            case 2: library.displayAllBooks(); break;
//            case 3: library.addUser(); break;
//            case 4: library.borrowBook(); break;
//            // case 5: library.returnBook(); break;
//            case 6: cout << "Exiting program...\n"; break;
//            default: cout << "Invalid choice! Try again.\n"; pressEnterToContinue();
//        }
//    } while(choice != 6);
//
//    return 0;
//}







						//Libaray Management System
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Book class with basic properties
class Book {
public:
    string title;
    string author;
    string isbn;
    bool isAvailable;

    // Constructor
    Book(string t, string a, string i) {
        title = t;
        author = a;
        isbn = i;
        isAvailable = true;
    }

    void display() {
        cout << "\nBook: " << title
             << "\nAuthor: " << author
             << "\nISBN: " << isbn
             << "\nStatus: " << (isAvailable ? "Available" : "Borrowed") << endl;
    }
};

// Library management system
class Library {
private:
    vector<Book> books;

public:
    // Add a new book to the library
    void addBook() {
        string title, author, isbn;
        
        cout << "\nEnter book title: ";
        getline(cin, title);
        
        cout << "Enter author name: ";
        getline(cin, author);
        
        cout << "Enter ISBN: ";
        getline(cin, isbn);

        // Check if ISBN already exists
        bool exists = false;
        for(Book& book : books) {
            if(book.isbn == isbn) {
                exists = true;
                break;
            }
        }

        if(!exists) {
            books.push_back(Book(title, author, isbn));
            cout << "Book added successfully!\n";
        } else {
            cout << "Book with this ISBN already exists!\n";
        }
    }

    // Display all books
    void showAllBooks() {
        if(books.empty()) {
            cout << "\nNo books in the library!\n";
            return;
        }

        cout << "\n=== Library Books ===\n";
        for(Book& book : books) {
            book.display();
        }
    }

    // Borrow a book
    void borrowBook() {
        string isbn;
        cout << "\nEnter ISBN of book to borrow: ";
        getline(cin, isbn);

        for(Book& book : books) {
            if(book.isbn == isbn) {
                if(book.isAvailable) {
                    book.isAvailable = false;
                    cout << "Book borrowed successfully!\n";
                } else {
                    cout << "Book is already borrowed!\n";
                }
                return;
            }
        }
        cout << "Book not found!\n";
    }

    // Return a book
    void returnBook() {
        string isbn;
        cout << "\nEnter ISBN of book to return: ";
        getline(cin, isbn);

        for(Book& book : books) {
            if(book.isbn == isbn) {
                if(!book.isAvailable) {
                    book.isAvailable = true;
                    cout << "Book returned successfully!\n";
                } else {
                    cout << "Book was not borrowed!\n";
                }
                return;
            }
        }
        cout << "Book not found!\n";
    }
};

// Main menu
int main() {
    Library library;
    int choice;

    do {
        cout << "\n=== Library System ===\n"
             << "1. Add Book\n"
             << "2. Show All Books\n"
             << "3. Borrow Book\n"
             << "4. Return Book\n"
             << "5. Exit\n"
             << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch(choice) {
            case 1:
                library.addBook();
                break;
            case 2:
                library.showAllBooks();
                break;
            case 3:
                library.borrowBook();
                break;
            case 4:
                library.returnBook();
                break;
            case 5:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 5);

    return 0;
}
