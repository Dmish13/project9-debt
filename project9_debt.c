// Daniel Misherky
// U93099650
// This program will create a linked list of debts
// The user can add to the list, delete the first item from the list 
// search the list, and print the list of debts
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NAME_LEN 30

struct debt{
	char company[NAME_LEN+1];
	double balance;
	double minimum;
	double interest_rate;
	struct debt *next;
}; // struct representing a node in the linked list, with each node having company info


struct debt *add_to_list(struct debt *list);
struct debt *delete_first(struct debt *list);
void search_list(struct debt *list);
void print_list(struct debt *list);
void clear_list(struct debt *list);
int read_line(char str[], int n);

/**********************************************************
 * main: Prompts the user to enter an operation code,     *
 *       then calls a function to perform the requested   *
 *       action. Repeats until the user enters the        *
 *       command 'q'. Prints an error message if the user *
 *       enters an illegal code.                          *
 **********************************************************/
int main(void)
{
  char code;

  struct debt *debt_list = NULL;  
  printf("Operation Code: a for adding to the list, d for deleting the first debt, s for searching"
	  ", p for printing the list; q for quit.\n");
  for (;;) {
    printf("Enter operation code: ");
    scanf(" %c", &code);
    while (getchar() != '\n')   /* skips to end of line */
      ;
    switch (code) {
      case 'a': debt_list = add_to_list(debt_list);
                break;
      case 'd': debt_list = delete_first(debt_list);
                break;
      case 's': search_list(debt_list);
                break;
      case 'p': print_list(debt_list);
                break;
      case 'q': clear_list(debt_list);
		return 0;
      default:  printf("Illegal code\n");
    }
    printf("\n");
  }
}

struct debt *add_to_list(struct debt *list)
{
  struct debt *new_node, *prev, *cur;  // initializes new node, and pointers to go through linked list
  new_node = malloc(sizeof(struct debt)); // allocate memory for new node

  if(new_node == NULL) // check if memory allocation was successful
  {
    printf("Memory allocation failed\n");
    return list; // return the original list if allocation failed
  }

  printf("Enter company name: "); // user inputs company info
  read_line(new_node->company, NAME_LEN); // readline function reads a line of input with length NAME_LEN
  printf("Enter balance: ");
  scanf("%lf", &new_node->balance);
  printf("Enter monthly minimum: ");
  scanf("%lf", &new_node->minimum);
  printf("Enter interest rate: ");
  scanf("%lf", &new_node->interest_rate);

  new_node->next = NULL; // sets the next pointer of new node to NULL so it has all info needed

  if(list == NULL)
  {
    return new_node; // if list is empty, new node becomes the head of the list
  }

  for(prev = NULL, cur = list; cur!=NULL && cur->interest_rate>=new_node->interest_rate; 
  prev = cur, cur= cur->next); // goes through linked list to find the right place to insert new node
  // the loop stops when cur is NULL or when the interest rate of the current node is less than the new node's interest rate

  if(prev ==NULL) // if there is no previous node, then the node is put at the beginning of the list
  {
    new_node->next = list; // if the list is empty, set the next pointer of the new node to NULL
    return new_node; // return the new node as the head of the list
  }

  else // if there is a previous node, then the new node is inserted after the previous node, but before the current node
  {
    prev->next = new_node; // set the next pointer of the previous node to the new node
    new_node->next = cur; // set the next pointer of the new node to the current node
    return list; // return the original list with the new node added
  }
}

struct debt *delete_first(struct debt *list)
{
  struct debt *p; // pointer to go through linked list
  if(list==NULL) 
  {
    return NULL; // if the list is empty, return NULL
  }
  else
  {
    p = list; // saves the first node
    list = list->next; // starts list at the second node
    free(p); // frees memory of the first node
  }
  return list; // returns the new linked list
}

void search_list(struct debt *list)
{
  char company[NAME_LEN+1]; // initializes string for company name
  printf("Enter company name: "); 
  read_line(company, NAME_LEN); // reads a line of input with length NAME_LEN
  struct debt *p; // pointer to go through linked list
  int flag = 1; // flag to check if company is found
  for(p = list; p!=NULL; p = p->next) // goes through linked list
  {
    if(strcmp(p->company, company)==0) // compares the company name given to the one in the list
    {
      printf("%-28s%12.2f%12.2f%12.2f\n", p->company, p->balance, p->minimum, p->interest_rate); // displays company info if found
      flag = 0; // sets flag to 0 if company is found
    }
  }
  if(flag) // if flag is still 1, company was not found
  {
    printf("not found\n");
  }
}


void print_list(struct debt *list){
  printf("company                          balance     minimum    interest\n"); // header for table of company info
  struct debt *p; // pointer to go through linked list
  for(p = list; p!=NULL; p = p->next) // goes through linked list
  {
    // prints company info in a formatted table
    printf("%-28s%12.2f%12.2f%12.2f\n", p->company, p->balance, p->minimum, p->interest_rate);
  }

}

void clear_list(struct debt *list)
{
  struct debt *p; // pointer to go through linked list
  while(list != NULL) // while the list isn't empty
  {
    p = list; // saves the current node
    list = list->next; // goes to next node
    free(p); // frees memory of the current node
  }

}

int read_line(char str[], int n) // used to read a line of input given by the user
{
  int ch, i = 0;

  while (isspace(ch = getchar()))
    ;
  str[i++] = ch;
  while ((ch = getchar()) != '\n') {
    if (i < n)
      str[i++] = ch;
    
   }
   str[i] = '\0';
   return i;
}
