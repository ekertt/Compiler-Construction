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

/*
 * Traversal functions
 */

node *CAbinop(node *arg_node, info *arg_info)
{
    DBUG_ENTER("FLbinop");

    DBUG_RETURN(arg_node);
}

/*
 * Traversal start function
 */

node *CAdoCount(node *syntaxtree)
{
    DBUG_ENTER("FLdoOptSub");

    TRAVpush(TR_fl);
    syntaxtree = TRAVdo(syntaxtree, NULL);
    TRAVpop();

    DBUG_RETURN(syntaxtree);
}
