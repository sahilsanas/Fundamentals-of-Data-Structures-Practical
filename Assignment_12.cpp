//============================================================================
// Name        : Assignment_12.cpp
// Author      : Sahil Sanas
// Version     :
// Copyright   : Your copyright notice
// Description : Direct Access File Handling
//============================================================================
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX_RECORDS = 10;

class Student {
    int rollNumber;
    char name[50];
    char address[100];

public:
    void readData() {
        cout << "Enter Roll Number: ";
        cin >> rollNumber;
        cin.ignore();
        cout << "Enter Name: ";
        cin.getline(name, 50);
        cout << "Enter Address: ";
        cin.getline(address, 100);
    }

    void displayData() {
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "---------------------" << endl;
    }

    int getRollNumber() const {
        return rollNumber;
    }
};

class StudentManagement {
    fstream file;

    int hashFunction(int rollNumber) {
        return rollNumber % MAX_RECORDS;
    }

public:
    void addStudent() {
        file.open("students.txt", ios::in | ios::out | ios::binary);
        Student student;
        student.readData();
        
        int position = hashFunction(student.getRollNumber());
        file.seekp(position * sizeof(Student), ios::beg);
        file.write(reinterpret_cast<char*>(&student), sizeof(Student));

        file.close();
        cout << "Student added successfully!" << endl;
    }

    void deleteStudent() {
        int rollNumber;
        cout << "Enter Roll Number of the student to delete: ";
        cin >> rollNumber;

        fstream tempFile;
        tempFile.open("temp.txt", ios::out | ios::binary);
        file.open("students.txt", ios::in | ios::binary);

        Student student;
        bool found = false;
        while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
            if (student.getRollNumber() != rollNumber) {
                tempFile.write(reinterpret_cast<char*>(&student), sizeof(Student));
            } else {
                found = true;
            }
        }

        file.close();
        tempFile.close();

        if (found) {
            remove("students.txt");
            rename("temp.txt", "students.txt");
            cout << "Student deleted successfully!" << endl;
        } else {
            cout << "Student not found!" << endl;
        }
    }

    void displayStudents() {
        file.open("students.txt", ios::in | ios::binary);
        Student student;

        while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
            student.displayData();
        }

        file.close();
    }
};

int main() {
    StudentManagement s;
    int choice;
    while (true) {
        cout << "Menu" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Delete Student" << endl;
        cout << "3. Display Students" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                s.addStudent();
                break;
            case 2:
                s.deleteStudent();
                break;
            case 3:
                s.displayStudents();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
        cout << endl;
    }
    return 0;
}
