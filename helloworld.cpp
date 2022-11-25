/**
    @author [mst]
    @file   helloworld.cpp    
    @brief  Basic cpp familiarity

    features, changelog:
    -2022.11: initial template draft
	-2022.11: static and dynamic allocation, vector operation
	-2022.11: various constructors demo (copy/move)

    @version 0.1 2022.11
*/


////////////////// LIBS
#include <iostream>            // usage of console prints
#include <vector>
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
        std::cout << "move" << std::endl;
    }

    int Volume() { return m_width * m_height * m_length; }
    void Add_Item(string item) { m_contents.push_back(item); }
    void Print_Contents() { for (const auto& item : m_contents) cout << item << " ";}
};

// standalone Box generation
Box get_Box()
{
    Box b(5, 10, 18); // "int,int,int" constructor will be called
    b.Add_Item("Toupee");
    b.Add_Item("Megaphone");
    b.Add_Item("Suit");
    return b;
}

////////////////// DRIVER
int main()
{
    // [bp] putting this in the global space is an overhead
    // even worse in a header file as would foce including in all users
    //using namespace std;
    
    // [bp] using endl would force a flush.                            
	cout << "[mst] hello world" << '\n' << '\n';


    // pointers
    int x = 1;
    int *p = &x;
    //int &&q = p; [wip] document the double reference operator

	// [demo] different constructors and behaviors
	Box b; // "default" constructor
    Box b1(b); // "copy" constructor will deep copy data from the original instance
    Box b2(get_Box()); // the rvalue argument will call "move" constructor, the created box will be moved under b2
    //[wip] why 'move' string is not printed? [here]
    cout << "b2 contents: ";
    b2.Print_Contents(); // Prove that we have all the values


    


	// [demo] array declaration and initialization
	const int length = 3;	// the size is const
	int stack_array[length] = { 0, 32, 54 };		// this will cteate an (static)  array on the stack for the current scope (no delete needed)
	int* array = new int[length];					// this will create an (dynamic) array on the heap. we have to delete it when done
	memcpy(array, stack_array,  sizeof(stack_array));

	// [demo] using 'auto' for type inference and a more generic approach. will not work for dynamic array pointer
    for (const auto& member : stack_array) {		
		std::cout << member << ", ";
	}

	delete[] array;

    // build a vector from an array
	vector<int> arr_vec;
	for (const auto& member : stack_array) {
		arr_vec.push_back(member);
	}


	// cin.get(); // pseudo-pause the console
	return 0;
}
