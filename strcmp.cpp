//
// [mst] strcmp.cpp strcmp doodle
// description
//
// features, changelog:
// -2021.10.11: -initial draft
// -[wip]
//


////////////////// LIBS
#include <iostream>            // usage of console prints

using namespace std;

////////////////// DECL_IMPL

int strcmp_me (string str1, string str2){

    if (str1.empty() || str2.empty()) {
        return -1;
    }

    // [here]

    /*
    int i = 0;
    while (str1.at(i) != '\n' && str2.at(i) != '\n') {
        if (str1.at(i) != str2.at(i)) {
            return -1;
        }
        std::cout << str1.at(i);
        i++;
    }
    */

    for ( std::string::iterator it=str1.begin(); it!=str1.end(); ++it) {
        std::cout << *it;
    }

    return 0;
}

////////////////// DRIVER
int main()
{
	cout << "[mst] strcmp doodle" << endl << endl;

    string teststr = "hello there";
    string substr = "hello";

    std::cout << "comparing \'" << teststr << "\' and \'" << substr << "\' ..." << std::endl;

    std::cout << strcmp_me(teststr, substr) << std::endl;


	//cin.get(); // pseudo-pause the console
	return 0;
}
