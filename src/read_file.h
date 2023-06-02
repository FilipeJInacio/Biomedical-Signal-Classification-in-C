#ifndef read_file_h
#define read_file_h
#include "defines.h"

typedef struct StringList
{
    char *string;
    struct StringList *next;
} StringList;

char *get_string_and_advance(StringList **list);

void add_to_string_list(StringList **head, char *string);

void free_string_list(StringList **head);

void printStringList(StringList *head);


typedef struct Data
{
    float *value1;
    float *value2;
    float *value3;
    float *value4;
    float *value5;
} Data;

int mem_treatment(Data *File[FILES_IN_CACHE]);
int allocate_mem(Data **data);
int readLineFromFile(const char *filename, Data *data);
int start_from_folder(const char *path, StringList **PathsList);
void free_data(Data *File[FILES_IN_CACHE]);
#endif
