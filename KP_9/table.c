#include <time.h>
#include <stdlib.h>
#include "table.h"

void printTable(row *arr, const int size)
{
    printf("╔═════════╦══════════════════════════════════════════════════╗\n");
    printf("║   Ключ  ║                    Значение                      ║\n");
    printf("╠═════════╬══════════════════════════════════════════════════╣\n");
    for (int i = 0; i < size; i++)
        printf("%9ld║%50s\n", arr[i]._key, arr[i]._str);
    printf("╚═════════╩══════════════════════════════════════════════════╝\n");
}

void getRow(FILE *file, char *str, const int size)
{
    int cnt = 0;
    char ch;
    while ((ch = getc(file)) != '\n' && cnt < size - 1)
    {
        str[cnt++] = ch;
    }
    str[cnt] = '\0'; //признак конца строки
}

void swapRows(row *r1, row *r2)
{
    row tmp;
    tmp = *r1;
    *r1 = *r2;
    *r2 = tmp;
}

int binSearch(const row *arr, const int size, const long int key)
{
    int start = 0, end = size - 1, mid;
    if (size <= 0)
        return -1;
    while (start < end)
    {
        mid = start + (end - start) / 2;

        if (arr[mid]._key == key)
            return mid;
        else if (arr[mid]._key < key)
            start = mid + 1;
        else
            end = mid;
    }
    if (arr[end]._key == key)
        return end;
    return -1;
}

int isSorted(const row *arr, const int size)
{
    for (int i = 0; i < size - 1; i++)
        if (arr[i]._key > arr[i + 1]._key)
            return 0;
    return 1;
}

/*void quickSort(row *arr, int left, int right)
{
    int pivot;          // разрешающий элемент
    int l_hold = left;  //левая граница
    int r_hold = right; // правая граница
    pivot = arr[left]._key;
    while (left < right) // пока границы не сомкнутся
    {
        while ((arr[right]._key >= pivot) && (left < right))
            right--;       // сдвигаем правую границу пока элемент [right] больше [pivot]
        if (left != right) // если границы не сомкнулись
        {
            arr[left]._key = arr[right]._key; // перемещаем элемент [right] на место разрешающего
            left++;                           // сдвигаем левую границу вправо
        }
        while ((arr[left]._key <= pivot) && (left < right))
            left++;        // сдвигаем левую границу пока элемент [left] меньше [pivot]
        if (left != right) // если границы не сомкнулись
        {
            arr[right]._key = arr[left]._key; // перемещаем элемент [left] на место [right]
            right--;                          // сдвигаем правую границу влево
        }
    }
    arr[left]._key = pivot; // ставим разрешающий элемент на место
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
        quickSort(arr, left, pivot - 1);
    if (right > pivot)
        quickSort(arr, pivot + 1, right);
}*/
void quickSort(row *arr, int left, int right)
{
    int pivot;
    row p;              // разрешающий элемент
    int l_hold = left;  //левая граница
    int r_hold = right; // правая граница
    pivot = arr[left]._key;
    p = arr[left];
    while (left < right) // пока границы не сомкнутся
    {
        while ((arr[right]._key >= pivot) && (left < right))
            right--;       // сдвигаем правую границу пока элемент [right] больше [pivot]
        if (left != right) // если границы не сомкнулись
        {
            //arr[left]._key = arr[right]._key;
            //*arr[left]._str = *arr[right]._str; // перемещаем элемент [right] на место разрешающего
            //printf("%s\t%s\t", arr[left]._str, arr[right]._str);
            swapRows(&arr[left], &arr[right]);
            left++; // сдвигаем левую границу вправо
        }
        while ((arr[left]._key <= pivot) && (left < right))
            left++;        // сдвигаем левую границу пока элемент [left] меньше [pivot]
        if (left != right) // если границы не сомкнулись
        {
            //arr[right]._key = arr[left]._key;
            //*arr[right]._str = *arr[left]._str; // перемещаем элемент [left] на место [right]
            swapRows(&arr[right], &arr[left]);
            right--; // сдвигаем правую границу влево
        }
    }
    arr[left]._key = pivot;
    // *arr[left]._str = *arr[l_hold]._str;
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
        quickSort(arr, left, pivot - 1);
    if (right > pivot)
        quickSort(arr, pivot + 1, right);
}
