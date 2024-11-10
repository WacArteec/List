#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "list.h"

enum TypeOfCell
{
    free_unit = -1,
    not_exist  = -1
};

enum SizeChanger
{
    more_size,
    less_size
};

void Create(struct array* list)
{
    list->element = (Cell*) calloc(3, sizeof(Cell));

    list->element[0].next = 3;
    list->element[0].prev = 1;

    list->size = 2;

    list->freecell = 2;

    list->freepos = 1;
}

int Search(struct array* list, int elem)
{
    int position = 0;
    bool found = false;

    for(position = 0; position < sizeof(list->element) / sizeof(Cell); position++)
    {
        if(list->element[position].value == elem)
        {
            found = true;
            break;
        }
    }

    if(found == true)
        return position;

    else
        return not_exist;
}

void ChangeSize(struct array* list)
{
    assert(list != NULL);
$$$ printf("%d free = %d size = %d element = %p \n", __LINE__, list->freecell, list->size, list->element);

    list->element = (Cell*) realloc(list->element, 2 * (list->size + 1) * sizeof(Cell));
$$$ printf("%d free = %d size = %d element = %p \n", __LINE__, list->freecell, list->size, list->element);
    assert(list->element); //минимальный пример, знаем, как работает, усложняем

    memset(list->element + list->size + 1, free_unit, (list->size + 1) * sizeof(Cell));

    list->freecell = list->size + 1;

    list->freepos = list->freecell;

    list->size = 2 * list->size + 1;

$$$ printf("%d free = %d size = %d element = %p \n", __LINE__, list->freecell, list->size, list->element);
}

void NeedSize(struct array* list)
{
    if(list->freecell < 1)
        ChangeSize(list);
}


void InsAfter(struct array* list, int position, int add)
{
    list->element[list->freepos].value = add;
    list->element[list->freepos].next  = list->element[position].next;
    list->element[list->freepos].prev  = position;

    list->element[list->element[position].next].prev = list->freepos;

    list->element[position].next = list->freepos;

    list->freecell--;

    NeedSize(list);

    while(list->element[list->freepos].prev != free_unit && list->freepos <= list->size)
        list->freepos++;
}

void InsBefore(struct array* list, int position, int add)
{
    list->element[list->freepos].value = add;
    list->element[list->freepos].prev  = list->element[position].prev;
    list->element[list->freepos].next  = position;

    list->element[list->element[position].prev].next = list->freepos;

    list->element[position].prev = list->freepos;

    list->freecell--;

    NeedSize(list);

    while(list->element[list->freepos].prev != free_unit && list->freepos <= list->size)
        list->freepos++;
}

void InsHead (struct array* list, int add)
{
    InsAfter(list, 0, add);
}

void DelPos (struct array* list, int position)
{
    list->element[list->element[position].prev].next = list->element[position].next;

    list->element[list->element[position].next].prev = list->element[position].prev;

    list->element[position].next = -1;
    list->element[position].prev = -1;
    list->element[position].value = -1;

    list->freecell++;
}
 
void DelBefore (struct array* list, int position)
{
    DelPos(list, list->element[position].prev);
}

void DelAfter (struct array* list, int position)
{
    DelPos(list, list->element[position].next);
}

void DelTail (struct array* list)
{
    DelPos(list, list->element[0].prev);
}

void Destroy (struct array* list) //lonely lol
{
    free(list->element);

    list->element = NULL;

    list->freecell = 0;
    list->size = 0;
}

int Verification(struct array* list)
{
    if(list == 0)
        return 1;

    else
        return 0;
}

void Dump(struct array* list)
{
    for(int i = 0; i < list->size + 1; i++)
    {
        printf("\t prev[%d] = %d next[%d] = %d value[%d] = %d \n", i, list->element[i].prev, i, list->element[i].next, i, list->element[i].value);
    }
}