/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>

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

int main(void){
	printf("%d\n", is_prime(1));   // 1 is not a prime.       Should print 0.
	printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
	printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
	printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
