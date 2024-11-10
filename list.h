#ifndef LIST_H
#define LIST_H

#define $$$

#include <stdlib.h>

struct Cell
{
    int value = 0;
    int prev = 0;
    int next = 0;
};

struct array
{
    Cell* element = NULL;
    unsigned int size = 0;
    unsigned int freecell = 0;
    unsigned int freepos = 0;
};

void Create(struct array* list);
int Search(struct array* list, int elem);
void InsHead (struct array* list, int add);
void InsAfter(struct array* list, int position, int add);
void DelPos (struct array* list, int position);
void DelBefore (struct array* list, int position);
void DelAfter (struct array* list, int position);
void DelTail (struct array* list);
void Dump(struct array* list);
void Destroy (struct array* list); //lonely lol

#endif //LIST_H