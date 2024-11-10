#include <stdio.h>

#include "list.h"

int main()
{
    printf("sizeof(Array) = %d \n sizeof(Cell) = %d \n", sizeof(array), sizeof(Cell));

    array list = {};

    Create(&list);

    for(int i = 0; i < 10; i++)
    {
        
        printf("%d\n", i);
        InsHead(&list, i);
    //    printf("\t prev[%d] = %d next[%d] = %d value[%d] = %d \n", i, list.element[i].prev, i, list.element[i].next, i, list.element[i].value);
    }

    Dump(&list);

    for(int i = 0; i < 10; i++)
    {
        DelTail(&list);
    }

    Destroy(&list);

    return 0;
}