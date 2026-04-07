#include <iostream>
#include <fstream>
using namespace std;

class Student {
    int rollNo;
    char name[50];
    float marks;

public:
    void input() {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() const {
        cout << "\nRoll No: " << rollNo;
        cout << "\nName: " << name;
        cout << "\nMarks: " << marks << endl;
    }

    int getRollNo() const {
        return rollNo;
    }

    void updateMarks(float m) {
        marks = m;
    }
};


void addStudent() {
    Student s;
    ofstream out("students.dat", ios::binary | ios::app);

    s.input();
    out.write(reinterpret_cast<char*>(&s), sizeof(s));

    cout << "Student added successfully!\n";
    out.close();
}


void searchStudent(int roll) {
    Student s;
    ifstream in("students.dat", ios::binary);

    while (in.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.getRollNo() == roll) {
            s.display();
            return;
        }
    }

    cout << "Student not found!\n";
    in.close();
}


void updateStudent(int roll) {
    Student s;
    fstream file("students.dat", ios::binary | ios::in | ios::out);

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.getRollNo() == roll) {
            float newMarks;
            cout << "Enter new marks: ";
            cin >> newMarks;

            s.updateMarks(newMarks);

            int pos = -1 * sizeof(s);
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&s), sizeof(s));

            cout << "Marks updated!\n";
            return;
        }
    }

    cout << "Student not found!\n";
    file.close();
}


void deleteStudent(int roll) {
    Student s;
    ifstream in("students.dat", ios::binary);
    ofstream out("temp.dat", ios::binary);

    while (in.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.getRollNo() != roll) {
            out.write(reinterpret_cast<char*>(&s), sizeof(s));
        }
    }

    in.close();
    out.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    cout << "Student deleted if existed.\n";
}


int main() {
    int choice, roll;

    do {
        cout << "\n--- STUDENT MENU ---\n";
        cout << "1. Add Student\n";
        cout << "2. Search Student\n";
        cout << "3. Update Marks\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            cout << "Enter Roll No: ";
            cin >> roll;
            searchStudent(roll);
            break;
        case 3:
            cout << "Enter Roll No: ";
            cin >> roll;
            updateStudent(roll);
            break;
        case 4:
            cout << "Enter Roll No: ";
            cin >> roll;
            deleteStudent(roll);
            break;
        }
    } while (choice != 5);

    return 0;
}