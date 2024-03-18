
#include <stdio.h>
#include <stdlib.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";
int* list1 = 0;                                               //Initialize both pointers for the lists, later in main we will allocate memory using malloc  
int* list2 = 0;                                               
int  count = 0;                                               //Count doesn't need to be initialised as a pointer, but we will still increment it at the address



void copy_codes(char *textP, int *listP, int *countAdd){      //Pointers to the text and list 

                                                  //Dereferencing textP makes the for-loop loop for each char in the text. 
    for(int i = 0; i < *textP; i++){              //Make a loop to copy of the values from the text into the list
      *listP = *textP;                            //Put in the first char into the list, dereferencing them both. 
      textP++;                                    //Increment both the text and list, dont need to dereference because we want the adress to increment
      listP++;                                    //If you increment the dereferenced pointer the value where the pointer is pointing will get updated
                                                  //The compiler knows the type of the pointers, meaning they increment with the correct value
      (*countAdd)++;                              //Increment count, but here we increment the value where count is pointing to 
    }
  } 

void work(){
  copy_codes(text1, list1, &count);               //Send text and list pointers to copy_codes function
  copy_codes(text2, list2, &count);               //Send the memory address from count directly to copy_code
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

  list1 = (int*) malloc(80);        //Allocate memory for the lists.(Making them an "array")
  list2 = (int*) malloc(80);        //Count doesn't need memory because it's not handle as an "array", 

  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);


  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);

  free(list1);
  free(list2);  
}