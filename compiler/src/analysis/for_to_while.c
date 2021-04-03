/*****************************************************************************
 *
 * Module: Change for loops to while loops
 *
 * Prefix: FTW
 *
 * Description: Changes all for loops to while loops
 *
 *****************************************************************************/

#include "for_to_while.h"

#include "types.h"
#include "tree_basic.h"
#include "traverse.h"
#include "dbug.h"

#include "memory.h"
#include "free.h"
#include "str.h"
#include "copy.h"
#include "ctinfo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// used the key value linked list from: https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm
/*
*
*   This is a key value linkedlist helper to function for the for to while part of the code analysis
*
*/

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

keyvalueListNode *KeyValueDeleteFirst(keyvalueListNode *head, const char *key, const char *value)
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

/*
*
*   End of linked list
*
*/

struct INFO
{
    node *var_declarations;
    int counter;
    node *statements;
    keyvalueListNode *names;
};

#define INFO_VARDECLS(n) ((n)->var_declarations)
#define INFO_COUNTER(n) ((n)->counter)
#define INFO_STMTS(n) ((n)->statements)
#define INFO_NAMES(n) ((n)->names)

static info *MakeInfo()
{
    info *result;

    DBUG_ENTER("MakeInfo");

    result = (info *)MEMmalloc(sizeof(info));

    INFO_VARDECLS(result) = NULL;
    INFO_STMTS(result) = NULL;
    INFO_NAMES(result) = NULL;
    INFO_COUNTER(result) = 0;

    DBUG_RETURN(result);
}

static info *FreeInfo(info *info)
{
    DBUG_ENTER("FreeInfo");

    KeyValueDispose(INFO_NAMES(info));

    info = MEMfree(info);

    DBUG_RETURN(info);
}

void append(node *head, node *new)
{
    if (head == NULL)
    {
        return;
    }

    if (NODE_TYPE(head) == N_stmts)
    {
        if (STMTS_NEXT(head) == NULL)
        {
            STMTS_NEXT(head) = new;
        }
        else
        {
            append(STMTS_NEXT(head), new);
        }
    }
    else if (NODE_TYPE(head) == N_vardecl)
    {
        if (VARDECL_NEXT(head) == NULL)
        {
            VARDECL_NEXT(head) = new;
        }
        else
        {
            append(VARDECL_NEXT(head), new);
        }
    }
}

node *FTWfor(node *arg_node, info *arg_info)
{
    DBUG_ENTER("FTWfor");
    DBUG_PRINT("FTW", ("FTWfor"));

    const char *varname = FOR_LOOPVAR(arg_node);

    char *name = STRcatn(3, varname, "_", STRitoa(INFO_COUNTER(arg_info)));
    INFO_COUNTER(arg_info)
    ++;

    if (INFO_NAMES(arg_info) == NULL)
    {
        INFO_NAMES(arg_info) = KeyValueCreateList(varname, name, NULL);
    }
    else
    {
        INFO_NAMES(arg_info) = KeyValueDeleteFirst(INFO_NAMES(arg_info), varname, name);
    }

    FOR_BLOCK(arg_node) = TRAVopt(FOR_BLOCK(arg_node), arg_info);
    INFO_NAMES(arg_info) = KeyValueFrontOfList(INFO_NAMES(arg_info));

    node *for_step = TBmakeVardecl(STRcat(name, "_step"), T_int, NULL, NULL, NULL);
    node *for_stop = TBmakeVardecl(STRcat(name, "_stop"), T_int, NULL, NULL, for_step);
    node *for_start = TBmakeVardecl(STRcpy(name), T_int, NULL, NULL, for_stop);

    if (INFO_VARDECLS(arg_info) == NULL)
    {
        INFO_VARDECLS(arg_info) = for_start;
    }
    else
    {
        append(INFO_VARDECLS(arg_info), for_start);
    }

    node *expressionOfSteps;

    if (FOR_STEP(arg_node))
    {
        expressionOfSteps = COPYdoCopy(FOR_STEP(arg_node));
    }
    else
    {
        expressionOfSteps = TBmakeNum(1);
    }

    INFO_STMTS(arg_info) = TBmakeStmts(
        TBmakeAssign(TBmakeVarlet(STRcpy(VARDECL_NAME(for_start)), for_start, NULL), COPYdoCopy(FOR_START(arg_node))),
        TBmakeStmts(TBmakeAssign(TBmakeVarlet(STRcpy(VARDECL_NAME(for_stop)), for_stop, NULL), COPYdoCopy(FOR_STOP(arg_node))),
                    TBmakeStmts(TBmakeAssign(TBmakeVarlet(STRcpy(VARDECL_NAME(for_step)), for_step, NULL), expressionOfSteps), NULL)));

    node *new_block = COPYdoCopy(FOR_BLOCK(arg_node));

    node *assign = TBmakeAssign(
        TBmakeVarlet(STRcpy(VARDECL_NAME(for_start)), for_start, NULL),
        TBmakeBinop(BO_add, TBmakeVar(STRcpy(VARDECL_NAME(for_start)), for_start, NULL), TBmakeVar(STRcpy(VARDECL_NAME(for_step)), for_step, NULL)));

    if (new_block == NULL)
    {
        new_block = TBmakeStmts(assign, NULL);
    }
    else
    {
        append(new_block, TBmakeStmts(assign, NULL));
    }

    FREEdoFreeTree(arg_node);

    arg_node = TBmakeWhile(TBmakeTernary(
                               TBmakeBinop(BO_gt, TBmakeVar(STRcpy(VARDECL_NAME(for_step)), for_step, NULL), TBmakeNum(0)),
                               TBmakeBinop(BO_lt, TBmakeVar(STRcpy(VARDECL_NAME(for_start)), for_start, NULL), TBmakeVar(STRcpy(VARDECL_NAME(for_stop)), for_stop, NULL)),
                               TBmakeBinop(BO_gt, TBmakeVar(STRcpy(VARDECL_NAME(for_start)), for_start, NULL), TBmakeVar(STRcpy(VARDECL_NAME(for_stop)), for_stop, NULL))),
                           new_block);

    DBUG_RETURN(arg_node);
}

