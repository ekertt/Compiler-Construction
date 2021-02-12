/*****************************************************************************
 *
 * Module: count_identifiers
 *
 * Prefix: CI
 *
 * Description:
 *
 * This module implements a traversal that counts the identifiers in a file
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
    int var;
    int varLet;
};

#define INFO_VAR(n) ((n)->var)
#define INFO_VARLET(n) ((n)->varLet)

/*
 * INFO functions
 */

static info *MakeInfo(void)
{
    info *result;

    DBUG_ENTER("MakeInfo");

    result = (info *) MEMmalloc(sizeof(info));

    INFO_VAR(result) = 0;
    INFO_VARLET(result) = 0;

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

node *CIvarlet(node *arg_node, info *arg_info)
{
    DBUG_ENTER("CIvarlet");


    /*
     * Continue to traverse the syntax tree
     */
    //BINOP_LEFT(arg_node) = TRAVdo(BINOP_LEFT(arg_node), arg_info);
    //BINOP_RIGHT(arg_node) = TRAVdo(BINOP_RIGHT(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *CIvar( node *arg_node, info *arg_info)
{
    //char *name;

    DBUG_ENTER("CIvar");

    /*
     * Continue to traverse the syntax tree
     */
    //BINOP_LEFT(arg_node) = TRAVdo(BINOP_LEFT(arg_node), arg_info);
    //BINOP_RIGHT(arg_node) = TRAVdo(BINOP_RIGHT(arg_node), arg_info);

    DBUG_RETURN( arg_node);
}

/*
 * Start the traversal function
 */

node *CIdoCountIdentifiers(node *syntaxtree)
{
    DBUG_ENTER("CIdoCountIdentifiers");

    info *arg_info;

    arg_info = MakeInfo();

    TRAVpush(TR_ci);
    syntaxtree = TRAVdo(syntaxtree, arg_info);
    TRAVpop();

    arg_info = FreeInfo(arg_info);

    DBUG_RETURN(syntaxtree);
}
