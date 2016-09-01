//this program prints out a block of text prompting the user for an int, the scans in that number and returns it. 

//this is the main C library your code will not work without this. 
#include <stdio.h>

//this is your main function. By including (void) you dont have to remember to add return 0 at the end of the function. 
/* this is a multi line 
comment for better spacial organization of longer comments. */

int main (void) {
  
  int userInput;
  //the printf cmd prints out a block of text you decide; the \n is to skip down one line
  printf("Please enter a number below\n");
  
  //this scans in an integer and assigns it to the int varible userInput
  scanf("%d", &userInput);
  
  printf("You entered the number %d", userInput);



}
