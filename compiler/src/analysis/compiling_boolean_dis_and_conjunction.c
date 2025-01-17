/*****************************************************************************
 *
 * Module: Boolean conjunction
 *
 * Prefix: BC
 *
 * Description:
 *
 *****************************************************************************/
#include "compiling_boolean_dis_and_conjunction.h"

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

node *CBbinop(node *arg_node, info *arg_info)
{
    DBUG_ENTER("CBbinop");
    DBUG_PRINT("CB", ("CBbinop"));

    if (BO_and != BINOP_OP(arg_node) && BO_or != BINOP_OP(arg_node))
    {
        DBUG_RETURN(arg_node);
    }

    BINOP_LEFT(arg_node) = TRAVopt(BINOP_LEFT(arg_node), arg_info);
    BINOP_RIGHT(arg_node) = TRAVopt(BINOP_RIGHT(arg_node), arg_info);

    node *leftSide = NULL;

    if (BO_and == BINOP_OP(arg_node))
    {
        leftSide = TBmakeTernary(COPYdoCopy(BINOP_LEFT(arg_node)), COPYdoCopy(BINOP_RIGHT(arg_node)), TBmakeBool(0));
    }

    if (BO_or == BINOP_OP(arg_node))
    {
        leftSide = TBmakeTernary(COPYdoCopy(BINOP_LEFT(arg_node)), TBmakeBool(1), COPYdoCopy(BINOP_RIGHT(arg_node)));
    }

    FREEdoFreeTree(arg_node);

    DBUG_RETURN(leftSide);
}

node *CBdoCompileBoolean(node *syntaxtree)
{
    DBUG_ENTER("CBdoCompileBoolean");
    DBUG_PRINT("CB", ("CBdoCompileBoolean"));

    TRAVpush(TR_cb);
    syntaxtree = TRAVdo(syntaxtree, NULL);
    TRAVpop();

    DBUG_RETURN(syntaxtree);
}