/**
    @author [mst]
    @file   hash_stuff.cpp
    @brief  hash tables and maps related
    full/optional description: this is a placeholder
    template for new files creation

    Gains:
    -STL built in hash options
    -manual hash map implementation

    features, changelog:
    -2022.11:	-initial draft, manual implementation

    @version 0.1 2022.11
*/


////////////////// LIBS
#include <iostream>            // usage of console prints
#include <map>
#include <unordered_map>
#include <string>
using namespace std;
const int TABLE_SIZE = 128;

////////////////// DECL_IMPL


// [wiki] a hash table is a key-value structure that uses a pre-defined
// hash function to map or search an index of a member
// we implement it here as a pointer to pointers of hash nodes (entries)
class hashEntry {
public:
    int key;
    int val;
    // [wip] can be implemented as a linked list originating at a hashed key
    // example: https://github.com/DamienQuayle/Hash_Table
    hashEntry(int k, int v): key(k), val(v) {}
};

class hashMapTable {
private:
    hashEntry **table;
public:

    hashMapTable() {
        table = new hashEntry*[TABLE_SIZE]{nullptr}; // array of arrays, nullified
    }
    ~hashMapTable() {
         for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != nullptr)
               delete table[i];
            delete[] table;
         }
    }

    // a basic hashing function
    int hashFunc(int key) {
         return key % TABLE_SIZE;
    }

    int get (int key) {
        int hash = hashFunc(key);

        // hash-find the correct place for the member        
        while ((table[hash] != nullptr) && (table[hash]->key != key)) {
            hash = hashFunc(hash + 1);
        }

        if (table[hash] != NULL) return table[hash]->val;
        return -1;
    }

    void insert (int key, int value) {
        int hash = hashFunc(key);

        while ((table[hash] != nullptr) && (table[hash]->key != key)) {
            hash = hashFunc(hash + 1);
        }

        // clear if previous present
        if (table[hash] != NULL) delete table[hash];
        table[hash] = new hashEntry(key, value);
    }

    void remove (int key) {
        int hash = hashFunc(key);

        while ((table[hash] != nullptr) && (table[hash]->key != key)) {
            hash = hashFunc(hash + 1);
        }

        if (table[hash] != NULL) delete table[hash];
        return;

    }
};


////////////////// DRIVER
int main()
{
	cout << "[mst] hash map doodle" << '\n' << '\n';

    // [demo] we use unordered map for cases where iteration/traversal aren't necesary. O(1) indexing
    // example from: https://cppbyexample.com/hash_map.html
    unordered_map<int, string> status_messages = {
        {200, "Success"},
        {404, "This is not the page you're looking for"},
        {403, "Unauthorized"},
        {418, "I'm a teapot"},
    };

    // testing types
    int key1 = 404;
    cout << "key: " << key1 << " typeid<key>: " << typeid(key1).name() << '\n';
    cout << "value  " << status_messages[key1] << " typeid<value>: " << typeid(status_messages[key1]).name() << '\n';


    cout << endl << "[mst] manual implementation" << '\n';
    hashMapTable hash;
    int k, v;
    int c;

    while (1) {
      cout<<"1.Insert element into the table"<<endl;
      cout<<"2.Search element from the key"<<endl;
      cout<<"3.Delete element at a key"<<endl;
      cout<<"4.Exit"<<endl;
      cout<<"Enter your choice: ";
      cin>>c;
      switch(c) {
         case 1:
            cout<<"Enter element to be inserted: ";
            cin>>v;
            cout<<"Enter key at which element to be inserted: ";
            cin>>k;
            hash.insert(k, v);
         break;
         case 2:
            cout<<"Enter key of the element to be searched: ";
            cin>>k;
            if (hash.get(k) == -1) {
               cout<<"No element found at key "<<k<<endl;
               continue;
            } else {
               cout<<"Element at key "<<k<<" : ";
               cout<<hash.get(k)<<endl;
            }
         break;
         case 3:
            cout<<"Enter key of the element to be deleted: ";
            cin>>k;
            hash.remove(k);
         break;
         case 4:
            exit(1);
         default:
            cout<<"Enter correct option";
      }
   }   

    

	cin.get(); // pseudo-pause the console
	return 0;
}
