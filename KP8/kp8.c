#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void menu()
{
    printf("\nМеню:\n");
    printf("0) Добавить элемент в начало списка\n");
    printf("1) Добавить элемент в конец списка\n");
    printf("2) Удалить элемент из списка\n");
    printf("3) Вывести список\n");
    printf("4) Вывести длину списка\n");
    printf("5) Добавить в список копии одного элемента до длины списка k\n");
    printf("6) Меню\n");
    printf("7) Выход\n");
}

int main(void)
{
    char *data;
    list *lst = listCreate();
    listIterator *it = iteratorCreate(lst);
    char c;
    menu();
    while (1)
    {
        scanf("%c", &c);
        iteratorSet(lst->head, it);
        if (c == '\n' || c == ' ')
            continue;
        switch (c)
        {
        case '0':
            printf("Для того, чтобы добавить элемент, введите:\n");
            scanf("%s", data);
            listInsertb(lst, data);
            printf("Элемент добавлен\n");
            break;
        case '1':
            printf("Для того, чтобы добавить элемент, введите:\n");
            scanf("%s", data);
            listInsert(lst, data);
            printf("Элемент добавлен\n");
            break;
        case '2':
            printf("Для того, чтобы удалить элемент, введите:\n");
            scanf("%s", data);
            listRemove(lst, data);
            break;
        case '3':
            listPrint(lst);
            break;
        case '4':
            printf("Длина списка: %d\n", listLen(lst));
            break;
        case '5':
            printf("Введите k - длину итогового списка:\n");
            int k;
            scanf("%d", &k);
            printf("Введите элемент, которым вы хотите дополнить список до длины %d:\n", k);
            scanf("%s", data);
            listInsertToK(lst, k, data);
            printf("Нужное количество элементов добавлено\n");
            break;
        case '6':
            menu();
            break;
        case '7':
            free(it);
            free(lst);
            return 0;
        default:
            printf("Действия с таким номером не существует, выберите команду из меню\n");
            menu();
            break;
        }
    }
}
