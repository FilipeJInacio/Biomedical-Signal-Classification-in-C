#include "utility.h"
#include "defines.h"

#include <stdlib.h>
#include <string.h>

void add_to_string_list(StringList **head, char *string)
{
    // Create a new node
    StringList *newNode;
    if((newNode = (StringList*)malloc(sizeof(StringList))) == NULL){
        // Call error
    }

    newNode->string = strdup(string);
    newNode->next = NULL;

    // If the list is empty, make the new node the head
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // Traverse the list to find the last node
    StringList *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    // Append the new node to the end
    current->next = newNode;
}


void free_string_list(StringList **head)
{
    StringList *current = *head;
    while (current != NULL)
    {
        StringList *next = current->next;
        free(current->string);
        free(current);
        current = next;
    }
    *head = NULL;
}








