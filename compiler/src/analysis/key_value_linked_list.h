// used the key value linked list from: https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm
/*
*
*   This is a key value linkedlist helper to function for the for to while part of the code analysis
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct keyvalueListNode
{
    const char *key;
    const char *value;
    struct keyvalueListNode *next;
} keyvalueListNode;

typedef void (*callback)(keyvalueListNode *data);

keyvalueListNode *KeyValueCreateList(const char *key, const char *value, keyvalueListNode *next)
{
    keyvalueListNode *new_list_node = (keyvalueListNode *)malloc(sizeof(keyvalueListNode));
    new_list_node->key = key;
    new_list_node->value = value;
    new_list_node->next = next;

    return new_list_node;
}

keyvalueListNode *KeyValueDeleteFirst(const char *key, const char *value, keyvalueListNode *head)
{
    keyvalueListNode *new_keyvalueListNode = KeyValueCreateList(key, value, head);
    head = new_keyvalueListNode;
    return head;
}

keyvalueListNode *KeyValueFrontOfList(keyvalueListNode *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    keyvalueListNode *current = head;
    head = head->next;
    current->next = NULL;
    if (current == head)
    {
        head = NULL;
    }
    free(current);

    return head;
}

keyvalueListNode *KeyValueRemoveLast(keyvalueListNode *node)
{

    keyvalueListNode *current = node;
    keyvalueListNode *back = NULL;

    if (node == NULL)
        return NULL;

    while (current->next != NULL)
    {
        back = current;
        current = current->next;
    }

    if (back != NULL)
    {
        back->next = NULL;
    }

    if (current == node)
    {
        node = NULL;
    }

    free(current);

    return node;
}

keyvalueListNode *KeyValueSearch(keyvalueListNode *head, const char *key)
{

    keyvalueListNode *current = head;
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current;
        }

        current = current->next;
    }
    return NULL;
}

void KeyValueDispose(keyvalueListNode *head)
{
    keyvalueListNode *current, *temp;

    if (head != NULL)
    {
        current = head->next;
        head->next = NULL;
        while (current != NULL)
        {
            temp = current->next;
            free(current);
            current = temp;
        }
    }
}