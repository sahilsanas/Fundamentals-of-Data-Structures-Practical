//============================================================================
// Name        : Assignment_4.cpp
// Author      : Sahil Sanas
// Version     :
// Copyright   : Your copyright notice
// Description : Hashing with Linear Probing
//============================================================================
#include <iostream>
#include <string>
using namespace std;

class Client {
private:
    string name;
    string teleno;

public:
    Client(string name = "", string teleno = "") : name(name), teleno(teleno) {}

    void display() const {
        cout << name << " - " << teleno << endl;
    }

    bool isEmpty() const {
        return name == "";
    }

    bool isEqual(const string& key) const {
        return name == key;
    }

    friend class HashTable;
};

class HashTable {
private:
    Client* table;
    int size;

    int HashFunction(string key) {
        int sum = 0;
        for (char c : key)
            sum += int(c);
        return sum % size;
    }

    void printTable() {
        for (int i = 0; i < size; ++i) {
            cout << "Index " << i << ": ";
            if (!table[i].isEmpty()) {
                table[i].display();
            } else {
                cout << "_" << endl;
            }
        }
        cout << "-----------------------------\n";
    }

public:
    HashTable(int size) : size(size) {
        table = new Client[size];
    }

    ~HashTable() {
        delete[] table;
    }

    void LinearProbingWithoutReplacement(string name, string teleno) {
        int index = HashFunction(name);
        int start = index;

        do {
            if (table[index].isEmpty()) {
                table[index] = Client(name, teleno);
                break;
            }
            index = (index + 1) % size;
        } while (index != start);

        printTable();
    }

    void LinearProbingWithReplacement(string name, string teleno) {
        int index = HashFunction(name);

        if (table[index].isEmpty()) {
            table[index] = Client(name, teleno);
        } else {
            int existingHash = HashFunction(table[index].name);
            if (existingHash != index) {
                for (int i = size - 1; i >= 0; --i) {
                    if (table[i].isEmpty()) {
                        table[i] = Client(name, teleno);
                        break;
                    }
                }
            } else {
                int newIndex = (index + 1) % size;
                while (!table[newIndex].isEmpty()) {
                    newIndex = (newIndex + 1) % size;
                }
                table[newIndex] = Client(name, teleno);
            }
        }

        printTable();
    }
};

int main() {
    int size = 10;
    HashTable h1(size), h2(size);

    h1.LinearProbingWithoutReplacement("Sahil", "70");
    h1.LinearProbingWithoutReplacement("Om", "71");
    h1.LinearProbingWithoutReplacement("Sanveg", "72");
    h1.LinearProbingWithoutReplacement("Ben", "73");

    h2.LinearProbingWithReplacement("Sahil", "80");
    h2.LinearProbingWithReplacement("Om", "81");
    h2.LinearProbingWithReplacement("Sanveg", "82");
    h2.LinearProbingWithReplacement("Ben", "83");

    return 0;
}

