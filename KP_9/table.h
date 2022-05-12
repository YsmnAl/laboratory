#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>

typedef struct _row
{
    long int _key;
    char _str[120];
} row;

void printTable(row *arr, const int size);
void getRow(FILE *stream, char *str, const int size);
void swapRows(row *r1, row *r2);
int binSearch(const row *arr, const int size, const long int key);
int isSorted(const row *arr, const int size);
void quickSort(row *arr, int left, int right);
#endif
