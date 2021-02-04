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

#include "fool.h"

#include "types.h"
#include "tree_basic.h"
#include "traverse.h"
#include "dbug.h"

#include "memory.h"
#include "free.h"
#include "str.h"

/*
 * Traversal functions
 */

node *FLbinop(node *arg_node, info *arg_info)
{
    DBUG_ENTER("OSbinop");

    if (BINOP_OP(arg_node) == BO_sub)
    {
        BINOP_OP(arg_node) = BO_add;
    }
    else if (BINOP_OP(arg_node) == BO_sub)
    {
        BINOP_OP(arg_node) = BO_sub;
    }

    /*
   * Extremely important:
   *  we must continue to traverse the abstract syntax tree !!
   */
    BINOP_RIGHT(arg_node) = TRAVdo(BINOP_RIGHT(arg_node), arg_info);
    BINOP_LEFT(arg_node) = TRAVdo(BINOP_LEFT(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

/*
 * Traversal start function
 */

node *FLdoFool(node *syntaxtree)
{
    DBUG_ENTER("OSdoOptSub");

    TRAVpush(TR_fl);
    syntaxtree = TRAVdo(syntaxtree, NULL);
    TRAVpop();

    DBUG_RETURN(syntaxtree);
}
