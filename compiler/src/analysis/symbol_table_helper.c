/*****************************************************************************
 *
 * Module: symbol table
 *
 * Prefix: ST
 *
 * Description: this initializes the symbol table
 *
 *****************************************************************************/
#include "symbol_table.h"
#include "symbol_table_helper.h"

#include "types.h"
#include "tree_basic.h"
#include "traverse.h"
#include "dbug.h"
#include "print.h"
#include "memory.h"
#include "free.h"
#include "str.h"
#include "ctinfo.h"
#include "string.h"

/*
 * INFO structure
 */

struct INFO
{
    node *table;
    int params;
    int arguments;
};

node *STadd(node *table, node *entry)
{
    DBUG_ENTER("STadd");
    printf("Finding: %s ", SYMBOLTABLEENTRY_NAME(entry));
    // printf("Table ok?: %d ", table != NULL);

    if (STfind(table, SYMBOLTABLEENTRY_NAME(entry)) != NULL)
    {
        CTIerror("Redefinition of var %s at line %d", SYMBOLTABLEENTRY_NAME(entry), NODE_LINE(entry), NODE_COL(entry));
        return NULL;
    }

    node *latestEntry = STlatestEntry(SYMBOLTABLE_ENTRY(table));

    if (latestEntry == NULL)
    {
        return SYMBOLTABLE_ENTRY(table) = entry;
    }

    SYMBOLTABLEENTRY_NEXT(latestEntry) = entry;
    DBUG_RETURN(entry);
}

node *STfind(node *symbol_table, const char *name)
{
    if (SYMBOLTABLE_ENTRY(symbol_table) == NULL)
    {
        return NULL;
    }

    node *entry = SYMBOLTABLE_ENTRY(symbol_table);
    return STfindEntry(entry, name);
}

node *STfindEntry(node *entry, const char *name)
{
    if (STReq(SYMBOLTABLEENTRY_NAME(entry), name))
    {
        return entry;
    }

    if (SYMBOLTABLEENTRY_NEXT(entry) != NULL)
    {
        return STfindEntry(SYMBOLTABLEENTRY_NEXT(entry), name);
    }

    return NULL;
}

node *STlatestEntry(node *linkedlist)
{
    if (linkedlist == NULL)
    {
        return linkedlist;
    }

    if (SYMBOLTABLEENTRY_NEXT(linkedlist) == NULL)
    {
        return linkedlist;
    }

    return STlatestEntry(SYMBOLTABLEENTRY_NEXT(linkedlist));
}

// INSERT FIND AND LAST NEEDED
void STdisplay(node *table, size_t tabs)
{
    STprint(SYMBOLTABLE_ENTRY(table), tabs);
}

void STprint(node *list, size_t tabs)
{
    if (list == NULL)
        return;

    for (size_t i = 0; i < tabs; i++)
        printf("\t");

    // print the type
    printf("Type: ");

    switch (SYMBOLTABLEENTRY_TYPE(list))
    {
    case T_void:
        printf("void");
        break;
    case T_bool:
        printf("bool");
        break;
    case T_int:
        printf("int");
        break;
    case T_float:
        printf("float");
        break;
    case T_unknown:
        DBUG_ASSERT(0, "unknown type detected!");
    }

    printf(", Name: %s\n", SYMBOLTABLEENTRY_NAME(list));

    // if (SYMBOLTABLEENTRY_TABLE(list) != NULL)
    //     STdisplay(SYMBOLTABLEENTRY_TABLE(list), tabs + 1);

    STdisplay(SYMBOLTABLEENTRY_NEXT(list), tabs);
}