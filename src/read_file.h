#ifndef read_file_h
#define read_file_h
#include "defines.h"
#include "utility.h"

typedef struct Data
{
    int start_time;
    unsigned short *sensor1;
    unsigned short *sensor2;
    unsigned short *sensor3;
    unsigned short *sensor4;
} Data;

int mem_treatment(Data *File[FILES_IN_CACHE]);
int allocate_mem(Data **data);
int readLineFromFile(const char *filename, Data *data);
int start_from_folder(const char *path, StringList **PathsList);
void free_data(Data *File[FILES_IN_CACHE]);

#endif
