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



////////////////// DECL_IMPL



////////////////// DRIVER
int main()
{
    // [bp] putting this in the global space is an overhead
    // even worse in a header file as would foce including in all users
    using namespace std;
    
    // [bp] using endl would force a flush.                            
	cout << "[mst] hello world" << '\n' << '\n';

	cin.get(); // pseudo-pause the console
	return 0;
}
