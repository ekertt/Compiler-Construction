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
#include "traverse.h" fad
#include "dbug.h"
#include "print.h"
#include "memory.h"
#include "free.h"
#include "str.h"
#include "ctinfo.h"

/*
 * INFO structure
 */

struct INFO
{
    node *table;
    int params;
    int arguments;
};

/*
 * INFO macros
 */

#define INFO_SYMBOL_TABLE(n) ((n)->table)
#define INFO_PARAMS(n) ((n)->params)
#define INFO_ARGUMENTS(n) ((n)->arguments)

/*
 * INFO functions
 */

static info *MakeInfo(node *parent)
{
    info *result;

    DBUG_ENTER("MakeInfo");

    result = (info *)MEMmalloc(sizeof(info));

    DBUG_RETURN(result);
}

static info *FreeInfo(info *info)
{
    DBUG_ENTER("FreeInfo");

    info = MEMfree(info);

    DBUG_RETURN(info);
}

*node STadd(node *table, node *entry)
{

}

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

    STprint(SYMBOLTABLEENTRY_NEXT(list), tabs);
}