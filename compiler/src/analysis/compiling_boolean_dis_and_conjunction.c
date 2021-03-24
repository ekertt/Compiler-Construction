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

#include "types.h"
#include "tree_basic.h"
#include "traverse.h"
#include "dbug.h"
#include "print.h"
#include "memory.h"
#include "free.h"
#include "str.h"
#include "ctinfo.h"
#include "copy.h"

node *CBbinop(node *arg_node, info *arg_info)
{
    DBUG_ENTER("CBbinop");
    DBUG_PRINT("CB", ("CBbinop"));

    if (BO_and != BINOP_OP(arg_node) && BO_or != BINOP_OP(arg_node))
    {
        DBUG_RETURN(arg_node);
    }

    node *leftSide = NULL;

    BINOP_LEFT(arg_node) = TRAVopt(BINOP_LEFT(arg_node), arg_info);
    BINOP_RIGHT(arg_node) = TRAVopt(BINOP_RIGHT(arg_node), arg_info);

    if (BO_and == BINOP_OP(arg_node))
    {
        leftSide = TBmakeTernary(COPYdoCopy(BINOP_LEFT(arg_node)), COPYdoCopy(BINOP_RIGHT(arg_node)), TBmakeBool(0));
    }
    else if (BO_or == BINOP_OP(arg_node))
    {
        leftSide = TBmakeTernary(COPYdoCopy(BINOP_LEFT(arg_node)), TBmakeBool(1), COPYdoCopy(BINOP_RIGHT(arg_node)));
    }

    FREEdoFreeTree(arg_node);

    arg_node = leftSide;
    DBUG_RETURN(arg_node);
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