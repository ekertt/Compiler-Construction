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

#include "copy.h"
#include "ctinfo.h"
#include "dbug.h"
#include "free.h"
#include "print.h"
#include "memory.h"
#include "str.h"
#include "string.h"
#include "types.h"
#include "tree_basic.h"
#include "traverse.h"

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

    if (INFO_BEGIN(arg_info))
    {
        node *initFunction = TBmakeFundef(T_void, STRcpy("__init"), TBmakeFunbody(NULL, NULL, INFO_BEGIN(arg_info)), NULL);
        node *symboltableInit = TBmakeSymboltable(NULL);

        PROGRAM_DECLS(arg_node) = TBmakeDecls(initFunction, PROGRAM_DECLS(arg_node));

        SYMBOLTABLE_PARENT(symboltableInit) = INFO_SYMBOL_TABLE(arg_info);

        FUNDEF_ISEXPORT(initFunction) = 1;

        STadd(INFO_SYMBOL_TABLE(arg_info), TBmakeSymboltableentry(STRcpy(FUNDEF_NAME(initFunction)), FUNDEF_TYPE(initFunction), 0, 0, arg_node, NULL, symboltableInit));
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

    info *infoFunBody = MakeInfo();
    FUNBODY_VARDECLS(arg_node) = TRAVopt(FUNBODY_VARDECLS(arg_node), infoFunBody);

    if (INFO_END(infoFunBody) == NULL)
    {
        FreeInfo(infoFunBody);

        DBUG_RETURN(arg_node);
    }
    else
    {
        STMTS_NEXT(INFO_END(infoFunBody)) = FUNBODY_STMTS(arg_node);
        FUNBODY_STMTS(arg_node) = INFO_BEGIN(infoFunBody);

        FreeInfo(infoFunBody);

        DBUG_RETURN(arg_node);
    }
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