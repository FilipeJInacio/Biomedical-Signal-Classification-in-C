#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 128
#define MAX_NUMBER_LENGTH 25
#define NUMBER_OF_LINES 1400000
#define SIGNIFICATIVE 4

typedef struct
{
    float *value1;
    float *value2;
    float *value3;
    float *value4;
    float *value5;
} Data;

int allocate_mem(Data *data)
{

    if ((data->value1 = (float *)malloc(NUMBER_OF_LINES * sizeof(float))) == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    if ((data->value2 = (float *)malloc(NUMBER_OF_LINES * sizeof(float))) == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    if ((data->value3 = (float *)malloc(NUMBER_OF_LINES * sizeof(float))) == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    if ((data->value4 = (float *)malloc(NUMBER_OF_LINES * sizeof(float))) == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    if ((data->value5 = (float *)malloc(NUMBER_OF_LINES * sizeof(float))) == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    return 0;
}

float parser(const char *start)
{
    const char *p = start;
    int Esign = 0;
    int i, j;
    int exp;
    int frac1, frac2;
    float ft;

    if (p[20] == '-') // Is the exp negative?
    {
        exp = -((p[21] - '0') * 10 + (p[22] - '0')) + 12;

        frac1 = (p[1] - '0');
        for (i = 3; i < exp; i++) // i = 3 skip -1. in -1.4578 to go to 4
        {
            frac1 = 10 * frac1 + (p[i] - '0');
        }

        frac2 = (p[i] - '0');
        i++;

        for (j; j < SIGNIFICATIVE - 1; j++, i++)
        {
            frac2 = 10 * frac2 + (p[i] - '0');
        }

        printf("\n%i\n", frac2);

        ft = frac1 + 1.0e-4f * frac2;
    }
    else
    {
        exp = (p[21] - '0') * 10 + (p[22] - '0');
    }

    if (p[20] == '-')
    {
        return -ft;
    }
    else
    {
        return ft;
    }
}

int readLineFromFile(const char *filename, Data *data)
{

    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        perror("Failed to open file\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    uint i = 0;

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
    {
        // data->value1[i] = strtof(&line[3], &line[24]);
        printf("\n%f\n", data->value1[i]);

        i++;
        if (i >= NUMBER_OF_LINES)
        {
            break;
        }
    }

    fclose(file);
    return 0;
}

int start()
{

    Data myData;

    if (allocate_mem(&myData))
    {
        return 1;
    }

    if (readLineFromFile("/mnt/c/Users/fjina/OneDrive/Ambiente de Trabalho/Data/00117.txt", &myData))
    {
        printf("Failed\n");
        return 1;
    }
    return 0;
}

int main()
{
    char *a = "-1.4801251239795476e-06";

    float b = parser(a);
    printf("%f\n", b);
    return 0;
}
