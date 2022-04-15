#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct list *deletehead(struct list *root)
{
    struct list *temp;
    temp = root->next;
    temp->prev = NULL;
    free(root); // освобождение памяти текущего корня
    root = NULL;
    return (temp); // новый корень списка
}

struct list *add(struct list *lst, int number) //указатель на узел, после которого происходит добавление, и значение
{
    if (lst->next == NULL)
    {
        struct list *temp, *p;
        temp = (struct list *)malloc(sizeof(struct list));
        p = lst->next;    // сохранение указателя на следующий узел
        lst->next = temp; // предыдущий узел указывает на создаваемый
        temp->k = number; // сохранение поля данных добавляемого узла
        temp->next = p;   // созданный узел указывает на следующий узел
        temp->prev = lst; // созданный узел указывает на предыдущий узел
        if (p != NULL)
            p->prev = temp;
        return (temp);
    }
    add(lst->next, number);
}
struct list *init(int a) // а- значение первого узла
{
    struct list *lst;
    // выделение памяти под корень списка
    lst = (struct list *)malloc(sizeof(struct list));
    lst->k = a;
    lst->next = NULL; // указатель на следующий узел
    lst->prev = NULL; // указатель на предыдущий узел
    return (lst);
}

struct list *find(struct list *l, int n)
{
    if (l->k == n)
    {
        return l;
    }
    find(l->next, n);
}

struct list *delete (struct list *l) //указатель на удаляемый узел
{
    struct list *prev, *next;
    prev = l->prev; // узел, предшествующий lst
    next = l->next; // узел, следующий за lst
    if (prev != NULL)
        prev->next = l->next; // переставляем указатель
    if (next != NULL)
        next->prev = l->prev; // переставляем указатель
    free(l);                  // освобождаем память удаляемого элемента
    return (prev);
}

int empty(struct list *l)
{
    if (l == NULL)
        return 0;
    else
        return 1;
}

/*void print(struct list *l)
{
    if (l == NULL)
    {
        return;
    }
    printf("%d ", l->k);
    print(l->next);
}*/
void print(struct list *lst)
{
    struct list *p;
    p = lst;
    do
    {
        printf("%d ", p->k); // вывод значения элемента p
        p = p->next;         // переход к следующему узлу
    } while (p != NULL);     // условие окончания обхода
}

struct list *rem(struct list *l)
{
    if (l == NULL)
        return l;
    if (l->next == NULL)
    {
        free(l);
        return NULL;
    }
    if (l->next != NULL)
        l->next = rem(l->next);
}

int length(struct list *l, int r)
{
    if (l == NULL)
    {
        return r;
    }
    r++;
    if (l->next == NULL)
    {
        return r;
    }
    length(l->next, r);
}

int minim(struct list *l)
{
    if (l != NULL)
    {
        if (l->k <= l->next->k)
        {
            minim(l->next);
        }
        else
        {
            return l->next->k;
        }
    }
}

void insert(struct list *after_node, int value)
{
    struct list *inserted = (struct list *)malloc(sizeof(struct list));
    inserted->k = value;
    inserted->next = after_node->next;
    after_node->next = inserted;
    inserted->prev = after_node;
    inserted->next->prev = inserted;
}

struct list *replace(struct list *l, int min)
{
    if (l == NULL)
    {
        return l;
    }
    //struct list *t = find(l, min)->prev;
    // struct list *s = find(l, min)->prev;
    if ((min >= l->prev->k) && (min <= l->next->k) && (l->prev != NULL))
    {
        struct list *t = l->prev;
        delete (find(l, min));
        insert(t, min);
        return l;
    }
    /*if ((min <= l->next->k) && (l->prev == NULL))
    {
        struct list *lst = (struct list *)malloc(sizeof(struct list));
        lst->k = min;
        lst->next = l;    // указатель на следующий узел
        lst->prev = NULL; // указатель на предыдущий узел
        return (lst);
    }*/
    replace(l->prev, min);
    return l;
}
