/*****************************************************************************
 *
 * Module: opt_sub
 *
 * Prefix: OS
 *
 * Description:
 *
 * This module implements a demo traversal of the abstract syntax tree that 
 * replaces subtractions with identical left and right argument by zeros.
 *
 *****************************************************************************/

#include "count_operators.h"

#include "types.h"
#include "tree_basic.h"
#include "traverse.h"
#include "dbug.h"

#include "memory.h"
#include "free.h"
#include "str.h"
#include "ctinfo.h"
#include "stdio.h"

struct INFO
{
    int mul;
    int sub;
    int add;
    int div;
    int mod;
};

#define COUNT_OPERATORS_MUL(n) ((n)->mul)
#define COUNT_OPERATORS_SUB(n) ((n)->sub)
#define COUNT_OPERATORS_ADD(n) ((n)->add)
#define COUNT_OPERATORS_DIV(n) ((n)->div)
#define COUNT_OPERATORS_MOD(n) ((n)->mod)

/*
 * INFO functions
 */

static info *MakeInfo(void)
{
    info *result;

    DBUG_ENTER("MakeInfo");

    result = (info *)MEMmalloc(sizeof(info));

    COUNT_OPERATORS_MUL(result) = 0;
    COUNT_OPERATORS_SUB(result) = 0;
    COUNT_OPERATORS_ADD(result) = 0;
    COUNT_OPERATORS_DIV(result) = 0;
    COUNT_OPERATORS_MOD(result) = 0;

    DBUG_RETURN(result);
}

static info *FreeInfo(info *info)
{
    DBUG_ENTER("FreeInfo");

    info = MEMfree(info);

    DBUG_RETURN(info);
}

/*
 * Traversal functions
 */

node *CAbinop(node *arg_node, info *arg_info)
{
    DBUG_ENTER("CAbinop");

    /*
       * Extremely important:
       *  we must continue to traverse the abstract syntax tree !!
       */
    BINOP_RIGHT(arg_node) = TRAVdo(BINOP_RIGHT(arg_node), arg_info);
    BINOP_LEFT(arg_node) = TRAVdo(BINOP_LEFT(arg_node), arg_info);

    if (BINOP_OP(arg_node) == BO_mul)
    {
        COUNT_OPERATORS_MUL(arg_info) = COUNT_OPERATORS_MUL(arg_info) + 1;
    }
    else if (BINOP_OP(arg_node) == BO_sub)
    {
        COUNT_OPERATORS_SUB(arg_info) = COUNT_OPERATORS_SUB(arg_info) + 1;
    }
    else if (BINOP_OP(arg_node) == BO_add)
    {
        COUNT_OPERATORS_ADD(arg_info) = COUNT_OPERATORS_ADD(arg_info) + 1;
    }
    else if (BINOP_OP(arg_node) == BO_div)
    {
        COUNT_OPERATORS_DIV(arg_info) = COUNT_OPERATORS_DIV(arg_info) + 1;
    }
    else if (BINOP_OP(arg_node) == BO_mod)
    {
        COUNT_OPERATORS_MOD(arg_info) = COUNT_OPERATORS_MOD(arg_info) + 1;
    }

    DBUG_RETURN(arg_node);
}

node *CAmodule(node *arg_node, info *arg_info)
{
    DBUG_ENTER("CAmodule");

    TRAVdo(MODULE_NEXT(arg_node), arg_info);
    MODULE_MUL(arg_node) = COUNT_OPERATORS_MUL(arg_info);
    MODULE_SUB(arg_node) = COUNT_OPERATORS_SUB(arg_info);
    MODULE_ADD(arg_node) = COUNT_OPERATORS_ADD(arg_info);
    MODULE_DIV(arg_node) = COUNT_OPERATORS_DIV(arg_info);
    MODULE_MOD(arg_node) = COUNT_OPERATORS_MOD(arg_info);

    DBUG_RETURN(arg_node);
}

/*
 * Traversal start function
 */

node *CAdoCount(node *syntaxtree)
{
    DBUG_ENTER("CAdoCount");

    info *arg_info;

    arg_info = MakeInfo();

    TRAVpush(TR_ca);
    syntaxtree = TRAVdo(syntaxtree, arg_info);
    TRAVpop();

    FreeInfo(arg_info);

    DBUG_RETURN(syntaxtree);
}
