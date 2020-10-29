    /***********************************************************************
     * Auther: Mingi Lee                                                   *
     *               <April 27th, 2020>                                    *
     ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAXSTRLEN 30



typedef struct node ticket;


/* Definition of structure ticket*/
struct node {
    int ticketNum;
    char identifier[MAXSTRLEN + 1];
    char problem[MAXSTRLEN + 1];
    int urgency;
    char status[MAXSTRLEN + 1];
    int lol;
    char technician[MAXSTRLEN + 1];
    ticket * next;
};

/* Print menu options to the screen */
/* printMenu
  post-condition:  the menu is printed.
*/
void
printMenu(void)
{
    printf("\nMENU : Enter the number\n");
    printf("1. Create a new tracking ticket\n");
    printf("2. Assign a new ticket to a technician for handling\n");
    printf("3. Mark a ticket complete\n");
    printf("4. Print a list of new tickets\n");
    printf("5. Print a list of assigned tickets\n");
    printf("6. Print a list of completed tickets\n");
    printf("7. Exit the program\n");
} // printMenu


/*create

  pre-condition:  firstPtr points to the pointer
                   designating the head of a list
  post-condition:  a ticket is created and inserted in the list
  Every input in this fuction has to have designated type.
*/
void
create(ticket ** firstPtr)
{
    ticket* new;
    new = malloc(sizeof(ticket));
    printf("Enter the ticket number (integer) : ");
    scanf("%d", &new->ticketNum);
    printf("The company identifier (characters) : ");
    scanf("%s", &new->identifier);
    printf("Code that indicates the type of problem (characters) : ");
    scanf("%s", &new->problem);
    printf("Code that indicates the relative level of urgency (integers from 1 to 4) : ");
    scanf("%d", &new->urgency);
    strcpy(new->status, "new");
    strcpy(new->technician, "unassigned");
    new->next = *firstPtr;
    *firstPtr = new;
}




/* assign

  pre-condition:  firstPtr1 points to the pointer
                   designating the head of a list
                   firstPtr2 points to the pointer
                   designating the head of a list
  post-condition:  a ticket is assigned from list of
                   new tickets to the list of
                   assigned tickets by urgency.
*/
void
assign(ticket** firstPtr1, ticket** firstPtr2)
{
    char * name ;
    ticket* cur;
    ticket* prev;
    ticket* firstNode = *firstPtr1;

    if (*firstPtr1 == NULL)
    {
        printf("There is no any new tickets.\n");
        return;
    }

    name = malloc(15);
    if (name == NULL)
    {
        printf("Error : malloc failed");
        return;
    }
    printf("Enter the name of the technician : ");
    scanf("%s", name);//asking for name

    for (cur = *firstPtr1, prev = NULL;
        cur != NULL && cur->urgency != 1;
        prev = cur, cur = cur->next)
        ;
    if (cur == NULL)
    {

        *firstPtr1 = (*firstPtr1)->next;
        firstNode->next = *firstPtr2;
        *firstPtr2 = firstNode;

        strcpy((*firstPtr2)->technician, name);
        strcpy((*firstPtr2)->status, "assigned");
        return;
    }
    if (prev == NULL)
    {

        *firstPtr1 = (*firstPtr1)->next;
        firstNode->next = *firstPtr2;
        *firstPtr2 = firstNode;

        strcpy((*firstPtr2)->technician, name);
        strcpy((*firstPtr2)->status, "assigned");
        return;
    }
    else 
    {
        prev->next = cur->next;
        cur->next = *firstPtr2;
        *firstPtr2 = cur;

        strcpy((*firstPtr2)->technician, name);
        strcpy((*firstPtr2)->status, "assigned");
        return;
    }
    
}


/* mark

  pre-condition:  firstPtr1 points to the pointer
                   designating the head of a list
                   firstPtr2 points to the pointer
                   designating the head of a list
  post-condition:  a ticket is assigned from list of
                   assigned tickets to the list of
                   completed tickets.
*/
void
mark(ticket** firstPtr1, ticket** firstPtr2) {
    ticket * cur;
    ticket * prev;
    int num;

    if (*firstPtr1 == NULL)
    {
        printf("There is no any assigned tickets.\n");
    }
    else
    {
        printf("Enter the ticket number to complete : ");
        scanf("%d", &num);
        for (cur = *firstPtr1, prev = NULL;
            cur != NULL && cur->ticketNum != num;
            prev = cur, cur = cur->next)
            ;
        if (cur == NULL)
        {
            printf("The number was not found. Try again.\n");
            return;
        }
        if (prev == NULL)
        {

            *firstPtr1 = cur->next;

            cur->next = *firstPtr2;
            *firstPtr2 = cur;
            strcpy((*firstPtr2)->status, "completed");

        }
        else
        {

            prev->next = cur->next;

            cur->next = *firstPtr2;
            *firstPtr2 = cur;
            strcpy((*firstPtr2)->status, "completed");
        }


    }





}


/* print

  pre-condition:  first designates the first node of a list 
  post-condition:  values in the structure is printed.
*/
void
print(ticket* first) {

    printf("The names on the list are:\n\n");

    for (ticket* current = first; current != NULL; current = current->next) {

        printf("%d\n", current->ticketNum);
        printf("%s\n", current->identifier);
        printf("%s\n", current->problem);
        printf("%d\n", current->urgency);
        printf("%s\n", current->status);
        printf("%s\n", current->technician);
        printf("\n");
    }

    printf("End of List\n\n");
} // print


int main(void)
{
    //initialize the pointer to the first item.
    int option;
    ticket* first1;
    first1 = NULL;//new tickets

    ticket* first2;
    first2 = NULL;//assigned tickets

    ticket* first3;
    first3 = NULL;//completed tickets

    //prints friedly message
    printf("Hello! This is an issue tracking program\n");
    printf("that creates new tickets and locates existing tickets\n");
    printf("You can also check each list of tickets.\n");

   
    //while statement to repeat the menu until entered 7.
    while (1) {
        printMenu();
        printf("Enter the option : ");
        scanf("%d", &option);
        switch (option) {
        case 1: create(&first1);
            break;
        case 2: assign(&first1, &first2);
            break;
        case 3: mark(&first2, &first3);
            break;
        case 4: print(first1);
            break;
        case 5: print(first2);
            break;
        case 6: print(first3);
            break;
        case 7: printf("Thank you for using our program.\n");
            return 0;
            break;
        default: printf("Invalid Option - Try Again!\n");
            continue;
        }
    }



    return 0;

}

