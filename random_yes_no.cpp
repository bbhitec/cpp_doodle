/**
    @author [mst]
    @file   random_yes_no.cpp
    @brief  simple yes/no randomizer

    features, changelog:
    -2022.04: converted to cpp
    -pre2020: c version

    @version 0.2 2022.04
*/

#include <time.h>
#include <iostream>
#include <cstdlib>

int main ()
{
	using namespace std;

	int i;

	cout << "[mst] simple randomizer! press to roll!" << '\n';
	cin.get();	// empty input
	cin.sync(); // discard remaining buffer

	srand(time(0));
	i = rand()%2;

	cout << ((i)?"yes":"no") << '\n';

	cin.get(); // pseudo-pause the console
	return 0;
}
