#include "parser.h"
#include "defines.h"

#include <stdio.h>

#include <stdlib.h>

float parser(const char *start)
{
    const char *p = start;
    int i, j;
    int exp;
    int frac1, frac2;
    float ft = 0;

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

        for (j = 0; j < SIGNIFICATIVE - 1; j++, i++)
        {
            frac2 = 10 * frac2 + (p[i] - '0');
        }

        ft = frac1 + 1.0e-4f * frac2;
    }
    else
    {
        // Not supposed to happen
    }

    return ft;
}