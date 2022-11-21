/**
    @author [mst]
    @file   helloworld.cpp    
    @brief  Basic cpp familiarity
    
    features, changelog:
    -2021.04: -initial template draft

    @version 0.1 2022.04
*/


////////////////// LIBS
#include <iostream>            // usage of console prints
#include <vector>



////////////////// DECL_IMPL


////////////////// DRIVER
int main()
{
    // [bp] putting this in the global space is an overhead
    // even worse in a header file as would foce including in all users
    using namespace std;
    
    // [bp] using endl would force a flush.                            
	cout << "[mst] hello world" << '\n' << '\n';


	// [demo] array declaration and initialization
	const int length = 3;	// the size is const
	int stack_array[length] = { 0, 32, 54 };		// this will cteate an (static)  array on the stack for the current scope (no delete needed)
	int* array = new int[length];					// this will create an (dynamic) array on the heap. we have to delete it when done
	memcpy(array, stack_array,  sizeof(stack_array));


    for (const auto& member : stack_array) {		// [demo] using 'auto' for type inference and a more generic approach. will not work for dynamic array pointer
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
