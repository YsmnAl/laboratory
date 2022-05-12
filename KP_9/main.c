#include <stdio.h>
#include <stdlib.h>
#include "table.h"

void menu()
{
    printf("Меню:\n");
    printf("1) Вывести таблицу\n");
    printf("2) Найти элемент в таблице по ключу\n");
    printf("3) Отсортировать таблицу\n");
    printf("4) Меню\n");
    printf("5) Выход\n");
}

int main(void)
{
    const int N = 50;
    int i, cnt, rule;
    long key;
    char ch;
    row arr[N];
    char filename[100];
    printf("Введите название файла:\n");
    scanf("%s", filename);
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Файл не существует\n");
        return 0;
    }
    i = 0;
    while (i < N && fscanf(file, "%ld", &arr[i]._key) == 1)
    {
        fscanf(file, "%c", &ch);
        getRow(file, arr[i]._str, sizeof(arr[i]._str));
        i++;
    }
    fclose(file);
    cnt = i;
    menu();
    while (1)
    {
        scanf("%d", &rule);
        switch (rule)
        {
        case 1:
            printTable(arr, cnt);
            break;
        case 2:
            if (!isSorted(arr, cnt))
            {
                printf("Таблица неотсортирована\n");
            }
            else
            {
                printf("Введите ключ\n");
                scanf("%ld", &key);
                i = binSearch(arr, cnt, key);
                if (i > -1)
                {
                    printf("По ключу %ld найден элемент \"%s\"\n", key, arr[i]._str);
                }
                else
                    printf("Элемент с данным ключом не найден\n");
            }
            break;
        case 3:
            quickSort(arr, 0, cnt - 1);
            printf("Таблица отсортирована\n");
            break;
        case 4:
            menu();
            break;
        case 5:
            return 0;
            break;
        default:
            printf("Выберите корректную команду из меню\n");
            break;
        }
    }
    return 0;
}
