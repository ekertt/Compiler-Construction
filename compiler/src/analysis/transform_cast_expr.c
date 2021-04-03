/*****************************************************************************
 *
 * Module: Transform cast expression
 *
 * Prefix: TCE
 *
 * Description:
 *
 *****************************************************************************/
#include "transform_cast_expr.h"

#include "type_check.h"
#include "symbol_table.h"

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

struct INFO
{
    type type;
    node *symboltable;
};

#define INFO_TYPE(n) ((n)->type)
#define INFO_SYMBOLTABLE(n) ((n)->symboltable)

static info *MakeInfo(void)
{
    DBUG_ENTER("MakeInfo");
    info *result;
    result = (info *)MEMmalloc(sizeof(info));
    INFO_TYPE(result) = T_unknown;
    INFO_SYMBOLTABLE(result) = NULL;
    DBUG_RETURN(result);
}

static info *FreeInfo(info *info)
{
    DBUG_ENTER("FreeInfo");
    info = MEMfree(info);
    DBUG_RETURN(info);
}

node *TCEnum(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCEnum");
    DBUG_PRINT("TCE", ("TCEnum"));

    INFO_TYPE(arg_info) = T_int;

    DBUG_RETURN(arg_node);
}

node *TCEfloat(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCEfloat");
    DBUG_PRINT("TCE", ("TCEfloat"));

    INFO_TYPE(arg_info) = T_float;

    DBUG_RETURN(arg_node);
}

node *TCEbool(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCEbool");
    DBUG_PRINT("TCE", ("TCEbool"));

    INFO_TYPE(arg_info) = T_bool;

    DBUG_RETURN(arg_node);
}

node *TCEvar(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCEbool");
    DBUG_PRINT("TCE", ("TCEbool"));

    INFO_TYPE(arg_info) = SYMBOLTABLEENTRY_TYPE(STfindInParent(INFO_SYMBOLTABLE(arg_info), VAR_NAME(arg_node)));

    DBUG_RETURN(arg_node);
}

node *TCEprogram(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCEprogram");
    DBUG_PRINT("TCE", ("TCEprogram"));

    INFO_SYMBOLTABLE(arg_info) = PROGRAM_SYMBOLTABLE(arg_node);
    PROGRAM_DECLS(arg_node) = TRAVdo(PROGRAM_DECLS(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *TCEfundef(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCEfundef");
    DBUG_PRINT("TCE", ("TCEfundef"));

    node *symboltable = INFO_SYMBOLTABLE(arg_info);

    INFO_SYMBOLTABLE(arg_info) = SYMBOLTABLEENTRY_TABLE(STfindFundef(symboltable, FUNDEF_NAME(arg_node)));
    FUNDEF_FUNBODY(arg_node) = TRAVopt(FUNDEF_FUNBODY(arg_node), arg_info);
    INFO_SYMBOLTABLE(arg_info) = symboltable;

    DBUG_RETURN(arg_node);
}

node *TCEbinop(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCEbinop");
    DBUG_PRINT("TCE", ("TCEbinop"));

    BINOP_LEFT(arg_node) = TRAVopt(BINOP_LEFT(arg_node), arg_info);
    BINOP_RIGHT(arg_node) = TRAVopt(BINOP_RIGHT(arg_node), arg_info);

    if (BINOP_OP(arg_node) == BO_ne || BINOP_OP(arg_node) == BO_lt || BINOP_OP(arg_node) == BO_le || BINOP_OP(arg_node) == BO_gt || BINOP_OP(arg_node) == BO_ge || BINOP_OP(arg_node) == BO_eq)
    {
        INFO_TYPE(arg_info) = T_bool;
    }

    DBUG_RETURN(arg_node);
}

node *TCEcast(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCEcast");
    DBUG_PRINT("TCE", ("TCEcast"));

    CAST_EXPR(arg_node) = TRAVdo(CAST_EXPR(arg_node), arg_info);

    node *expression = COPYdoCopy(CAST_EXPR(arg_node));
    type cast_type = CAST_TYPE(arg_node);

    if (cast_type == T_bool)
    {
        FREEdoFreeTree(arg_node);

        node *numFloat;

        if (INFO_TYPE(arg_info) == T_int)
        {
            numFloat = TBmakeNum(0);
        }
        else
        {
            numFloat = TBmakeFloat(0.0);
        }

        arg_node = TBmakeBinop(BO_ne, expression, numFloat);
    }
    else if (INFO_TYPE(arg_info) == T_bool)
    {
        FREEdoFreeTree(arg_node);

        if (cast_type == T_int)
        {
            arg_node = TBmakeTernary(expression, TBmakeNum(1), TBmakeNum(0));
        }

        if (cast_type == T_float)
        {
            arg_node = TBmakeTernary(expression, TBmakeFloat(1.0), TBmakeFloat(0.0));
        }
    }
    else
    {
        FREEdoFreeTree(expression);
    }

    DBUG_RETURN(arg_node);
}

node *TCEdoTransform(node *syntaxtree)
{
    DBUG_ENTER("TCEdoTransform");
    DBUG_PRINT("TCE", ("TCEdoTransform"));

    info *info = MakeInfo();

    TRAVpush(TR_tce);
    syntaxtree = TRAVdo(syntaxtree, info);
    TRAVpop();

    FreeInfo(info);

    DBUG_RETURN(syntaxtree);
}