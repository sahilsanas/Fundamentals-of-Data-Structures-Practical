//============================================================================
// Name        : Assignment_5.cpp
// Author      : Sahil Sanas
// Version     :
// Copyright   : Your copyright notice
// Description : Hashing with separate chaining
//============================================================================
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string key;
    string value;
    Node* next;

    Node(string key, string value) : key(key), value(value), next(nullptr) {}
};

class Dictionary {
private:
    Node** table;
    int tablesize;

    int hash(const string& key) {
        int hashValue = 0;
        for (char c : key) {
            hashValue += c;
        }
        return hashValue % tablesize;
    }

public:
    Dictionary(int size) {
        tablesize = size;
        table = new Node*[tablesize];
        for (int i = 0; i < tablesize; i++) {
            table[i] = nullptr;
        }
    }

    ~Dictionary() {
        for (int i = 0; i < tablesize; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insert(const string& key, const string& value) {
        int index = hash(key);
        Node* newNode = new Node(key, value);
        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            newNode->next = table[index];
            table[index] = newNode;
        }
    }

    string find(const string& key) {
        int index = hash(key);
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return "Key not found!";
    }

    void deleteKey(const string& key) {
        int index = hash(key);
        Node* current = table[index];
        Node* prev = nullptr;
        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                cout << "Deleted key: " << key << endl;
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "Key not found!" << endl;
    }

    void display() {
        for (int i = 0; i < tablesize; i++) {
            if (table[i] != nullptr) {
                Node* current = table[i];
                cout << "Index " << i << ": ";
                while (current != nullptr) {
                    cout << "(" << current->key << ", " << current->value << ") -> ";
                    current = current->next;
                }
                cout << "nullptr" << endl;
            }
        }
    }
};

int main() {
    Dictionary dict(10);
    int choice;
    string key, value;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Find\n";
        cout << "3. Delete\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key: ";
                cin >> key;
                cout << "Enter value: ";
                cin >> value;
                dict.insert(key, value);
                break;

            case 2:
                cout << "Enter key to find: ";
                cin >> key;
                cout << "Value: " << dict.find(key) << endl;
                break;

            case 3:
                cout << "Enter key to delete: ";
                cin >> key;
                dict.deleteKey(key);
                break;

            case 4:
                dict.display();
                break;

            case 5:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
