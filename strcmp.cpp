//
// [mst] strcmp.cpp strcmp doodle
// simple string comparison run
//
// features, changelog:
// -2021.10.11: -initial draft
//


////////////////// LIBS
#include <iostream>            // usage of console prints

using namespace std;

////////////////// DECL_IMPL

int strcmp_me (string str1, string str2){

    if (str1.empty() || str2.empty()) {
        return -1;
    }

    // iterate the substring
    for (auto i = 0; i< str2.size(); i++) {
        if (str1[i] != str2[i]) return -1;
    }

    return 1;
}

////////////////// DRIVER
int main()
{
	cout << "[mst] strcmp doodle" << endl << endl;

    string teststr = "hello there";
    string substr = "hello";

    std::cout << "comparing \'" << teststr << "\' and \'" << substr << "\' ..." << std::endl << std::endl;

    std::cout << strcmp_me(teststr, substr) << std::endl;


	//cin.get(); // pseudo-pause the console
	return 0;
}
