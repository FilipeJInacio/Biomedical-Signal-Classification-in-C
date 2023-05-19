#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 128
#define MAX_NUMBER_LENGTH 25
#define NUMBER_OF_LINES 1400000

typedef struct {
    float value1[NUMBER_OF_LINES];
    float value2[NUMBER_OF_LINES];
    float value3[NUMBER_OF_LINES];
    float value4[NUMBER_OF_LINES];
    float value5[NUMBER_OF_LINES];
} Data;


int readLineFromFile(const char* filename, Data* data) {

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        perror("Failed to open file\n");
        return 0;
    }
    
    char line[MAX_LINE_LENGTH];
    uint i = 0;

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        int count = sscanf(line, "%f %f %f %f %f",&(data->value1[i]),&(data->value2[i]),&(data->value3[i]),&(data->value4[i]),&(data->value5[i]));
        data->value2[i] *= 1000000000;
        data->value3[i] *= 1000000000;
        data->value4[i] *= 1000000000;
        data->value5[i] *= 1000000000;
        i++;
        if (count != 5) { return 0;}
        if(i>=NUMBER_OF_LINES){break;}
    }
    
    fclose(file);
    return 1;
}


int main(){

    Data myData;

    if (readLineFromFile("data/00000.txt", &myData)) {
        printf("worked\n");
    }

    printf("%f\n", myData.value1[NUMBER_OF_LINES-1]);
    
    return 0;
}