#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdio>

using namespace std;

// Student class
class Student {
public:
    int rollNo;
    string name;
    int age;
    string course;
    string phone;

    // Function to input student details
    void input() {
        cout << "\nEnter Roll Number: ";
        cin >> rollNo;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();

        cout << "Enter Course: ";
        getline(cin, course);

        cout << "Enter Phone Number: ";
        getline(cin, phone);
    }

    // Function to display student details
    void display() const {
        cout << left
             << setw(10) << rollNo
             << setw(25) << name
             << setw(8) << age
             << setw(20) << course
             << setw(15) << phone
             << endl;
    }
};

// Add a new student
void addStudent() {
    Student s;

    ofstream file("students.dat", ios::binary | ios::app);

    if (!file) {
        cout << "\nError opening file!\n";
        return;
    }

    s.input();
    file.write(reinterpret_cast<char*>(&s), sizeof(s));

    /*
       The above binary method cannot safely store std::string objects.
       Therefore, this function is replaced below by text-file handling.
    */

    file.close();
}

// Add student using text file
void addStudentText() {
    Student s;
    s.input();

    ofstream file("students.txt", ios::app);

    if (!file) {
        cout << "\nError opening file!\n";
        return;
    }

    file << s.rollNo << "|"
         << s.name << "|"
         << s.age << "|"
         << s.course << "|"
         << s.phone << endl;

    file.close();

    cout << "\nStudent added successfully!\n";
}

// Display all students
void displayStudents() {
    ifstream file("students.txt");

    if (!file) {
        cout << "\nNo student records found!\n";
        return;
    }

    Student s;
    string line;

    cout << "\n================ STUDENT RECORDS ================\n";

    cout << left
         << setw(10) << "Roll No"
         << setw(25) << "Name"
         << setw(8) << "Age"
         << setw(20) << "Course"
         << setw(15) << "Phone"
         << endl;

    cout << "--------------------------------------------------------------------------\n";

    bool found = false;

    while (getline(file, line)) {
        size_t pos;

        pos = line.find("|");
        if (pos == string::npos) continue;

        s.rollNo = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find("|");
        s.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find("|");
        s.age = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find("|");
        s.course = line.substr(0, pos);
        line.erase(0, pos + 1);

        s.phone = line;

        s.display();
        found = true;
    }

    if (!found) {
        cout << "No student records found!\n";
    }

    file.close();
}

// Search student
void searchStudent() {
    int roll;
    cout << "\nEnter Roll Number to search: ";
    cin >> roll;

    ifstream file("students.txt");

    if (!file) {
        cout << "\nNo student records found!\n";
        return;
    }

    Student s;
    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t pos;

        pos = line.find("|");
        if (pos == string::npos) continue;

        s.rollNo = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find("|");
        s.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find("|");
        s.age = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find("|");
        s.course = line.substr(0, pos);
        line.erase(0, pos + 1);

        s.phone = line;

        if (s.rollNo == roll) {
            cout << "\nStudent Found!\n";
            cout << "-----------------------------------\n";
            cout << "Roll Number : " << s.rollNo << endl;
            cout << "Name        : " << s.name << endl;
            cout << "Age         : " << s.age << endl;
            cout << "Course      : " << s.course << endl;
            cout << "Phone       : " << s.phone << endl;
            cout << "-----------------------------------\n";

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nStudent with Roll Number "
             << roll << " not found!\n";
    }

    file.close();
}

// Update student
void updateStudent() {
    int roll;
    cout << "\nEnter Roll Number to update: ";
    cin >> roll;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file || !temp) {
        cout << "\nError opening file!\n";
        return;
    }

    Student s;
    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t pos;

        pos = line.find("|");
        if (pos == string::npos) continue;

        s.rollNo = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find("|");
        s.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find("|");
        s.age = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find("|");
        s.course = line.substr(0, pos);
        line.erase(0, pos + 1);

        s.phone = line;

        if (s.rollNo == roll) {
            cout << "\nEnter new details:\n";

            Student updated;
            updated.rollNo = roll;

            cin.ignore();

            cout << "Enter Name: ";
            getline(cin, updated.name);

            cout << "Enter Age: ";
            cin >> updated.age;
            cin.ignore();

            cout << "Enter Course: ";
            getline(cin, updated.course);

            cout << "Enter Phone Number: ";
            getline(cin, updated.phone);

            temp << updated.rollNo << "|"
                 << updated.name << "|"
                 << updated.age << "|"
                 << updated.course << "|"
                 << updated.phone << endl;

            found = true;
        }
        else {
            temp << s.rollNo << "|"
                 << s.name << "|"
                 << s.age << "|"
                 << s.course << "|"
                 << s.phone << endl;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent updated successfully!\n";
    else
        cout << "\nStudent not found!\n";
}

// Delete student
void deleteStudent() {
    int roll;

    cout << "\nEnter Roll Number to delete: ";
    cin >> roll;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file || !temp) {
        cout << "\nError opening file!\n";
        return;
    }

    Student s;
    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t pos;

        pos = line.find("|");
        if (pos == string::npos) continue;

        s.rollNo = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find("|");
        s.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find("|");
        s.age = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find("|");
        s.course = line.substr(0, pos);
        line.erase(0, pos + 1);

        s.phone = line;

        if (s.rollNo == roll) {
            found = true;
            continue;
        }

        temp << s.rollNo << "|"
             << s.name << "|"
             << s.age << "|"
             << s.course << "|"
             << s.phone << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent deleted successfully!\n";
    else
        cout << "\nStudent not found!\n";
}

// Main function
int main() {

    int choice;

    do {
        cout << "\n\n============================================\n";
        cout << "       STUDENT MANAGEMENT SYSTEM\n";
        cout << "============================================\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "============================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                addStudentText();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                cout << "\nThank you for using Student Management System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
