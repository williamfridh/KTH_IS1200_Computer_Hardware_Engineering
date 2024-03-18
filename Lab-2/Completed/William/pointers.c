#include <stdio.h>
#include <stdlib.h>


char*	text1	 		= "This is a string.";								// Preset value
char*	text2	 		= "Yet another thing.";								// Preset value
int		count			= 0;												// Initial value set
int*	list1;																// No inital value needed
int*	list2;																// No inital value needed


void copycodes(char* textAddr, int* listAddr, int* countAddr) {
	while(*textAddr != 0){													// Loop while content (not 00)
		*listAddr = *textAddr;												// Copy data
		textAddr += 1;														// Increment text address
		listAddr += 1;														// Increment list address
		(*countAddr)++;														// Increment count
	}
}


void work() {
	copycodes(text1, list1, &count);										// Call copycodes first round
	copycodes(text2, list2, &count);										// Call copycodes second round
}


void printlist(const int* lst){
	printf("ASCII codes and corresponding characters.\n");
	while(*lst != 0){
		printf("0x%03X '%c' ", *lst, (char)*lst);
		lst++;
	}
	printf("\n");
}


void endian_proof(const char* c){
	printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
				 (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
	
}


int main(void){

	list1 = (int*)malloc(80);												// Declare memory
	list2 = (int*)malloc(80);												// Declare memory

	work();

	printf("\nlist1: ");
	printlist(list1);
	printf("\nlist2: ");
	printlist(list2);
	printf("\nCount = %d\n", count);

	endian_proof((char*) &count);

	free(list1);															// Free memory
	free(list2);															// Free memory
}

