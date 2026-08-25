#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <cctype>

using namespace std;

// ===============================
// BOOK CLASS
// ===============================

class Book {
private:
    int bookId;
    string title;
    string author;
    bool issued;
    int issuedTo;

public:

    Book() {
        bookId = 0;
        title = "";
        author = "";
        issued = false;
        issuedTo = 0;
    }

    // Add book details
    void input() {

        cout << "\nEnter Book ID: ";
        cin >> bookId;
        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        issued = false;
        issuedTo = 0;
    }

    // Display book details
    void display() const {

        cout << left
             << setw(10) << bookId
             << setw(30) << title
             << setw(25) << author;

        if (issued)
            cout << setw(15) << "Issued";
        else
            cout << setw(15) << "Available";

        cout << endl;
    }

    int getBookId() const {
        return bookId;
    }

    string getTitle() const {
        return title;
    }

    string getAuthor() const {
        return author;
    }

    bool isIssued() const {
        return issued;
    }

    int getIssuedTo() const {
        return issuedTo;
    }

    void issueBook(int memberId) {
        issued = true;
        issuedTo = memberId;
    }

    void returnBook() {
        issued = false;
        issuedTo = 0;
    }

    // Save book to file
    void saveToFile(ofstream &file) const {

        file << bookId << "|"
             << title << "|"
             << author << "|"
             << issued << "|"
             << issuedTo << endl;
    }

    // Load book from file
    bool loadFromLine(string line) {

        size_t pos;

        // Book ID
        pos = line.find("|");

        if (pos == string::npos)
            return false;

        bookId = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        // Title
        pos = line.find("|");

        if (pos == string::npos)
            return false;

        title = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Author
        pos = line.find("|");

        if (pos == string::npos)
            return false;

        author = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Issued status
        pos = line.find("|");

        if (pos == string::npos)
            return false;

        issued = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        // Member ID
        issuedTo = stoi(line);

        return true;
    }
};


// ===============================
// MEMBER CLASS
// ===============================

class Member {
private:
    int memberId;
    string name;
    string phone;

public:

    Member() {
        memberId = 0;
        name = "";
        phone = "";
    }

    // Add member
    void input() {

        cout << "\nEnter Member ID: ";
        cin >> memberId;
        cin.ignore();

        cout << "Enter Member Name: ";
        getline(cin, name);

        cout << "Enter Phone Number: ";
        getline(cin, phone);
    }

    // Display member
    void display() const {

        cout << left
             << setw(12) << memberId
             << setw(30) << name
             << setw(20) << phone
             << endl;
    }

    int getMemberId() const {
        return memberId;
    }

    // Save member to file
    void saveToFile(ofstream &file) const {

        file << memberId << "|"
             << name << "|"
             << phone << endl;
    }

    // Load member from file
    bool loadFromLine(string line) {

        size_t pos;

        // Member ID
        pos = line.find("|");

        if (pos == string::npos)
            return false;

        memberId = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        // Name
        pos = line.find("|");

        if (pos == string::npos)
            return false;

        name = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Phone
        phone = line;

        return true;
    }
};


// ===============================
// CHECK MEMBER
// ===============================

bool memberExists(int memberId) {

    ifstream file("members.txt");

    if (!file)
        return false;

    string line;

    while (getline(file, line)) {

        Member member;

        if (member.loadFromLine(line)) {

            if (member.getMemberId() == memberId) {

                file.close();
                return true;
            }
        }
    }

    file.close();

    return false;
}


// ===============================
// CHECK BOOK
// ===============================

bool bookExists(int bookId) {

    ifstream file("books.txt");

    if (!file)
        return false;

    string line;

    while (getline(file, line)) {

        Book book;

        if (book.loadFromLine(line)) {

            if (book.getBookId() == bookId) {

                file.close();
                return true;
            }
        }
    }

    file.close();

    return false;
}


// ===============================
// ADD BOOK
// ===============================

void addBook() {

    Book book;

    book.input();

    if (bookExists(book.getBookId())) {

        cout << "\nBook ID already exists!\n";
        return;
    }

    ofstream file("books.txt", ios::app);

    if (!file) {

        cout << "\nError opening books file!\n";
        return;
    }

    book.saveToFile(file);

    file.close();

    cout << "\nBook added successfully!\n";
}


// ===============================
// ADD MEMBER
// ===============================

void addMember() {

    Member member;

    member.input();

    if (memberExists(member.getMemberId())) {

        cout << "\nMember ID already exists!\n";
        return;
    }

    ofstream file("members.txt", ios::app);

    if (!file) {

        cout << "\nError opening members file!\n";
        return;
    }

    member.saveToFile(file);

    file.close();

    cout << "\nMember added successfully!\n";
}


// ===============================
// DISPLAY ALL BOOKS
// ===============================

void displayBooks() {

    ifstream file("books.txt");

    if (!file) {

        cout << "\nNo books found!\n";
        return;
    }

    string line;
    bool found = false;

    cout << "\n==============================================================\n";
    cout << "                     ALL BOOKS\n";
    cout << "==============================================================\n";

    cout << left
         << setw(10) << "Book ID"
         << setw(30) << "Title"
         << setw(25) << "Author"
         << setw(15) << "Status"
         << endl;

    cout << "--------------------------------------------------------------------------\n";

    while (getline(file, line)) {

        Book book;

        if (book.loadFromLine(line)) {

            book.display();

            found = true;
        }
    }

    if (!found)
        cout << "No books available.\n";

    file.close();
}


