#include "parser.h"
#include "utility.h"
#include "defines.h"
#include "read_file.h"

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
        // 

        printf("%s\n",curr->string);
    }

    free_data(File);
    return 0;
}




int read(const char* filename) {
    size_t numNumbers;
    unsigned short* numbers = readBinaryFile(filename, &numNumbers);

    if (numbers != NULL) {
        for (size_t i = 0; i < numNumbers; i++) {
            printf("%hu ", numbers[i]);
        }
        printf("\n");

        free(numbers);
    }

    return 0;
}




int main()
{
    StringList *PathsList = NULL;
    start_from_folder("/mnt/c/Users/fjina/OneDrive/Ambiente de Trabalho/Inesc/BinData",&PathsList);
    printf("%li %li %li\n",sizeof(int),sizeof(Data),sizeof(unsigned short*));
    //printStringList(PathsList);

    for(StringList *curr = PathsList; curr != NULL; curr = curr->next){
        
        read(curr->string);

        printf("%s\n",curr->string);
    }

    return 0;
}



