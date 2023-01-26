//
// [mst] kmp_substring1.cpp
// practicing a substring searching with a Knuth-Morris-Pratt(KMP) Pattern Matching algorithm
// based on: https://youtu.be/GTJr8OvyEVQ
//
// gains:
// - KMP algorithm
// - console prints coloring :)
//
// features, changelog:
// - initial. c style, naive implementation
// - 2020.12.25 full kmp implementation
//		- added assisting color-coded debug prints

////////////////// LIBS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h> // WinApi header, for console recoloring

#define DEBUG 1

// color console prints like a boss
#define CLR_DEF 7
#define CLR_RED 12
#define CLR_GRN 10
#define SET_CLR_DEF SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CLR_DEF);
#define SET_CLR_RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CLR_RED);
#define SET_CLR_GRN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CLR_GRN);


#define printf_red(X) SET_CLR_RED printf(#X); SET_CLR_DEF
#define printf_grn(X) SET_CLR_GRN printf(X); SET_CLR_DEF


////////////////// DECL_IMPL


// a defined printf modified
//
void printf_redd() {
	//printf("---iterating:\nstr: %s\n", str_ptr);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CLR_GRN);
	//printf("pat: %*s\n", pat_len + i, patt);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CLR_DEF);
}

// print an array
//
void print_arr(const int* arr, int n) {
	for (int k = 0; k < n; k++){
		printf("%d ", arr[k]);
	}
	putchar('\n');
}

// print an array and signal given char in color
//
void print_arr_point(const int* arr, int n, int i, int clr) {
	for (int k = 0; k < n; k++){
		if (k == i) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr); }
		printf("%d ", arr[k]);
		if (k == i) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CLR_DEF); }
	}

	putchar('\n');
}

// print a char array string
//
void print_str(const char* str) {
	for (int k = 0; k < strlen(str); k++){
		printf("%c ", str[k]);
	}
	putchar('\n');
}

// print a char array string and signal given chars range in color
//
void print_str_point(const char* arr, int i, int j, int clr) {
	for (int k = 0; k < strlen(arr); k++){
		if ((k >= i) && (k<=j)) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr); }
		printf("%c", arr[k]);
		if ((k >= i) && (k <= j)) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CLR_DEF); }
	}

	putchar('\n');
}



// a naive substring pattern search. simply iterate strcmp at each index.
// targeted at O(n*m) time
//
int substr_naive(const char *str, const char *patt)
{
	const char *str_ptr = str;	// record for full string visibility
	int i = 0;
	int pat_len = strlen(patt);

	printf("searching substring. naive method\n");
	while (*str)
	{
		// compare for each char index of the searched text
		if (0 == strncmp(str, patt, pat_len)) {
			if (DEBUG){
				printf("---iterating:\nstr: %s\n", str_ptr);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CLR_GRN);
				printf("pat: %*s\n", pat_len + i, patt);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CLR_DEF);
			}
			return i;
		}
		else
		{
			if (DEBUG){
				printf("---iterating:\nstr: %s\n", str_ptr);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CLR_RED);
				printf("pat: %*s\n", pat_len + i, patt);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CLR_DEF);
			}
			i++;
			str++;
		}
	}
	return -1;
}


// a KMP (Knuth-Morris-Pratt algorithm) substring pattern search:
// targeted at O(n+m) time
//
int substr_kmp(const char *str, const char *patt)
{
	int result = -1;
	const char *str_ptr = str;	// record for full string visibility
	int str_len_s = strlen(str);
	int str_len_p = strlen(patt);
	if (str_len_s < str_len_p) return -1;

	// building the pattern's temp array
	printf("kmp array for the pattern:\n", patt);
	print_str(patt);
	int * occurences;
	occurences = new int[str_len_p]{};	// initted to zeroes
	int i = 1;
	int j = 0;
	for (; i < str_len_p; i++) {
		if (patt[j] == patt[i]) {
			occurences[i] = j + 1;
			j++;
		}
		else if (j != 0) {
			j = occurences[j - 1];
			i--;	// realign i to compare again
		}
	}
	print_arr(occurences, str_len_p);

	// now lets go and match that pattern
	i = j = 0;
	if (DEBUG){ printf("\nstr|pat\n---|---\n"); }	// header
	while ((i < str_len_s) || (j < str_len_p)){
		// match found
		if (str[i] == patt[j]) {
			if (DEBUG) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CLR_GRN);
				printf(" %c = %c \n", str[i], patt[j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CLR_DEF);
			}
			j++;
			i++;

			// once we found the pattern once, we exit and return the index
			if (j == str_len_p) {
				result = i - str_len_p;
				break;
			}
		} // match found

		// no match
		else {
			if (DEBUG) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CLR_RED);
				printf(" %c ! %c ", str[i], patt[j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CLR_DEF);
				if (j > 0) {
					printf("  ==>  pattern ptr moves to index: ");
					print_arr_point(occurences, str_len_p, j - 1, CLR_RED);
				}
				else{
					putchar('\n');
				}
			}
			if (j > 0) { j = occurences[j - 1]; }	// continue matching from a prefix
			else { i++; }
		} // no match

	}

	// cleanup
	delete (occurences);

	// report if pattern found
	return result;
}


////////////////// DRIVER
int main(int argc, char *argv[])
{
	printf("[mst] Knuth-Morris-Pratt(KMP) Pattern Matching algorithm doodle\n");
	int res = -1;

	// naive run
	char text1[]		= "abckkkabcxkkkabc";
	char substr1[]	= "abcx";
	printf("\nnaive pattern search (nested loop): %s in string: %s\n", substr1, text1);
	res = substr_naive(text1, substr1);
	if (-1 != res) printf("found a substring at index %d\n", res);


	// some substrings to test the occurence array building
	//char *substr = "abcdabca";
	//char *substr = "aabaabaaa";

	char text[] = "abxabcabcabcaby";
	char substr[] = "abcaby";
	printf("\n\nKMP-matching pattern: %s in string: %s\n", substr, text);
	res = substr_kmp(text, substr);
	if (-1 != res) {
		printf("found a substring at index %d:\n", res);
		print_str_point(text, res, res + strlen(substr), CLR_GRN);
	}

	char text2[] = "abcxabcdabxabcdabcdabcy";
	char substr2[] = "abcdabcy";
	printf("\n\nKMP-matching pattern: %s in string: %s\n", substr2, text2);
	res = substr_kmp(text2, substr2);
	if (-1 != res) {
		printf("found a substring at index %d:\n", res);
		print_str_point(text2, res, res + strlen(substr2), CLR_GRN);
	}

	getchar();
}