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
 Return: int {0,1}
 Input: int n, n > 0

 This function will return 1 if the arugment is a prime number, otherwise 1
*/
int is_prime(int n) {
	if (n < 2) return 0;				// Not a prime (quick detection)
	int isPrime = 1;                    // Default is that the number is a prime
	for (int i = n - 1; i > 1; i--) {   // For loop that starts at n-1 and decreases
		if (n%i == 0) {       			// Don't have decimal = not prime
			isPrime = 0;                // Set result to 0
			break;                      // Leave loop
		}
	}
	return isPrime;                     // Return result
}

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
*/
void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS

	for (int i = 2; i <= n; i++) {		// Loop from 2 up to (including) given number n
		if (is_prime(i)) {				// Check if prime
			print_number(i);
		}
	}

	printf("\n");
  int amount = 0;
  int last_prime = 0;
	for (int i = 2; i <= n; i++) {		// Loop from 2 up to (including) given number n
		if (is_prime(i)) {				// Check if prime
			
			//printf("%d\n", (i-last_prime));
			if (i-last_prime == 8) amount++;
			last_prime = i;
		}
	}
	printf("%d\n", amount);
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 
