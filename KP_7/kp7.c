#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "matrix.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Использование: ./а.out <FILE_NAME>\n");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        fprintf(stderr, "Не удалось открыть файл \"%s\"\n", argv[1]);
        return 2;
    }
    matrix a, ans;
    mat_init(&a);
    mat_init(&ans);
    mat_read(&a, f);
    fprintf(stdout, "\nИзначальная матрица:\n");
    mat_print(&a);
    fprintf(stdout, "\nПредставление матрицы:\n");
    mat_print_vec(&a);
    fprintf(stdout, "\n");
    fprintf(stdout, "\n");
    if (a.n == a.m)
    {
        mat_trans_diag(&a, &ans);
        fprintf(stdout, "Матрица, транспонированная относительно побочной диагонали:\n");
        mat_print(&ans);
        fprintf(stdout, "\nПредставление матрицы:\n");
        mat_print_vec(&ans);
        if (mat_check_skew_symmetry(&ans))
        {
            fprintf(stdout, "\nМатрица кососимметричная\n");
        }
        else
        {
            fprintf(stdout, "\nМатрица НЕ кососимметричная \n");
        }
    }
    else
    {
        fprintf(stdout, " Матрица не является квадратной, транспонировать нельзя\n");
    }
    mat_destroy(&a);
    mat_destroy(&ans);
    fclose(f);
}
