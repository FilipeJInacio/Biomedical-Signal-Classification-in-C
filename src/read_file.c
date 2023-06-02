#include "read_file.h"
#include "defines.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

int allocate_mem(Data **data)
{
    if (((*data) = (Data *)malloc(sizeof(Data))) == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    if (((*data)->value1 = (float *)malloc(NUMBER_OF_LINES * sizeof(float))) == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    if (((*data)->value2 = (float *)malloc(NUMBER_OF_LINES * sizeof(float))) == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    if (((*data)->value3 = (float *)malloc(NUMBER_OF_LINES * sizeof(float))) == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    if (((*data)->value4 = (float *)malloc(NUMBER_OF_LINES * sizeof(float))) == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    if (((*data)->value5 = (float *)malloc(NUMBER_OF_LINES * sizeof(float))) == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    return 0;
}

int mem_treatment(Data *File[FILES_IN_CACHE])
{

    if(File[0]==NULL){
        allocate_mem(&(File[0]));
        return 0;
    }
    if(File[1]==NULL){
        allocate_mem(&File[1]);
        return 1;
    }
    if(File[2]==NULL){
        allocate_mem(&File[2]);
        return 2;
    }
    if(File[3]==NULL){
        allocate_mem(&File[3]);
        return 3;
    }
    if(File[4]==NULL){
        allocate_mem(&File[4]);
        return 4;
    }

    free(File[0]->value1);
    free(File[0]->value2);
    free(File[0]->value3);
    free(File[0]->value4);
    free(File[0]->value5);
    free(File[0]);

    File[0]=File[1];
    File[1]=File[2];
    File[2]=File[3];
    File[3]=File[4];

    allocate_mem(&File[4]);
    return 4;
}

int readLineFromFile(const char *filename, Data *data)
{
    int flag = 0;
    int counter[4] = {0,0,0,0};
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        perror("Failed to open file\n");
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    uint i = 0;

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
    {
        data->value1[i] = i;

        if((data->value2[i] = parser(&line[27]))> THRESHHOLD){
            flag = 1;
            counter[0]++;
        }
        if((data->value3[i] = parser(&line[52]))> THRESHHOLD){
            flag = 1;
            counter[1]++;
        }
        if((data->value4[i] = parser(&line[77]))> THRESHHOLD){
            flag = 1;
            counter[2]++;
        }
        if((data->value5[i] = parser(&line[102]))> THRESHHOLD){
            flag = 1;
            counter[3]++;
        }

        i++;
        if (i >= NUMBER_OF_LINES)
        {
            break;
        }
    }

    printf("%i\n",flag);
    printf("%i %i %i %i\n",counter[0],counter[1],counter[2],counter[3]);

    fclose(file);
    return flag;
}

int start_from_folder(const char *path, StringList **PathsList)
{
    DIR *dir;
    struct dirent *ent;
    char filePath[PATHSIZE];

    // Open the directory
    dir = opendir(path);

    if (dir != NULL) {
        // Read directory entries
        while ((ent = readdir(dir)) != NULL) {
            // Skip current directory (.)
            if (strcmp(ent->d_name, ".") == 0)
                continue;

            // Skip parent directory (..)
            if (strcmp(ent->d_name, "..") == 0)
                continue;

            // Get the full file path
            snprintf(filePath, sizeof(filePath), "%s/%s", path, ent->d_name);

            // Print the file name
            add_to_string_list(PathsList,filePath);
        }

        // Close the directory
        closedir(dir);
    } else {
        // Failed to open directory
        perror("Failed to open directory");
        return 1;
    }

    return 0;
}   

void free_data(Data *File[FILES_IN_CACHE])
{

    for(int i = 0; i < FILES_IN_CACHE;i++){
        if(File[i]!=NULL){
            free(File[i]->value1);
            free(File[i]->value2);
            free(File[i]->value3);
            free(File[i]->value4);
            free(File[i]->value5);
            free(File[i]);
        }
    }
}




char *get_string_and_advance(StringList **list)
{
    char *string;

    // Check if the list pointer is null or the list is empty
    if (list == NULL || *list == NULL)
    {
        return NULL;
    }

    // Get the string from the current element
    string = (*list)->string;

    // Advance the pointer to the next element
    *list = (*list)->next;

    // Return the string
    return string;
}

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

void printStringList(StringList *head)
{
    int i = 0;
    for (StringList *curr = head; curr != NULL; curr = curr->next, i++)
    {
        fprintf(stderr,"%s\n",curr->string);
    }
}
