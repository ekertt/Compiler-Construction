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

linkedlist *push(char *val, int count, linkedlist *next)
{
    linkedlist *newList = (linkedlist *)malloc(sizeof(linkedlist));
    newList->val = val;
    newList->count = count;
    newList->next = next;

    return newList;
}

linkedlist *add(linkedlist *head, char *val, int count)
{
    if (head == NULL)
    {
        return NULL;
    }

    linkedlist *current = head;

    while (current->next != NULL)
    {
        current = current->next;
    }

    linkedlist *newList = push(val, count, NULL);

    current->next = newList;

    return head;
}

void dipsose(linkedlist *current)
{
    if (current == NULL)
    {
        return;
    }

    linkedlist *tmp;

    while (current != NULL)
    {
        tmp = current->next;
        free(current->val);
        free(current);

        current = tmp;
    }
}

linkedlist *search(linkedlist *head, const char *val)
{

    linkedlist *current = head;
    while (current != NULL)
    {
        if (strcmp(current->val, val) == 0)
        {
            return current;
        }

        current = current->next;
    }
    return NULL;
}