// ===============================
// DISPLAY ALL MEMBERS
// ===============================

void displayMembers() {

    ifstream file("members.txt");

    if (!file) {

        cout << "\nNo members found!\n";
        return;
    }

    string line;
    bool found = false;

    cout << "\n==============================================================\n";
    cout << "                    ALL MEMBERS\n";
    cout << "==============================================================\n";

    cout << left
         << setw(12) << "Member ID"
         << setw(30) << "Name"
         << setw(20) << "Phone"
         << endl;

    cout << "--------------------------------------------------------------\n";

    while (getline(file, line)) {

        Member member;

        if (member.loadFromLine(line)) {

            member.display();

            found = true;
        }
    }

    if (!found)
        cout << "No members available.\n";

    file.close();
}


// ===============================
// SEARCH BOOK
// ===============================

void searchBook() {

    int choice;

    cout << "\nSearch Book By:\n";
    cout << "1. Title\n";
    cout << "2. Author\n";
    cout << "Enter choice: ";

    cin >> choice;
    cin.ignore();

    string searchText;

    cout << "Enter search text: ";
    getline(cin, searchText);

    // Convert search text to lowercase
    transform(searchText.begin(),
              searchText.end(),
              searchText.begin(),
              ::tolower);

    ifstream file("books.txt");

    if (!file) {

        cout << "\nNo books found!\n";
        return;
    }

    string line;
    bool found = false;

    cout << "\nSearch Results:\n";

    cout << left
         << setw(10) << "Book ID"
         << setw(30) << "Title"
         << setw(25) << "Author"
         << setw(15) << "Status"
         << endl;

    cout << "--------------------------------------------------------------------------\n";

    while (getline(file, line)) {

        Book book;

        if (book.loadFromLine(line)) {

            string title = book.getTitle();
            string author = book.getAuthor();

            transform(title.begin(),
                      title.end(),
                      title.begin(),
                      ::tolower);

            transform(author.begin(),
                      author.end(),
                      author.begin(),
                      ::tolower);

            bool match = false;

            if (choice == 1 &&
                title.find(searchText) != string::npos) {

                match = true;
            }

            if (choice == 2 &&
                author.find(searchText) != string::npos) {

                match = true;
            }

            if (match) {

                book.display();
                found = true;
            }
        }
    }

    if (!found)
        cout << "No matching book found.\n";

    file.close();
}


// ===============================
// ISSUE BOOK
// ===============================

void issueBook() {

    int bookId;
    int memberId;

    cout << "\nEnter Book ID: ";
    cin >> bookId;

    cout << "Enter Member ID: ";
    cin >> memberId;

    if (!bookExists(bookId)) {

        cout << "\nBook not found!\n";
        return;
    }

    if (!memberExists(memberId)) {

        cout << "\nMember not found!\n";
        return;
    }

    ifstream file("books.txt");
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {

        Book book;

        if (book.loadFromLine(line)) {

            if (book.getBookId() == bookId) {

                found = true;

                if (book.isIssued()) {

                    cout << "\nBook is already issued!\n";

                    temp << line << endl;
                }
                else {

                    book.issueBook(memberId);

                    book.saveToFile(temp);

                    cout << "\nBook issued successfully!\n";
                }
            }
            else {

                temp << line << endl;
            }
        }
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found)
        cout << "\nBook not found!\n";
}


// ===============================
// RETURN BOOK
// ===============================

void returnBook() {

    int bookId;

    cout << "\nEnter Book ID: ";
    cin >> bookId;

    if (!bookExists(bookId)) {

        cout << "\nBook not found!\n";
        return;
    }

    ifstream file("books.txt");
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {

        Book book;

        if (book.loadFromLine(line)) {

            if (book.getBookId() == bookId) {

                found = true;

                if (!book.isIssued()) {

                    cout << "\nThis book is already available.\n";

                    temp << line << endl;
                }
                else {

                    book.returnBook();

                    book.saveToFile(temp);

                    cout << "\nBook returned successfully!\n";
                }
            }
            else {

                temp << line << endl;
            }
        }
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found)
        cout << "\nBook not found!\n";
}


// ===============================
// MAIN FUNCTION
// ===============================

int main() {

    int choice;

    do {

        cout << "\n\n==============================================\n";
        cout << "          LIBRARY MANAGEMENT SYSTEM\n";
        cout << "==============================================\n";

        cout << "1. Add Book\n";
        cout << "2. Add Member\n";
        cout << "3. Display All Books\n";
        cout << "4. Display All Members\n";
        cout << "5. Search Book\n";
        cout << "6. Issue Book\n";
        cout << "7. Return Book\n";
        cout << "8. Exit\n";

        cout << "==============================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                addBook();
                break;

            case 2:
                addMember();
                break;

            case 3:
                displayBooks();
                break;

            case 4:
                displayMembers();
                break;

            case 5:
                searchBook();
                break;

            case 6:
                issueBook();
                break;

            case 7:
                returnBook();
                break;

            case 8:
                cout << "\nThank you for using Library Management System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 8);

    return 0;
}
