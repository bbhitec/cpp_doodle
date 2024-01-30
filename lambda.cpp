/**
    @author [mst]
    @file   lambda.cpp
    @brief  Some lambda, STL cpp functionality doodles

	gains:
    -cpp for_each
    -basic lambda functions
	-using the function wrapper (C++11)


    @version 0.1 2023.02
*/

////////////////// LIBS
#include <iostream>         // usage of console prints
#include <vector>
#include <algorithm>		// usage of for_each
#include <functional>

using namespace std;


////////////////// DECL_IMPL

void print_vec(vector<int> nums) {
	string divider = ", ";
	cout << "the vector: ";

	// here we use lambda with a capture group (outer variables to be seen within the lambda)
    for_each(nums.begin(),nums.end(), [divider](int &x){cout << x << divider;});
	cout << endl;
}


void func_print(int x) {cout << "your number is: " << x << endl;};
void func_hi() {cout << "hello!" << endl;};


////////////////// DRIVER
int main()
{
	cout << "[mst] lambda doodle" << endl << endl;


	////////////// LAMBDA RELATED

	// using iterators, lambda and for_each for a sexy code
    vector<int> nums = {-4,-1,0,3,10};
	print_vec(nums);

	// square all and sort (used in leetcode 977)
	auto bgn = nums.begin();
    auto end = nums.end();

	// [demo] we can use lambda expression with an explicit return type (not needed here as an a reference is used)
	for_each(bgn,end,[](int &x) -> int {x*=x;});
    sort(bgn,end);

	print_vec(nums);

	////////////// FUNCTIONAL WRAPPER

    // [demo] using functional wrapper for any signature-fitting callable object
	function<void()> f = func_hi;
	f();

	function<void(int)> fp = func_print;
	fp(48);

	// or even a nameles lambda function
	auto f_lambda = [](int x) {cout << "whoa, its: " << x << endl;};
	function<void(int)> fl = f_lambda;
	fl(32);

	return 0;
}
