#ifndef LIST_H
#define LIST_H

typedef int item;
typedef struct _list_node list_node;
typedef struct _list_node
{
    char data[100];
    list_node *next;
    list_node *prev;
} list_node;

typedef struct listIterator
{
    list_node *node;
} listIterator;

typedef struct
{
    list_node *head;
} list;

list *listCreate();
void listPrint(list *l);
void listInsert(list *lst, char *data);
void listRemove(list *lst, char *data);
int listLen(list *lst);
void listInsertToK(list *lst, int k, char *data);
listIterator *iteratorCreate(list *lst);
void iteratorNext(listIterator *it);
list_node *iteratorGet(listIterator *it);
void iteratorSet(list_node *l, listIterator *it);
void listInsertb(list *lst, char *data);

#endif
