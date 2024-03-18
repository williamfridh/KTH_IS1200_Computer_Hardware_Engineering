/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6


/*
 Author: William Frid
 Date: 2023-01-31
 Input: int n, n > 0

 This function will print out prime numbers in ascending order starting at 2 up to (including) given number n.
 It will do this in 6 columns and insert linebreaks when needed.	
*/
int col = 0;						// Column index counter
void print_number(int n) {
	printf("%10d ", n);				// Print prime number in column
	col++;							// Increase column
	if (col == COLUMNS) {			// If it's time to jump line
		printf("\n");				// Jump line
		col = 0;					// Reset column index
	}
}


/*
 Author: William Frid
 Date: 2023-02-01
 Input: int n, n > 0

 This function will use Sieve of Eratosthenes to find all prime numbers equal to or less than given n.
 It will take the largest prime and send it to print_numbers.
*/
void print_sieves(int n){

	int arrLen = n;												// Store length for array
	char *arr = (char*)malloc(arrLen * sizeof(char));			// n bytes long array allocated in heap

    for (int i = 1; i < arrLen; i++) arr[i] = 1;             	// Loop each value 2 <= x < n and store in array

	for (int i = 1; i < arrLen; i++) {
		if (arr[i] == 0) continue;								// Skip iteration
		print_number(i+1);										// Print via print_number
		for (int j = i+i+1; j < arrLen; j+=i+1) arr[j] = 0;		// Loop upcoming indexes and set to zero if multiple
	}
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 
