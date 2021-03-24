/*****************************************************************************
 *
 * Module: Boolean conjunction
 *
 * Prefix: BC
 *
 * Description:
 *
 *****************************************************************************/
#include "transform_cast_expr.h"

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

node *TCEprogram(node *arg_node, info *arg_info)
{
    DBUG_ENTER("CBbinop");
    DBUG_PRINT("CB", ("CBbinop"));

    DBUG_RETURN(arg_node);
}

node *TCEdoTransform(node *syntaxtree)
{
    DBUG_ENTER("CBdoCompileBoolean");
    DBUG_PRINT("CB", ("CBdoCompileBoolean"));

    TRAVpush(TR_tce);
    syntaxtree = TRAVdo(syntaxtree, NULL);
    TRAVpop();

    DBUG_RETURN(syntaxtree);
}