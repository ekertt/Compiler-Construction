/*****************************************************************************
 *
 * Module: count_identifiers
 *
 * Prefix: OS
 *
 * Description:
 *
 * This module implements a demo traversal of the abstract syntax tree that 
 * replaces subtractions with identical left and right argument by zeros.
 *
 *****************************************************************************/

#include "count_identifiers.h"

#include "types.h"
#include "tree_basic.h"
#include "traverse.h"
#include "dbug.h"

#include "memory.h"
#include "free.h"
#include "str.h"
#include "lookup_table.h"

struct INFO
{
    lut_t *lookuptable;
};

#define INFO_LUT(n) ((n)->lookuptable)

static info *MakeInfo(void)
{
    info *result;

    DBUG_ENTER("MakeInfo");

    result = MEMmalloc(sizeof(info));
    INFO_LUT(result) = LUTgenerateLut();

    DBUG_RETURN(result);
}

static info *FreeInfo(info *info)
{
    DBUG_ENTER("FreeInfo");

    INFO_LUT(info) = LUTremoveLut(INFO_LUT(info));
    info = MEMfree(info);

    DBUG_RETURN(info);
}

struct count_identifiers
{
    int sum;
    char *name;
};

typedef struct count_identifiers counter;


/*
 * Traversal functions
 */

node *CIvar(node *arg_node, info *arg_info)
{
    DBUG_ENTER("CIvar");

    DBUG_RETURN(arg_node);
}

node *CIvarlet(node *arg_node, info *arg_info)
{
    DBUG_ENTER("CIvarlet");

    DBUG_RETURN(arg_node);
}

/*
 * Traversal start function
 */

node *CIdoCount(node *syntaxtree)
{
    DBUG_ENTER("FLdoOptSub");

    TRAVpush(TR_fl);
    syntaxtree = TRAVdo(syntaxtree, NULL);
    TRAVpop();

    DBUG_RETURN(syntaxtree);
}
