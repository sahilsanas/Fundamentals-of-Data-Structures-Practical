//============================================================================
// Name        : Assignment_11.cpp
// Author      : Sahil Sanas
// Version     :
// Copyright   : Your copyright notice
// Description : Sequential File Handling
//============================================================================
#include <iostream>
#include <fstream>
using namespace std;

class Student {
public:
    int roll, div;
    string name, address;

    Student() {
        roll = div = 0;
        name = address = "";
    }

    void display() const {
        cout << name << " " << roll << " " << div << " " << address << endl;
    }

    void getData() {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter roll no: ";
        cin >> roll;
        cout << "Enter div: ";
        cin >> div;
        cout << "Enter address: ";
        cin >> address;
    }

    void writeToFile(ofstream& out) const {
        out << name << " " << roll << " " << div << " " << address << "\n";
    }

    bool readFromFile(ifstream& in) {
        return (bool)(in >> name >> roll >> div >> address);
    }
};

class MyFile {
    string filename;
    Student S;

public:
    MyFile() {
        cout << "Enter filename: ";
        cin >> filename;
        ofstream file(filename);  
        if (file)
            cout << "File opened successfully." << endl;
        else
            cout << "File opening error." << endl;
        file.close();
    }

    void addRecord() {
        ofstream file(filename, ios::app);
        S.getData();
        S.writeToFile(file);
        file.close();
    }

    void displayRecords() {
        ifstream file(filename);
        cout << "\n--- Student Records ---\n";
        while (S.readFromFile(file)) {
            S.display();
        }
        file.close();
    }

    void deleteRecord(int rollToDelete) {
        ifstream file(filename);
        ofstream temp("temp");
        bool found = false;

        while (S.readFromFile(file)) {
            if (S.roll == rollToDelete) {
                cout << "Deleting: ";
                S.display();
                found = true;
            } else {
                S.writeToFile(temp);
            }
        }

        if (!found)
            cout << "No such data exists." << endl;

        file.close();
        temp.close();

        remove(filename.c_str());
        rename("temp", filename.c_str());
    }
};

int main() {
    MyFile File;
    int Choice;
    int R;

    do {
        cout << "\n1: Add a record\n2: Display Database\n3: Delete a record\n4: Exit\nEnter your choice: ";
        cin >> Choice;

        switch (Choice) {
            case 1:
                File.addRecord();
                break;
            case 2:
                File.displayRecords();
                break;
            case 3:
                cout << "Enter the record you want to delete (roll no): ";
                cin >> R;
                File.deleteRecord(R);
                break;
            case 4:
                cout << "Exiting the program" << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (Choice != 4);

    return 0;
}
