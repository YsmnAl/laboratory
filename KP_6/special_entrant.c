#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include "entrant.h"

void usage()
{
    printf("Usage: program [-key] filename\nKeys: -f or -p\n");
}

int main(int argc, char *argv[])
{
    FILE *in;
    int f = 0;
    int p = 0;
    if (argc != 3)
    {
        usage();
        return 1;
    }
    if (strcmp(argv[1], "-f") == 0)
    {
        f = 1;
        in = fopen(argv[2], "rb");
    }
    else if (strcmp(argv[1], "-p") == 0)
    {
        p = 1;
        in = fopen(argv[2], "rb");
    }
    else
    {
        usage();
        return 2;
    }
    entrant e;
    if (in == NULL)
    {
        perror("Can not open file\n");
        return 3;
    }
    if (f == 1)
    {
        printf(" ________________________________________________________________________________\n");
        printf("|     SURNAME     | INITIALS |   SEX   |  SCHOOL  | MEDAL | MATH |  RUS  | ESSAY |\n");
        printf(" ________________________________________________________________________________\n");
        while (fread(&e, sizeof(e), 1, in) == 1)
        {
            printf("|%-17s|%-10s|%-9s|%-10d|%-7s|%-6d|%-7d|%-7s|\n", e.surname, e.initials, e.sex, e.school,
                   e.medal, e.math, e.rus, e.essay);
            printf("_________________________________________________________________________________\n");
        }
        fclose(in);
        return 0;
    }
    if (p == 1)
    {
        int sum_num = 0;
        int n = 0;
        while (fread(&e, sizeof(e), 1, in) == 1)
        {
            sum_num += e.math + e.rus;
            n++;
        }
        fseek(in, 0, SEEK_SET); // относительно начала файла
        if (n == 0)
        {
            printf("No people\n");
            return 4;
        }
        double average = (double)sum_num / n;
        printf(" ________________________________________________________________________________\n");
        printf("|     SURNAME     | INITIALS |   SEX   |  SCHOOL  | MEDAL | MATH |  RUS  | ESSAY |\n");
        printf(" ________________________________________________________________________________\n");
        while (fread(&e, sizeof(e), 1, in) == 1)
        {
            if ((strcmp("M", e.sex) == 0) && (strcmp("No", e.medal) == 0) && (e.rus + e.math > average))
            {
                printf("|%-17s|%-10s|%-9s|%-10d|%-7s|%-6d|%-7d|%-7s|\n", e.surname, e.initials, e.sex, e.school,
                       e.medal, e.math, e.rus, e.essay);
                printf("_________________________________________________________________________________\n");
            }
        }
        fclose(in);
        return 0;
    }
    return 0;
}
