/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>

int is_prime(int n){

	if(n <= 1){
		return 0;
	}

	int isPrime = 1;

	for(int i = n - 1; i > 1; i--){
    	if(n%i == 0){
    		isPrime = 0;
    		break;
      	}
  	}
return isPrime;
}


int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
