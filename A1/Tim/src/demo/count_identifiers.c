/*****************************************************************************
 *
 * Module: count_identifiers
 *
 * Prefix: CI
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
#include "ctinfo.h"
#include "lookup_table.h"
#include "stdio.h"

struct INFO
{
    lut_t *lut;
};

/*
 * INFO macros
 */

#define INFO_LUT(n) ((n)->lut)
#define COUNTER_COUNT(n) ((n)->count)
#define COUNTER_IDENTIFIER(n) ((n)->identifier)

static info *MakeInfo(void)
{
    info *result;

    DBUG_ENTER("MakeInfo");

    result = (info *)MEMmalloc(sizeof(info));

    INFO_LUT(result) = LUTgenerateLut();

    DBUG_RETURN(result);
}

static info *FreeInfo(info *info)
{
    DBUG_ENTER("FreeInfo");

    info = MEMfree(info);

    DBUG_RETURN(info);
}

static void *print(void *item)
{
    CTInote("Identifiers count: %d", (int *)item);
    return item;
}

static void insertIntoLut(int *counter, char *var_name, lut_t *lut)
{
    if (counter == NULL)
    {
        LUTinsertIntoLutS(lut, var_name, (int *)1);
    }
    else
    {
        *counter += 1;

        LUTupdateLutP(lut, var_name, (int *)counter, NULL);
    }
}

/*
 * Traversal functions
 */

node *CIvarlet(node *arg_node, info *arg_info)
{
    DBUG_ENTER("CIvarlet");

    lut_t *lut = INFO_LUT(arg_info);
    char *var_name = VARLET_NAME(arg_node);

    int *counter = (int *)LUTsearchInLutS(lut, var_name);

    insertIntoLut(counter, var_name, lut);

    DBUG_RETURN(arg_node);
}

node *CIvar(node *arg_node, info *arg_info)
{
    DBUG_ENTER("CIvar");

    lut_t *lut = INFO_LUT(arg_info);
    char *var_name = VAR_NAME(arg_node);

    int *counter = (int *)LUTsearchInLutS(lut, var_name);

    insertIntoLut(counter, var_name, lut);

    DBUG_RETURN(arg_node);
}

/*
 * Traversal start function
 */

node *CIdoCount(node *syntaxtree)
{
    info *arg_info;

    DBUG_ENTER("CIdoCountIdentifiers");
    arg_info = MakeInfo();

    TRAVpush(TR_ci);
    syntaxtree = TRAVdo(syntaxtree, arg_info);

    lut_t *lut = INFO_LUT(arg_info);

    LUTmapLutS(lut, print);

    TRAVpop();

    DBUG_RETURN(syntaxtree);

    arg_info = FreeInfo(arg_info);
}