/**
    @author [mst]
    @file   helloworld.cpp
    @brief  Basic cpp familiarity

    features, gains:
    -2023.01: more iterators and inputs stuff
    -2022.11: initial template draft
	-2022.11: static and dynamic allocation, vector operation
	-2022.11: various constructors demo (copy/move)

    @version 0.1 2022.11
*/


////////////////// LIBS
#include <iostream>             // usage of console prints
#include <vector>
#include <bits/stdc++.h>        // usage of: find_if
using namespace std;

////////////////// DECL_IMPL

// will demonstrate different constructor types
// more examples: https://www.geeksforgeeks.org/move-constructors-in-c-with-examples/
class Box {
private:
    int m_width{ 0 };	// [bp] 'm_' prefix is for 'member', default value is 0
    int m_height{ 0 };
    int m_length{ 0 };
    vector<string> m_contents;

public:
    // [demo] default constructor with two ways to init a member value
    Box() : m_width(0){
        m_width = 0;
        std::cout << "default" << std::endl;
    }
    // overloaded constructor - compile time polymorphism
    Box(int width, int height, int length) : m_width(width), m_height(height), m_length(length) {
        std::cout << "int,int,int" << std::endl;
    }
	// copy constructor - will copy the actual data
    Box(Box& other)  : m_width(other.m_width), m_height(other.m_height), m_length(other.m_length) {
        std::cout << "copy" << std::endl;
    }
	// move constructor - will point to already existing object (r-value referencing)
    Box(Box&& other) : m_width(other.m_width), m_height(other.m_height), m_length(other.m_length) {
        m_contents = std::move(other.m_contents);
        other.m_width  = 0;
        other.m_height = 0;
        other.m_length = 0;
        std::cout << "move" << std::endl;
    }
    friend ostream& operator<<(ostream &os, const Box& box);

    int Volume() { return m_width * m_height * m_length; }
    void Add_Item(string item) { m_contents.push_back(item); }
    void Print_Contents() { for (const auto& item : m_contents) cout << item << " ";}
};

// [demo] overloading stream operator for a print
    ostream& operator<<(ostream &os, const Box& box){
        for (const auto& item : box.m_contents) os << item << " ";
        return os;
    }

// standalone Box generation
Box get_Box()
{
    Box b(5, 10, 18); // "int,int,int" constructor will be called
    b.Add_Item("Toupee");
    b.Add_Item("Megaphone");
    b.Add_Item("Suit");
    return b;
}



string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not_fn(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not_fn(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

// [demo] handling basic inputs with getline. not error-checked!
void inputs_getline() {
    string n_temp;
    // [demo][bp] using cin >> n_temp would terminate input on a space!
    getline(cin, n_temp);

    // ASCII to integer
    int n = stoi(ltrim(rtrim(n_temp)));
    cout << "trimmed input: " << n << endl;

    string s = "Hello";
    cout << s + n_temp << endl;
}

// [demo] handling basic inputs with cin
void inputs_cin_check(){
    int x;
    cout << "Enter number: ";
    cin >> x;

    // [demo] requesting re-entry on a bad input
    while (cin.fail()) {
        cin.clear();    // clear the fail flag;
        cin.ignore(INT_MAX, '\n');   // ignore previous stream (or op to a new-line)
        cout << "Bad input. Please try again: ";
        cin >> x;
    }
    cout << x << " is a correct input!" << endl;
}




////////////////// DRIVER
int main()
{
    // [bp] putting this in the global space is an overhead
    // even worse in a header file as would foce including in all users
    //using namespace std;

    // [bp] using endl will force a flush, sometimes we don't need to
	cout << "[mst] hello world" << '\n' << '\n';


    ////////////// POINTERS
    int x = 1;
    int *p = &x;
    //int &&q = p; [wip] document the double reference operator


	////////////// CONSTRUCTORS
    // [demo] different constructors and behaviors
	// Box b; // "default" constructor
    // Box b1(b); // "copy" constructor (that we have overridden) will deep copy data from the original instance
    Box b2(get_Box()); // the rvalue argument will call "int int int" constructor, the created box will be  under b2
    // Box b3 = b2;    // will also invoke copy constructor;
    Box b4 = move(b2);  // this will invoke the move constructor;
    //[wip] why 'move' string is not printed? [here]
    cout << "b4 contents: ";
    // b2.Print_Contents(); // Prove that we have all the values
    cout << b4; // overloaded << operator
    cout << endl;
    cout << "b2 contents after 'move': ";
    cout << b2; // the moved members of b2 are nulled
    cout << endl << endl;


    ////////////// ARRAYS and VECTORS
	// [demo] array declaration and initialization
	const int length = 3;	// the size is const
	int stack_array[length] = { 0, 32, 54 };		// this will cteate an (static)  array on the stack for the current scope (no delete needed)
	int* array = new int[length];					// this will create an (dynamic) array on the heap. we have to delete it when done
	memcpy(array, stack_array,  sizeof(stack_array));

	// [demo] using 'auto' for type inference and a more generic approach. will not work for dynamic array pointer
    for (const auto& member : stack_array) {
		std::cout << member << ", ";
	}
    cout << endl;

	delete[] array;

    // build a vector from an array
	vector<int> arr_vec;
	for (const auto& member : stack_array) {
		arr_vec.push_back(member);
	}

    // [demo] another way for an iterator based loop
    for (auto i = arr_vec.begin(); i != arr_vec.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;

    // 2D vector initialization
    vector<vector<int>> vect
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };



    ////////////// INPUTS
    // inputs_getline();
    // inputs_cin_check();



	// cin.get(); // pseudo-pause the console
	return 0;
}
