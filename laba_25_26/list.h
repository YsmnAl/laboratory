#ifndef list_h
#define list_h

struct list
{
    int k;
    struct list *next;
    struct list *prev;
};

struct list *add(struct list *l, int n);

struct list *find(struct list *l, int n);

struct list *delete (struct list *l);

int empty(struct list *l);

void print(struct list *l);

struct list *rem(struct list *l);

struct list *replace(struct list *l, int min);

void insert(struct list *after_node, int value);

int minim(struct list *l);

struct list *init(int a);

struct list *deletehead(struct list *root);

#endif
