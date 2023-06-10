#ifndef utility_h
#define utility_h

typedef struct StringList
{
    char *string;
    struct StringList *next;
} StringList;

/**
|   Input: New string element
|
|   Output:
|
|   Description: Adds a new string element to the end of the list
|
 */
void add_to_string_list(StringList **head, char *string);

/**
|   Input: 
|
|   Output:
|
|   Description: Frees all the elements of the list
|
 */
void free_string_list(StringList **head);






#endif