node *FTWfunbody(node *arg_node, info *arg_info)
{
    DBUG_ENTER("FTWfunbody");
    DBUG_PRINT("FTW", ("FTWfunbody"));

    FUNBODY_STMTS(arg_node) = TRAVopt(FUNBODY_STMTS(arg_node), arg_info);

    if (INFO_VARDECLS(arg_info) == NULL)
    {
        DBUG_RETURN(arg_node);
    }

    if (FUNBODY_VARDECLS(arg_node) == NULL)
    {
        FUNBODY_VARDECLS(arg_node) = INFO_VARDECLS(arg_info);
    }
    else
    {
        append(FUNBODY_VARDECLS(arg_node), INFO_VARDECLS(arg_info));
    }

    INFO_VARDECLS(arg_info) = NULL;

    DBUG_RETURN(arg_node);
}

node *FTWstmts(node *arg_node, info *arg_info)
{
    DBUG_ENTER("FTWstmts");
    DBUG_PRINT("FTW", ("FTWstmts"));

    nodetype type = NODE_TYPE(STMTS_STMT(arg_node));

    STMTS_STMT(arg_node) = TRAVdo(STMTS_STMT(arg_node), arg_info);

    if (type != N_for)
    {
        STMTS_NEXT(arg_node) = TRAVopt(STMTS_NEXT(arg_node), arg_info);
    }

    if (type == N_for)
    {
        node *oldnode = arg_node;
        append(INFO_STMTS(arg_info), arg_node);
        arg_node = INFO_STMTS(arg_info);
        INFO_STMTS(arg_info) = NULL;

        STMTS_NEXT(oldnode) = TRAVopt(STMTS_NEXT(oldnode), arg_info);
    }

    DBUG_RETURN(arg_node);
}

node *FTWvarlet(node *arg_node, info *arg_info)
{
    DBUG_ENTER("FTWvarlet");
    DBUG_PRINT("FTW", ("FTWvarlet"));

    if (KeyValueSearch(INFO_NAMES(arg_info), VARLET_NAME(arg_node)) == NULL)
    {
        DBUG_RETURN(arg_node);
    }
    else
    {
        VARLET_NAME(arg_node) = STRcpy(KeyValueSearch(INFO_NAMES(arg_info), VARLET_NAME(arg_node))->value);
    }

    DBUG_RETURN(arg_node);
}

node *FTWvar(node *arg_node, info *arg_info)
{
    DBUG_ENTER("FTWvar");
    DBUG_PRINT("FTW", ("FTWvar"));

    if (KeyValueSearch(INFO_NAMES(arg_info), VAR_NAME(arg_node)) == NULL)
    {
        DBUG_RETURN(arg_node);
    }
    else
    {
        VAR_NAME(arg_node) = STRcpy(KeyValueSearch(INFO_NAMES(arg_info), VAR_NAME(arg_node))->value);
    }

    DBUG_RETURN(arg_node);
}

/*
 * Traversal start function
 */
node *FTWdoForToWhile(node *syntaxtree)
{
    DBUG_ENTER("FTWdoForToWhile");
    DBUG_PRINT("FTW", ("FTWdoForToWhile"));

    info *info = MakeInfo();

    TRAVpush(TR_ftw);
    syntaxtree = TRAVdo(syntaxtree, info);
    TRAVpop();

    FreeInfo(info);

    DBUG_RETURN(syntaxtree);
}