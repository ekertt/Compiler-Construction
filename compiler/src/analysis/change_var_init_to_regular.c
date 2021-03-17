/*****************************************************************************
 *
 * Module: change variable initialisations to regular
 *
 * Prefix: CI
 *
 * Description: Changes all variable iniialisations to regulars
 *
 *****************************************************************************/
#include "change_var_init_to_regular.h"
#include "symbol_table.h"

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
#include "copy.h"

/*
 * INFO structure
 */

struct INFO
{
    node *table;
    node *begin;
    node *end;
};

#define INFO_SYMBOL_TABLE(n) ((n)->table)
#define INFO_BEGIN(n) ((n)->begin)
#define INFO_END(n) ((n)->end)

/*
 * INFO functions
 */

static info *MakeInfo(void)
{
    info *result;

    DBUG_ENTER("MakeInfo");

    result = (info *)MEMmalloc(sizeof(info));

    INFO_SYMBOL_TABLE(result) = NULL;
    INFO_BEGIN(result) = NULL;
    INFO_END(result) = NULL;

    DBUG_RETURN(result);
}

static info *FreeInfo(info *info)
{
    DBUG_ENTER("FreeInfo");

    info = MEMfree(info);

    DBUG_RETURN(info);
}

node *CIprogram(node *arg_node, info *arg_info)
{
    DBUG_ENTER("CIprogram");
    DBUG_PRINT("CI", ("CIprogram"));

    INFO_SYMBOL_TABLE(arg_info) = PROGRAM_SYMBOLTABLE(arg_node);
    PROGRAM_DECLS(arg_node) = TRAVopt(PROGRAM_DECLS(arg_node), arg_info);

    node *statements = INFO_BEGIN(arg_info);

    if (statements == NULL)
    {
        DBUG_RETURN(arg_node);
    }

    node *initFunction = TBmakeFundef(T_void, STRcpy("__init"), TBmakeFunbody(NULL, NULL, statements), NULL);
    FUNDEF_ISEXPORT(initFunction) = 1;

    PROGRAM_DECLS(arg_node) = TBmakeDecls(initFunction, PROGRAM_DECLS(arg_node));

    node *symboltable = INFO_SYMBOL_TABLE(arg_info);

    node *inittable = TBmakeSymboltable(NULL);
    SYMBOLTABLE_PARENT(inittable) = symboltable;

    node *entry = TBmakeSymboltableentry(STRcpy(FUNDEF_NAME(initFunction)), FUNDEF_TYPE(initFunction), 0, 0, arg_node, NULL, inittable);

    STadd(symboltable, entry);

    DBUG_RETURN(arg_node);
}

node *CIglobdef(node *arg_node, info *arg_info)
{
    DBUG_ENTER("CIglobdef");
    DBUG_PRINT("CI", ("CIglobdef"));

    node *expression = GLOBDEF_INIT(arg_node);
    GLOBDEF_INIT(arg_node) = NULL;

    if (expression)
    {
        node *newstatements = TBmakeAssign(TBmakeVarlet(STRcpy(GLOBDEF_NAME(arg_node)), arg_node, NULL), COPYdoCopy(expression));

        FREEdoFreeTree(expression);

        helper(arg_node, arg_info, newstatements, 0);
    }

    DBUG_RETURN(arg_node);
}

node *CIvardecl(node *arg_node, info *arg_info)
{
    DBUG_ENTER("CIvardecl");
    DBUG_PRINT("CI", ("CIvardecl"));

    node *expression = VARDECL_INIT(arg_node);
    VARDECL_INIT(arg_node) = NULL;

    if (expression)
    {
        node *newstatements = TBmakeAssign(TBmakeVarlet(STRcpy(VARDECL_NAME(arg_node)), arg_node, NULL), COPYdoCopy(expression));

        FREEdoFreeTree(expression);

        helper(arg_node, arg_info, newstatements, 1);

        VARDECL_NEXT(arg_node) = TRAVopt(VARDECL_NEXT(arg_node), arg_info);
    }

    DBUG_RETURN(arg_node);
}

void helper(node *arg_node, info *arg_info, node *assign, int type)
{
    if (INFO_BEGIN(arg_info) != NULL)
    {
        node *node = TBmakeStmts(assign, NULL);
        STMTS_NEXT(INFO_END(arg_info)) = node;
        INFO_END(arg_info) = node;
    }
    else
    {
        INFO_BEGIN(arg_info) = TBmakeStmts(assign, NULL);
        INFO_END(arg_info) = INFO_BEGIN(arg_info);
    }
}

node *CIfunbody(node *arg_node, info *arg_info)
{
    DBUG_ENTER("CIfunbody");
    DBUG_PRINT("CI", ("CIfunbody"));

    info *info = MakeInfo();
    FUNBODY_VARDECLS(arg_node) = TRAVopt(FUNBODY_VARDECLS(arg_node), info);

    if (INFO_END(info) != NULL)
    {
        STMTS_NEXT(INFO_END(info)) = FUNBODY_STMTS(arg_node);
        FUNBODY_STMTS(arg_node) = INFO_BEGIN(info);
    }

    FreeInfo(info);
    DBUG_RETURN(arg_node);
}

node *CIdoChangeVariableInitToRegular(node *syntaxtree)
{
    DBUG_ENTER("CIdoChangeVariableInitToRegular");
    DBUG_PRINT("CI", ("CIdoChangeVariableInitToRegular"));

    info *info = MakeInfo();

    TRAVpush(TR_ci);
    syntaxtree = TRAVdo(syntaxtree, info);
    TRAVpop();

    FreeInfo(info);

    DBUG_RETURN(syntaxtree);
}