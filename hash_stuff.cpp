/**
    @author [mst]
    @file   hash_stuff.cpp
    @brief  hash tables and maps related
    full/optional description: this is a placeholder
    template for new files creation

    Gains:
    -STL built in hash options
    -[wip] manual hash map implementation

    features, changelog:
    -2022.11:	-initial draft

    @version 0.1 2022.11
*/


////////////////// LIBS
#include <iostream>            // usage of console prints
#include <map>
#include <unordered_map>
#include <string>


////////////////// DECL_IMPL


// [wiki] a hash table is a key-value structure that uses a pre-defined
// hash function to map or search an index of a member
// we implement it here as a pointer to pointers of hash nodes (entries)
class hashEntry
{
private:
    /* data */
public:
    hashEntry(/* args */);
    ~hashEntry();
};

hashEntry::hashEntry(/* args */)
{
}

hashEntry::~hashEntry()
{
}



////////////////// DRIVER
int main()
{
    using namespace std;    
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

    

    

	cin.get(); // pseudo-pause the console
	return 0;
}
