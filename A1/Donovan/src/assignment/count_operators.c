/*****************************************************************************
 *
 * Module: count_operators
 *
 * Prefix: CO
 *
 * Description:
 *
 * This module implements a traversal that counts the operators in a file
 *
 *****************************************************************************/

#include "count_operators.h"

#include "types.h"
#include "tree_basic.h"
#include "traverse.h"
#include "dbug.h"

#include "memory.h"
#include "ctinfo.h"
#include "free.h"
#include "str.h"
#include "stdio.h"

/*
 * INFO structure
 */

struct INFO 
{
    int add;
    int sub;
    int div;
    int mod;
    int mul;
};

#define INFO_ADDITION(n) ((n)->add)
#define INFO_SUBTRACTION(n) ((n)->sub)
#define INFO_DIVISOR(n) ((n)->div)
#define INFO_MODULO(n) ((n)->mod)
#define INFO_MULTIPLIER(n) ((n)->mul)

/*
 * INFO functions
 */

static info *MakeInfo(void)
{
    info *result;

    DBUG_ENTER("MakeInfo");

    result = (info *) MEMmalloc(sizeof(info));

    INFO_ADDITION(result) = 0;
    INFO_SUBTRACTION(result) = 0;
    INFO_DIVISOR(result) = 0;
    INFO_MODULO(result) = 0;
    INFO_MULTIPLIER(result) = 0;

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

node *CObinop(node *arg_node, info *arg_info)
{
    DBUG_ENTER("CObinop");

    // Count the occurrences
    if (BINOP_OP(arg_node) == BO_add) {
        INFO_ADDITION(arg_info) += 1;
    };

    if (BINOP_OP(arg_node) == BO_sub) {
        INFO_SUBTRACTION(arg_info) += 1;
    };

    if (BINOP_OP(arg_node) == BO_div) {
        INFO_DIVISOR(arg_info) += 1;
    };

    if (BINOP_OP(arg_node) == BO_mod) {
        INFO_MODULO(arg_info) += 1;
    }; 

    if (BINOP_OP(arg_node) == BO_mul) {
        INFO_MULTIPLIER(arg_info) += 1;
    };

    /*
     * Continue to traverse the syntax tree
     */
    BINOP_LEFT(arg_node) = TRAVdo(BINOP_LEFT(arg_node), arg_info);
    BINOP_RIGHT(arg_node) = TRAVdo(BINOP_RIGHT(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *COmodule(node *arg_node, info *arg_info)
{
    DBUG_ENTER("COmodule");

    TRAVdo(MODULE_NEXT(arg_node), arg_info);

    MODULE_ADD(arg_node) = INFO_ADDITION(arg_info);
    MODULE_SUB(arg_node) = INFO_SUBTRACTION(arg_info);
    MODULE_MOD(arg_node) = INFO_MODULO(arg_info);
    MODULE_DIV(arg_node) = INFO_DIVISOR(arg_info);
    MODULE_MUL(arg_node) = INFO_MULTIPLIER(arg_info);

    DBUG_RETURN(arg_node);
}

/*
 * Start the traversal function
 */

node *COdoCountOperators(node *syntaxtree)
{
    DBUG_ENTER("COdoCountOperators");

    info *arg_info;

    arg_info = MakeInfo();

    TRAVpush(TR_co);
    syntaxtree = TRAVdo(syntaxtree, arg_info);
    TRAVpop();

    CTInote( "Amount of additions: %d\n", INFO_ADDITION( arg_info));
    CTInote( "Amount of substitutions: %d\n", INFO_SUBTRACTION( arg_info));
    CTInote( "Amount of divisions: %d\n", INFO_DIVISOR( arg_info));
    CTInote( "Amount of modulo: %d\n", INFO_MODULO( arg_info));
    CTInote( "Amount of multiplications: %d\n", INFO_MULTIPLIER( arg_info));

    arg_info = FreeInfo(arg_info);

    DBUG_RETURN(syntaxtree);
}
