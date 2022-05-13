#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

listIterator *iteratorCreate(list *lst)
{
    if (lst != NULL)
    {
        listIterator *it = (listIterator *)malloc(sizeof(listIterator));
        it->node = lst->head;
        return it;
    }
    else
        return NULL;
}

void iteratorNext(listIterator *it)
{
    if (it->node == NULL)
    {
        printf("Конец списка\n");
    }
    else
    {
        it->node = it->node->next;
    }
}

list_node *iteratorGet(listIterator *it)
{
    return it->node;
}

void iteratorSet(list_node *lst, listIterator *it)
{
    it->node = lst;
}

list *listCreate()
{
    list *lst = (list *)malloc(sizeof(list));
    lst->head = (list_node *)malloc(sizeof(list_node));
    lst->head->next = NULL;
    lst->head->prev = NULL; //
    strcpy(lst->head->data, "BARRIER");
    return lst;
}

void listPrint(list *lst)
{
    listIterator *it = iteratorCreate(lst);
    if (it->node)
    {
        while (it->node != NULL)
        {
            if (it->node->data != "BARRIER")
            {
                printf("%s", it->node->data);
                if (it->node->next != NULL)
                    printf(" -> ");
            }
            //  enum_out(it->node->data);
            it->node = it->node->next;
        }
        // printf("BARRIER");
        printf("\n");
    }
}

void listInsert(list *lst, char *data) // в конец листа
{
    listIterator *it = iteratorCreate(lst);
    if (it->node)
    {
        while (it->node->next)
        {
            iteratorNext(it);
        }
        list_node *tail = (list_node *)malloc(sizeof(list_node));
        tail->next = NULL;
        strcpy(tail->data, "BARRIER");
        strcpy(it->node->data, data);
        it->node->next = tail;
        tail->prev = it->node;
    }
    else
        printf("Список не существует\n");
    free(it);
}

void listInsertb(list *lst, char *data) // в конец листа
{
    listIterator *it = iteratorCreate(lst);
    if (it->node)
    {
        list_node *tail = (list_node *)malloc(sizeof(list_node));
        tail->next = it->node;
        tail->prev = NULL;
        strcpy(tail->data, data);
        it->node->prev = tail;
        lst->head = tail;
    }
    else
        printf("Список не существует\n");
    free(it);
}

void listRemove(list *lst, char *data) // удаление узла листа
{
    int flag = 0;
    listIterator *it = iteratorCreate(lst);
    list_node *prew;
    char *f;
    if (it->node)
    {
        if (strncmp(it->node->data, data, 10) == 0) // если значение узла = значению удаляемого узла
        {
            lst->head = it->node->next;
            free(it->node);
            it->node = NULL;
        }
        else
        {
            while (it->node->next) // пока существует следующий узел
            {
                if (strncmp(it->node->next->data, data, 10) == 0) // если значение этого самого следующего узла = искомому
                {
                    prew = it->node;
                    iteratorNext(it);
                    flag = 1;
                    if (it->node->next != NULL)
                    {
                        prew->next = it->node->next;
                        it->node->next->prev = prew->next;
                    }
                    free(it->node);
                    it->node = NULL;
                    break;
                }
                iteratorNext(it);
            }
            if (!flag)
                printf("Элемента нет в списке\n");
            else
                printf("Элемент удалён\n");
        }
    }
    else
        printf("Список не существует\n");
    free(it);
}

int listLen(list *lst) // длина списка
{
    int count = 0;
    listIterator *it = iteratorCreate(lst);
    iteratorSet(lst->head, it);
    if (it->node)
    {
        while (it->node->next && it->node->next->data != "BARRIER")
        {
            count++;
            iteratorNext(it);
        }
    }
    else
        printf("The list doesn't exist!\n");
    free(it);
    //count++;
    return count;
}

void listInsertToK(list *lst, int k, char *data) // функция сама
{
    while (listLen(lst) < k)
    {
        listInsert(lst, data);
    }
}
