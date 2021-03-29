// used some linked list functions from: https://www.learn-c.org/en/Linked_lists
/*
*
*   This is a linkedlist helper to function for the for to while part of the code analysis
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linkedlist
{
    char *val;
    int count;
    struct linkedlist *next;
} linkedlist;

typedef void (*callback)(linkedlist *data);

linkedlist *LLcreate(char *val, int count, linkedlist *next)
{
    linkedlist *newList = (linkedlist *)malloc(sizeof(linkedlist));
    newList->val = val;
    newList->count = count;
    newList->next = next;

    return newList;
}

linkedlist *LLappend(linkedlist *head, char *val, int count)
{
    if (head == NULL)
        return NULL;

    linkedlist *cursor = head;

    while (cursor->next != NULL)
        cursor = cursor->next;

    linkedlist *new_linkedlist = LLcreate(val, count, NULL);

    cursor->next = new_linkedlist;

    return head;
}

void LLdispose(linkedlist *cursor)
{
    if (cursor == NULL)
        return;

    linkedlist *tmp;

    while (cursor != NULL)
    {
        tmp = cursor->next;
        free(cursor->val);
        free(cursor);

        cursor = tmp;
    }
}

linkedlist *LLsearch(linkedlist *head, const char *val)
{

    linkedlist *cursor = head;
    while (cursor != NULL)
    {
        if (strcmp(cursor->val, val) == 0)
            return cursor;

        cursor = cursor->next;
    }
    return NULL;
}