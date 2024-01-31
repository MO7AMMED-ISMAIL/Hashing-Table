#include <iostream>

using namespace std;

const int INITIAL_SIZE = 10;
const int GROWTH_FACTOR = 2;

class HashTable {
private:
    int* arr;
    int size;

public:
    HashTable(int initialSize = INITIAL_SIZE) {
        size = initialSize;
        arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = -1;
        }
    }

    ~HashTable() {
        delete[] arr;
    }

    int hashFunction(int key) {
        return key % size;
    }

    void rehash() {
        int oldSize = size;
        int* oldArr = arr;

        size *= GROWTH_FACTOR;
        arr = new int[size];

        for (int i = 0; i < size; i++) {
            arr[i] = -1;
        }

        for (int i = 0; i < oldSize; i++) {
            if (oldArr[i] != -1 && oldArr[i] != -2) {
                insert(oldArr[i]);
            }
        }

        delete[] oldArr;
    }

    void insert(int key) {
        int index = hashFunction(key);

        if (arr[index] == -1) {
            arr[index] = key;
        } else {
            // collision
            int i = 1;
            while (arr[(index + i) % size] != -1) {
                i++;
            }
            arr[(index + i) % size] = key;

            // Check if rehashing is needed
            if (i >= size / 2) {
                cout << "Rehashing..." << endl;
                rehash();
            }
        }
    }

    int remove(int key) {
        int index = hashFunction(key);
        int i = 0;
        while (arr[(index + i) % size] != -1) {
            if (arr[(index + i) % size] == key) {
                arr[(index + i) % size] = -2;
                cout << "Element deleted from the hash table" << endl;
                return 1;
            }
            i++;
        }
        cout << "Element not found in the hash table" << endl;
        return 0;
    }

    void display() {
        for (int i = 0; i < size; i++) {
            if (arr[i] == -1 || arr[i] == -2) {
                continue;
            }
            cout << "Index " << i << ": " << arr[i] << endl;
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

    // Uncomment the following lines to test rehashing
    // ht.remove(25);
    // ht.remove(35);
    // ht.insert(17); //Index: 7
    // ht.insert(18); //Index: 8

    cout << "Hash Table with Linear Probing:" << endl;
    ht.display();

    return 0;
}
