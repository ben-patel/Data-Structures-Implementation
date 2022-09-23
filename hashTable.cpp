/*
 *   Hash Table that uses key-value pairs, wheres key == int, value == string
 *   Compile using "g++ -std=c++11 -stdlib=libc++ hashTable.cpp" + "./a.out"
 */
#include <iostream>
#include <list>
#include <cstring>

/*
 * Uses an array of linked lists which contain key value pairs.
 */
class HashTable {
    private:
        // const number of lists
        static const int hashGroups = 10;
        std::list<std::pair<int, std::string> > table[hashGroups]; 
    
    public:
        bool isEmpty(); 
        int hashFunction(int key); // fetch value at key
        void insertItem(int key, std::string value); // insert key-val pair
        void removeItem(int key);
        void printTable();
        std::string getValue(int key);

};

// will return true if every list in table has size 0
bool HashTable::isEmpty() {
    for(int i = 0; i < hashGroups; i++) {
        if (table[i].size()) return false;
    }

    return true;
}

// returns index of given key
int HashTable::hashFunction(int key) {
    return key % hashGroups; // Key: 905 will return 5, which is the 6th list in the table.
}

// adds key value pair to tables
void HashTable::insertItem(int key, std::string value) {
    int hashValue = hashFunction(key);

    // point to list at given index
    auto& cell = table[hashValue]; 
    auto bgn = begin(cell);
    bool keyExists = false;

    for(; bgn != end(cell); bgn++) {
        if (bgn->first == key) {
            keyExists = true;
            bgn->second = value;
            std::cout << "Key exists, value has been replaced!" << '\n';
            break;
        }
    }

    if (!keyExists) {
        cell.emplace_back(key,value);
    }
    return;
}

// removes a given key-value pair from table
void HashTable::removeItem(int key) {
    int hashValue = hashFunction(key);

    auto&cell = table[hashValue];
    auto bgn = begin(cell);
    bool keyExists = false;

    for(; bgn != end(cell); bgn++) {
        if (bgn->first == key) {
            keyExists = true;
            bgn = cell.erase(bgn); // returns iterator to next 
            break;
        }
    }

    if (!keyExists) std::cout << "ERR: Key does not exist in table!\n" << '\n';
    return;
}

// iterates through table, printing each key-value pair
void HashTable::printTable() {
    for (int i = 0; i < hashGroups; i++) {
        if (table[i].size() == 0) continue;

        auto bgn = table[i].begin();
        for(; bgn != table[i].end(); bgn++) {
            std::cout << "Key : " << bgn->first << " Value: " << bgn->second << '\n';
        }
    }

    return;
}

// returns "null" if key not found, otherwise returns value
std::string HashTable::getValue(int key) {

    for(int i = 0; i < hashGroups; i++) {
        if (table[i].size() == 0) continue;
        auto bgn = table[i].begin();

        for(; bgn != table[i].end(); bgn++) {
            if (bgn->first == key) return bgn->second;
        }
    }

    std::cout << "ERR: Key does not in table!\n";
    return "null";
}

// testing
int main(void) {
    HashTable myHash;

    myHash.insertItem(203,"ben2");
    myHash.insertItem(204, "hello");
    myHash.insertItem(324, "benef");

    if (myHash.isEmpty()) {
        std::cout << "empty!" << std::endl;
    }

    myHash.printTable();
    myHash.removeItem(203);

    myHash.insertItem(2,"fsdfd");
    myHash.insertItem(2432,"fsdfd");
    myHash.insertItem(243,"fsdfd");
    myHash.insertItem(2432,"fsdfd");
    myHash.insertItem(24321,"fsdfd");
    myHash.insertItem(4322,"fsdfd");

    myHash.printTable();
    std::cout << myHash.getValue(204) << std::endl;

    myHash.removeItem(204);
    myHash.removeItem(2);
    myHash.removeItem(2432);
    myHash.removeItem(243);
    myHash.removeItem(24321);
    myHash.removeItem(4322);
    myHash.removeItem(324);

    myHash.printTable();
    if (myHash.isEmpty()) {
        std::cout << "empty!" << std::endl;
    }
    return 0;
}
