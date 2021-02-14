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

#include "count_identifiers.h"

#include "types.h"
#include "tree_basic.h"
#include "traverse.h"
#include "dbug.h"

#include "memory.h"
#include "ctinfo.h"
#include "free.h"
#include "str.h"
#include "stdio.h"
#include "lookup_table.h"

/*
 * INFO structure
 */

struct INFO
{
    lut_t *lut;
};

#define INFO_LUT(n) ((n)->lut)

/*
 * INFO functions
 */

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

/*
 * COUNTERIDENTIFIER structure
 */

struct COUNTERIDENTIFIER
{
    char *identifier;
    int value;
};

#define ID_ID(n) ((n)->identifier)
#define ID_VAL(n) ((n)->value)

typedef struct COUNTERIDENTIFIER counterid;

/*
 * COUNTERIDENTIFIER functions
 */

static counterid *MakeIdCounter(void)
{

    DBUG_ENTER("MakeInfo");

    counterid *result = (counterid *)MEMmalloc(sizeof(counterid));
    ID_ID(result) = NULL;
    ID_VAL(result) = 0;

    DBUG_RETURN(result);
}

/*
 * Traversal functions
 */

static void *mapAndPrint(void *item)
{
    counterid *identifierCounter = (counterid *)item;
    CTInote("Amount of %s: %d\n", identifierCounter->identifier, identifierCounter->value);
    return item;
}

node *CIvarlet(node *arg_node, info *arg_info)
{
    DBUG_ENTER("CIvarlet");

    lut_t *lut = INFO_LUT(arg_info);
    void **valueAddress = LUTsearchInLutS(lut, VARLET_NAME(arg_node));

    char *identifier = VARLET_NAME(arg_node);

    if (valueAddress == NULL)
    {
        counterid *identifierCounter = MakeIdCounter();
        ID_ID(identifierCounter) = STRcpy(identifier);
        ID_VAL(identifierCounter) = 1;

        LUTinsertIntoLutS(lut, identifier, identifierCounter);
    }
    else
    {
        counterid *identifierCounter = (counterid *)(* valueAddress);
        ID_VAL(identifierCounter) += 1;

        void *overwrite_item;
        LUTupdateLutS(lut, identifier, identifierCounter, &overwrite_item);
    }

    DBUG_RETURN(arg_node);
}

node *CIvar(node *arg_node, info *arg_info)
{
    DBUG_ENTER("CIvar");

    lut_t *lut = INFO_LUT(arg_info);
    void **valueAddress = LUTsearchInLutS(lut, VAR_NAME(arg_node));

    char *identifier = VAR_NAME(arg_node);

    if (valueAddress == NULL)
    {
        counterid *identifierCounter = MakeIdCounter();
        ID_ID(identifierCounter) = STRcpy(identifier);
        ID_VAL(identifierCounter) = 1;

        LUTinsertIntoLutS(lut, identifier, identifierCounter);
    }
    else
    {
        counterid *identifierCounter = (counterid *)(* valueAddress);
        ID_VAL(identifierCounter) += 1;

        void *overwrite_item;
        LUTupdateLutS(lut, identifier, identifierCounter, &overwrite_item);
    }

    DBUG_RETURN(arg_node);
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

    lut_t *lut = INFO_LUT(arg_info);
    LUTmapLutS(lut, mapAndPrint);

    TRAVpop();

    DBUG_RETURN(syntaxtree);

    arg_info = FreeInfo(arg_info);
}
