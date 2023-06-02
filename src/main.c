#include "parser.h"
#include "read_file.h"
#include "defines.h"

#include <stdio.h>
#include <stdlib.h>


int run(StringList *PathsList){

    int index;
    Data *File[FILES_IN_CACHE];

    for(int i = 0; i < FILES_IN_CACHE;i++){
        File[i] = NULL;
    }

    for(StringList *curr = PathsList; curr != NULL; curr = curr->next){
        
        index = mem_treatment(File);
        readLineFromFile(curr->string, File[index]);

        printf("%s\n",curr->string);
    }

    free_data(File);
    return 0;
}


void test_parser(char *a){
    float b = parser(a);
    printf("%f\n", b);
}


int main()
{
    StringList *PathsList = NULL;
    start_from_folder("/mnt/c/Users/fjina/OneDrive/Ambiente de Trabalho/Inesc/Data",&PathsList);

    //printStringList(PathsList);

    run(PathsList);

    return 0;
}
