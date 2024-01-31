#include<iostream>

using namespace std;

const int SIZE = 10;

class HashTable {
private:
    int arr[SIZE];

public:
    HashTable() {
        for (int i = 0; i < SIZE; i++) {
            arr[i] = -1;
        }
    }

    int hashFunction(int key) {
        return key % SIZE;
    }

    void insert(int key) {
        int index = hashFunction(key);

        if (arr[index] == -1 ) {
            arr[index] = key;
        } else {
            // collision
            int i = 1;
            while (arr[(index + i) % SIZE] != -1 ) {
                i++;
            }
            arr[(index + i) % SIZE] = key;
        }
    }

    int remove(int key) {
        int index = hashFunction(key);
        int i = 0;
        while (arr[(index + i) % SIZE] != -1) {
            if (arr[(index + i) % SIZE] == key) {
                arr[(index + i) % SIZE] = -2;
                cout << "Element deleted from the hash table" << endl;
                return 1;
            }
            i++;
        }
        cout << "Element not found in the hash table" << endl;
        return 0;
    }

    void display() {
        for (int i = 0; i < SIZE; i++) {
            if (arr[i] == -1 || arr[i] == -2) {
                continue;
            }
            cout << "Index " << i << ": "<<arr[i]<<endl;
        }
    }
};

int main() {
    HashTable ht;

    ht.insert(5);  // Index: 5
    ht.insert(15); // Index: 6, Collision
    ht.insert(25); // Index: 7, Collision
    ht.insert(35); // Index: 8. Collision
    ht.insert(45); // Index: 9. Collision

    // ht.remove(25);
    // ht.remove(35);

    // ht.insert(17); //Index: 7
    // ht.insert(18); //Index: 8

    cout << "Hash Table with Linear Probing:" << endl;
    ht.display();

    return 0;
}
