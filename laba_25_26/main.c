#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main()
{
    printf("Operations:\n");
    printf("a - to add element n to the list\n");
    printf("d - to delete element n from the list\n");
    printf("e - to check the list if it is empty\n");
    printf("p - to print the list\n");
    printf("s - to sort the list\n");
    printf("# - to finish.\n");
    char op = 'a';
    int e = 1;
    struct list *L = NULL;
    while (op != '#')
    {
        scanf("%c", &op);
        if (op == 'a')
        {
            scanf("%d", &e);
            if (L == NULL)
            {
                L = init(e);
            }
            else
            {
                add(L, e);
            }
        }
        if (op == 'd')
        {
            scanf("%d", &e);
            struct list *d = find(L, e);
            if (d->prev == NULL)
            {
                deletehead(d);
            }
            if (d->prev != NULL)
            {
                delete (d);
            }
        }
        if (op == 'e')
        {
            if (empty(L) == 0)
            {
                printf("List is empty\n");
            }
            else
            {
                printf("List is not empty\n");
            }
        }
        if (op == 'p')
        {
            print(L);
            printf("\n");
        }
        if (op == 's')
        {
            if (L != NULL)
            {
                int min = minim(L);
                replace(find(L, min), min);
            }
        }
    }

    L = rem(L);
    return 0;
}
