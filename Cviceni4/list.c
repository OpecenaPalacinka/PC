#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PERSON_NAME_LENGTH 32

typedef struct _person
{
    char name [PERSON_NAME_LENGTH];
    unsigned int age, shoesize;
} person;

typedef struct _person_list_node
{
    person data;
    struct _person_list_node *next;
} person_list_node;

/**
 * @brief 
 * 
 * @param head 
 * @param name 
 * @param age 
 * @param shoesize 
 * @return int 0 je špatně, 1 je dobře
 */
int person_list_add(person_list_node **head,char name[], unsigned int age, unsigned int shoesize){
    person_list_node *temp;
    
    if(!head || !name){
        return 0;
    }
    temp = (person_list_node *)malloc(sizeof(person_list_node));
    if (!temp /* temp == NULL*/){
        return 0;
    }

    strncpy((*temp).data.name, name, PERSON_NAME_LENGTH);
    temp->data.age = age;
    temp->data.shoesize = shoesize;

    temp->next = *head;
    *head = temp;
    return 1;
}

void person_list_print(person_list_node *head){
    /* Vytisknout spojový seznam do konzole.*/

    while (head)
    {
        printf("");
    }
    

}

void list_free(person_list_node **head){
    person_list_node *next;

    if(!head || !*head){
        return;
    }

    while (*head)
    {
        next = (*head)->next;
        free(*head);
    }

    *head = NULL;
}

int main(){
    person_list_node *head = NULL;

    person_list_add(&head, "Honzík", 27, 45);
    person_list_add(&head, "Hana", 22, 39);
    person_list_add(&head, "Bořek", 87, 43);

    list_free(&head);

    return EXIT_SUCCESS;
}