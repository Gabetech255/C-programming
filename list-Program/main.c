
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.c"

int main(void){

    //creates a char array and int variable where the user input can be stored.
    char stuff[50];
    int priority;

    Item *head, *current; //list/node pointers

    //this will hold the value of the menu option selection.
    int menu_select;

    //loads head ptr into the function file to be run so that the list file can be input.
    load_list(head);

    //takes in the value of the menu_selection, prints out the menu for the first time and returns the menu_select value.
    menu_select = menu();

    // as long as the user does not enter 7 which equals quit. the user can keep modifying the list.
    while (menu_select != 7) {

        //insert function
        if (menu_select == 1){
           //prompts the user for the new item scans it in.
           printf("Enter the name and priority of an item\n");
           //saves the string to the array stuff to be transfered
           scanf("%s %d", stuff, &priority);

           // runs the values through the function to insert them into the list.
           insert_item(stuff,priority);

        }

        //delete function
        if (menu_select == 2){
            deletefunc();

        }
        //search function
        if (menu_select == 3){
            search();

        }
        //print function
        if (menu_select == 4){
			printf("\nCalifornia Moving List\n");
			//sends head to the function file for processing.
			printDetails(head);
		}

        //save function
		if (menu_select == 5){
            //saves the current list to that same file it was imported from.
            save(head);
            printf("List saved to file name: california.txt\n");
		}

		// serve function
		if (menu_select == 6) {
            serve();
		}
		menu_select = menu();
    }
}
