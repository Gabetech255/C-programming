#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//creates a struct with my node and pointer
struct list {
    char item_name[50];
    int priority;
    struct list *next;
};

//create a type definition for easy of repeatability
typedef struct list Item;
typedef Item *Itemptr;


    //Global Variables

    char file_name[50]; //file variable
    FILE *filein, *fileout; //file pointers
    Item *head, *current, *prior, *post, *newitem; //list pointers



//prototype functions
void printDetails(Item *print);

void load_list(); //imports the contents of the file too the list.
int menu(); //contains my user menu
void insert_item(char inName[50], int inPrior);
void deletefunc();
void save(Item *print);
void search();
void serve();


// this loads the file specified by the user into the list.
void load_list(){

//Loads California.txt file
    printf("What is the name of the file you'd like to open?\n Hint: type in california.txt\n");
    scanf("%s", file_name);
        //ensure file name correctly entered by user
        if( (filein = fopen(file_name, "r")) == NULL){ //open file
            printf("File could not be opened.\n");
        }else{
            //set my head pointer and allocates its memory.
            head = NULL;
            head = malloc(sizeof(Item));
            //begins to scan in values from the file.
            fscanf(filein,"%s %d\n", head->item_name, &head->priority);//rewrites head from NULL->address to the address of the first Item[50]);

            current = head;//set the current variable to the address of the first node through the head pointer variable

            //as long as the scan has not reached the end of file, keep scaning values and entering them into the list.
            while(fscanf(filein, "%d", current->priority) != EOF){
                current->next = malloc(sizeof(Item));
                current = current->next;

                //scans the input file for the items ad there priority .
                fscanf(filein, "%s %d\n", current->item_name, &current->priority);//rewrites head from NULL->address to the address of the first Item[50]);
                // sets the last item to point to NULL.
                current->next = NULL;

            }
        }

        //close file pointer
        fclose(filein);
}

/*this is my insert function. it takes in a string and int from the user
and inserts it into the list*/
void insert_item(char inputName[50],  int inputPriority){

    //this sets our node pointers
    struct list *temp, *extra;

    //creates a temporary pointer pointing to enough memory to hold the values
    temp = (struct list *)malloc(sizeof(struct list));

    //copies the string from inputName and copies it to the current position of temp in my list.
    strcpy(temp->item_name, inputName);
    //does the same for my priority.
    temp->priority = inputPriority;
    temp->next = NULL;

    //points to thee current section in the list and helps me move through it.
    extra = (struct list *)head;

    while(extra->next !=NULL){
        extra = extra->next;
    }

    extra->next = temp;
    extra = temp;
    extra->next = NULL;
}


//Deletes whatever item from the list that the user specifies.
void deletefunc()  {
    // sets up our pointers.
	Itemptr post=head, prior=head, temp=NULL;
	//this array will hold the name of the item that is input
    char string[50];
    //asks the user what item they want to remove then scans the string into the array.
    printf("What task do you want to delete?\n");
    scanf("%s", string);

        	if (head == NULL)//checks if the list is empty
        		printf("The list is empty\n");
        	else if (strcmp(head->item_name,string)==0) {    // checks if its the head
            	temp=head;   // temporary ptr to free up the memory             		head=head->next;
            	free(temp);    }
        else    {        // searches the list for the item to be deleted
            	post=prior->next;
            	while (post != NULL) { //make sure its not at the end of the list
                        // if the item if found, free() is applied.
                        if((strcmp(post->item_name,string)==0)) {
                            	prior->next=post->next;
                            	free(post);     }      // free up memory
                    	else    {            // keep looking
                            	prior=post;
                            	post=prior->next; }
                }
            }
        }


// searches through the current list for an item specified by the user.
void search(){

    //this array will store the name of the item input.
    char input[50];
    int x = 0;

    //defines our current ptr
    Item *current;

    //asks the user what item they want. they scans in the input.
    printf("What are you looking for?\n");
    scanf("%s", input);

    //set out pointers to the beginning of the list.
    post = head;
    prior = head;
    //compares the string input with the one at the top of the list.
    if (strcmp(head->item_name,input)==0){
        printf("This is on the list\n");
    }

    else{
        //moves down the list.
        post = prior->next;

        //ask long as thee list isnt over or empty...
        while(post != NULL){
            //compares the input with each string in the list.
            if (strcmp(post->item_name,input)== 0){
                //if it finds it it prints a confirmation and breaks the loop.
                printf("That is on the list\n");
                x=1;
                break;
            }
            else{
            //moves down the list.
              prior = post;
              post = prior->next;
            }
        }
    }
    //condition which if met means the item is not on the list.
    if (x == 0 ){
        printf("This item is not on the list.\n");
    }
}

//the serve function is intended to provide the user with the priority of a particular item.
//the only true difference between this and the search function is that it finds the item
//and prints out its priority which is and integer pointed to by either head or post.
void serve(){

    char input[50];
    int x = 0;

    Item *current;

    printf("Which list item would you like the priority for?\n");
    scanf("%s", input);

    post = head;
    prior = head;

    if (strcmp(head->item_name,input)==0){
        printf("This is on the list\n");
        printf("The priority is %d\n", head->priority);
    }
    else{
        post = prior->next;

        while(post != NULL){
            //strcmp(ptrs->label,member)==0
            if (strcmp(post->item_name,input)== 0){
                printf("The priority for this item is %d\n", post->priority);
                x=1;
                break;
            }
            else{
              prior = post;
              post = prior->next;
            }
        }
    }
    if (x ==0 ){
        printf("This item is not on the list.\n");
    }
}

//print function. It prints our list to screen
void printDetails(Item *print){

    //points print to head which points to the top of our list.
    print = head;
    //as long as the list is not empty run the loop
    while(print != NULL){
        // prints whatevers in that spot of the list to the screen
        printf("%s %d\n", print->item_name, print->priority);
        //moves the pointer down the list
        print = print->next;
    }
}

// saves the current iteration of the list to the same file from which it was first scanned in.
void save(Item *print){

    //set print to point at head which points to the top of the list.
    print = head;
    fileout = fopen(file_name, "w");

    //as long as the list is not empty run the loop
    while (print != NULL){
        //prints out the current spot in the list to the file 'cali.txt'
        fprintf(fileout, "%s %d\n", print->item_name,print->priority);
        //moves the pointer down the list.
        print = print->next;
    }
    //closes the file.
    fclose(fileout);
}

//main menu. offers the user 7 choices on how to manipulate the list.
int menu() {
  int menu_select;
  printf("MENU\n");
  printf("1. Insert an item.\n");
  printf("2. Delete an item.\n");
  printf("3. Search for item.\n");
  printf("4. Print the current list.\n");
  printf("5. Save to File.\n");
  printf("6. Find out the priority of an item.\n");
  printf("7. Quit.\n");
  scanf("%d", &menu_select);
  return menu_select;
}
