#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listnode
{
    char *value;
    int counter;
    struct listnode* next;
} listnode;

typedef void (*callback)(listnode* data);

listnode *LLcreate(char *value, int counter, listnode* next)
{
    listnode* new_listnode = (listnode*)malloc(sizeof(listnode));
    new_listnode->value = value;
    new_listnode->counter = counter;
    new_listnode->next = next;

    return new_listnode;
}

listnode *LLprepend(listnode* head, char *value, int counter)
{
    listnode* new_listnode = LLcreate(value, counter, head);
    head = new_listnode;
    return head;
}

listnode *LLappend(listnode* head, char *value, int counter)
{
    if (head == NULL) return NULL;

    listnode *cursor = head;

    while(cursor->next != NULL) cursor = cursor->next;

    listnode* new_listnode =  LLcreate(value, counter, NULL);

    cursor->next = new_listnode;

    return head;
}

void LLtraverse(listnode* head, callback f)
{
    listnode* cursor = head;
    while(cursor != NULL)
    {
        f(cursor);
        cursor = cursor->next;
    }
}

listnode *LLremove_front(listnode* head)
{
    if ( head == NULL) return NULL;
    listnode *front = head;
    head = head->next;
    front->next = NULL;
    /* is this the last listnode in the list */
    if (front == head) head = NULL;
    free(front);

    return head;
}

listnode *LLremove_back(listnode* head)
{
    if(head == NULL)
        return NULL;

    listnode *cursor = head;
    listnode *back = NULL;
    while(cursor->next != NULL)
    {
        back = cursor;
        cursor = cursor->next;
    }

    if(back != NULL)
        back->next = NULL;

    if(cursor == head)
        head = NULL;

    free(cursor);

    return head;
}

listnode *LLremove_any(listnode* head, listnode* nd)
{
    if(nd == NULL) return NULL;
    /* if the listnode is the first listnode */
    if(nd == head) return LLremove_front(head);

    /* if the listnode is the last listnode */
    if(nd->next == NULL)
        return LLremove_back(head);

    /* if the listnode is in the middle */
    listnode* cursor = head;
    while(cursor != NULL)
    {
        if(cursor->next == nd) break;
        cursor = cursor->next;
    }

    if(cursor != NULL)
    {
        listnode* tmp = cursor->next;
        cursor->next = tmp->next;
        tmp->next = NULL;
        free(tmp);
    }
    return head;
}

void LLprint(listnode* cursor)
{
    while (cursor!=NULL)
    {
        printf("%s\n", cursor->value);
        cursor = cursor->next;
    }
}

listnode *LLsearch(listnode* head, const char *value)
{

    listnode *cursor = head;
    while (cursor!=NULL)
    {
        if (strcmp ( cursor->value, value) == 0) return cursor;

        cursor = cursor->next;
    }
    return NULL;
}

void LLdispose(listnode *cursor)
{
    if (cursor == NULL) return;

    listnode *tmp;

    while (cursor != NULL)
    {
        tmp = cursor->next;
        free(cursor->value);
        free(cursor);

        cursor = tmp;
    }
    
}

int LLcount(listnode *head)
{
    listnode *cursor = head;
    int c = 0;
    while (cursor != NULL)
    {
        c++;
        cursor = cursor->next;
    }
    return c;
}

listnode *LLreverse(listnode* head)
{
    listnode* prev    = NULL;
    listnode* current = head;
    listnode* next;
    while (current != NULL)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
}