#include "read_file.h"
#include "defines.h"
#include "parser.h"
#include "utility.h"

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

    if (((*data)->sensor1 = (unsigned short *)malloc(NUMBER_OF_LINES * sizeof(unsigned short))) == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    if (((*data)->sensor2 = (unsigned short *)malloc(NUMBER_OF_LINES * sizeof(unsigned short))) == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    if (((*data)->sensor3 = (unsigned short *)malloc(NUMBER_OF_LINES * sizeof(unsigned short))) == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    if (((*data)->sensor4 = (unsigned short *)malloc(NUMBER_OF_LINES * sizeof(unsigned short))) == NULL)
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

    free(File[0]->sensor1);
    free(File[0]->sensor2);
    free(File[0]->sensor3);
    free(File[0]->sensor4);
    free(File[0]);

    File[0]=File[1];
    File[1]=File[2];
    File[2]=File[3];
    File[3]=File[4];

    allocate_mem(&File[4]);
    return 4;
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
            free(File[i]->sensor1);
            free(File[i]->sensor2);
            free(File[i]->sensor3);
            free(File[i]->sensor4);
            free(File[i]);
        }
    }
}




