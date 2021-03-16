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
    node *table = TBmakeSymboltable(NULL);
    INFO_SYMBOL_TABLE(result) = table;

    DBUG_RETURN(result);
}

static info *FreeInfo(info *info)
{
    DBUG_ENTER("FreeInfo");

    info = MEMfree(info);

    DBUG_RETURN(info);
}

node *STprogram(node *arg_node, info *arg_info)
{
    DBUG_ENTER("STprogram");
    DBUG_PRINT("ST", ("STprogram"));

    PROGRAM_SYMBOLTABLE(arg_node) = INFO_SYMBOL_TABLE(arg_info);
    PROGRAM_DECLS(arg_node) = TRAVopt(PROGRAM_DECLS(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *STglobdef(node *arg_node, info *arg_info)
{
    DBUG_ENTER("STglobdef");
    DBUG_PRINT("ST", ("STglobdef"));

    node *symboltable = INFO_SYMBOL_TABLE(arg_info);
    node *symboltableentry = TBmakeSymboltableentry(STRcpy(GLOBDEF_NAME(arg_node)), GLOBDEF_TYPE(arg_node), 0, 0, arg_node, NULL, NULL);

    STadd(symboltable, symboltableentry);

    DBUG_RETURN(arg_node);
}

node *STfundef(node *arg_node, info *arg_info)
{
    DBUG_ENTER("STfundef");
    DBUG_PRINT("ST", ("STfundef"));

    node *symboltable = INFO_SYMBOL_TABLE(arg_info);

    info *symbolTableInfo = MakeInfo(symboltable);
    SYMBOLTABLE_RETURNTYPE(INFO_SYMBOL_TABLE(symbolTableInfo)) = FUNDEF_TYPE(arg_node);

    node *symboltableentry = TBmakeSymboltableentry(STRcpy(FUNDEF_NAME(arg_node)), FUNDEF_TYPE(arg_node), 0, 0, arg_node, NULL, INFO_SYMBOL_TABLE(symbolTableInfo));

    STadd(symboltable, symboltableentry);

    FUNDEF_PARAMS(arg_node) = TRAVopt(FUNDEF_PARAMS(arg_node), symbolTableInfo);
    FUNDEF_FUNBODY(arg_node) = TRAVopt(FUNDEF_FUNBODY(arg_node), symbolTableInfo);

    FreeInfo(symbolTableInfo);

    DBUG_RETURN(arg_node);
}

node *STparam(node *arg_node, info *arg_info)
{
    DBUG_ENTER("STparam");
    DBUG_PRINT("ST", ("STparam"));

    node *symboltable = INFO_SYMBOL_TABLE(arg_info);
    node *symboltableentry = TBmakeSymboltableentry(STRcpy(PARAM_NAME(arg_node)), PARAM_TYPE(arg_node), 0, 1, arg_node, NULL, NULL);

    STadd(symboltable, symboltableentry);

    PARAM_NEXT(arg_node) = TRAVopt(PARAM_NEXT(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

// node *STfuncall(node *arg_node, info *arg_info)
// {
//     DBUG_ENTER("STfuncall");
//     DBUG_PRINT("ST", ("STfuncall"));


//     DBUG_RETURN(arg_node);
// }

/*
 * Traversal start function
 */
node *STdoProcessSymbolTable(node *syntaxtree)
{
    DBUG_ENTER("STdoProcessSymbolTable");
    DBUG_PRINT("ST", ("STdoProcessSymbolTable"));

    info *info = MakeInfo(NULL);

    TRAVpush(TR_st);
    syntaxtree = TRAVdo(syntaxtree, info);
    TRAVpop();

    STdisplay(INFO_SYMBOL_TABLE(info), 0);

    FreeInfo(info);

    DBUG_RETURN(syntaxtree);
}