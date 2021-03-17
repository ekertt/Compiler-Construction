/*****************************************************************************
 *
 * Module: Type checking
 *
 * Prefix: TC
 *
 * Description: This does the type checking of vars and functions
 *
 *****************************************************************************/
#include "type_check.h"
#include "symbol_table.h"

#include "types.h"
#include "tree_basic.h"
#include "traverse.h"
#include "dbug.h"
#include "print.h"
#include "memory.h"
#include "free.h"
#include "str.h"
#include "ctinfo.h"
/*
 * INFO structure
 */

struct INFO
{
    node *symboltable;
    type type;
    node *fundef;
    size_t returntype;
};

/*
 * INFO macros
 */

#define INFO_SYMBOL_TABLE(n) ((n)->symboltable)
#define INFO_TYPE(n) ((n)->type)
#define INFO_FUN_DEF(n) ((n)->fundef)
#define INFO_RETURN(n) ((n)->returntype)

/*
 * INFO functions
 */

static info *MakeInfo()
{
    info *result;

    DBUG_ENTER("MakeInfo");

    result = (info *)MEMmalloc(sizeof(info));
    INFO_SYMBOL_TABLE(result) = NULL;
    INFO_TYPE(result) = T_unknown;
    INFO_FUN_DEF(result) = NULL;
    INFO_RETURN(result) = 0;

    DBUG_RETURN(result);
}

static info *FreeInfo(info *info)
{
    DBUG_ENTER("FreeInfo");

    info = MEMfree(info);

    DBUG_RETURN(info);
}

node *TCprogram(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCprogram");
    DBUG_PRINT("TC", ("TCprogram"));

    // STdisplay(PROGRAM_SYMBOLTABLE(arg_node), 0);
    INFO_SYMBOL_TABLE(arg_info) = PROGRAM_SYMBOLTABLE(arg_node);

    PROGRAM_DECLS(arg_node) = TRAVopt(PROGRAM_DECLS(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *TCnum(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCnum");
    DBUG_PRINT("TC", ("TCnum"));

    INFO_TYPE(arg_info) = T_int;

    DBUG_RETURN(arg_node);
}

node *TCbool(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCbool");
    DBUG_PRINT("TC", ("TCbool"));

    INFO_TYPE(arg_info) = T_bool;

    DBUG_RETURN(arg_node);
}

node *TCfloat(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCfloat");
    DBUG_PRINT("TC", ("TCfloat"));

    INFO_TYPE(arg_info) = T_float;

    DBUG_RETURN(arg_node);
}

node *TCfundef(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCfundef");
    DBUG_PRINT("TC", ("TCfundef"));

    node *symboltable = INFO_SYMBOL_TABLE(arg_info);
    node *symboltableentry = STfindFundef(symboltable, FUNDEF_NAME(arg_node));

    INFO_SYMBOL_TABLE(arg_info) = SYMBOLTABLEENTRY_TABLE(symboltableentry);
    FUNDEF_FUNBODY(arg_node) = TRAVopt(FUNDEF_FUNBODY(arg_node), arg_info);

    INFO_RETURN(arg_info) = 0;
    INFO_SYMBOL_TABLE(arg_info) = symboltable;

    DBUG_RETURN(arg_node);
}

node *TCreturn(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCreturn");
    DBUG_PRINT("TC", ("TCreturn"));

    INFO_RETURN(arg_info) += 1;

    node *symboltable = INFO_SYMBOL_TABLE(arg_info);

    if (RETURN_EXPR(arg_node) == NULL && SYMBOLTABLE_RETURNTYPE(symboltable) == T_void)
    {
        DBUG_RETURN(arg_node);
    }

    RETURN_EXPR(arg_node) = TRAVopt(RETURN_EXPR(arg_node), arg_info);

    if (INFO_TYPE(arg_info) == SYMBOLTABLE_RETURNTYPE(symboltable))
    {
        DBUG_RETURN(arg_node);
    }

    CTIerrorLine(NODE_LINE(arg_node), "Invalid from %s to %s", SYMBOLTABLE_RETURNTYPE(symboltable), INFO_TYPE(arg_info));
    DBUG_RETURN(arg_node);
}

node *TCexprstmt(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCexprstmt");
    DBUG_PRINT("TC", ("TCexprstmt"));

    EXPRSTMT_EXPR(arg_node) = TRAVopt(EXPRSTMT_EXPR(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *TCbinop(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCbinop");
    DBUG_PRINT("TC", ("TCbinop"));

    BINOP_LEFT(arg_node) = TRAVopt(BINOP_LEFT(arg_node), arg_info);

    type leftype = INFO_TYPE(arg_info);

    BINOP_RIGHT(arg_node) = TRAVopt(BINOP_RIGHT(arg_node), arg_info);

    type righttype = INFO_TYPE(arg_info);

    switch (BINOP_OP(arg_node))
    {
    case BO_add:
    case BO_sub:
    case BO_mul:
    case BO_div:

        if (leftype != righttype)
            CTIerrorLine(NODE_LINE(arg_node), "invalid conversion from \n");

        break;
    case BO_lt:
    case BO_le:
    case BO_gt:
    case BO_ge:
    case BO_eq:
    case BO_ne:

        if (leftype != righttype)
            CTIerrorLine(NODE_LINE(arg_node), "invalid conversion from \n");

        INFO_TYPE(arg_info) = T_bool;

        break;
    case BO_and:
    case BO_or:

        if (righttype != T_bool)
            CTIerrorLine(NODE_LINE(arg_node), "invalid conversion from\n");

        break;
    case BO_mod:
        if (righttype != T_int)
            CTIerrorLine(NODE_LINE(arg_node), "Modulo operator only supports interger types\n");

        break;

    case BO_unknown:
        break;
    }

    DBUG_RETURN(arg_node);
}

node *TCdoTypeCheck(node *syntaxtree)
{
    DBUG_ENTER("TCdoTypeCheck");

    info *arg_info = MakeInfo();

    TRAVpush(TR_tc);
    syntaxtree = TRAVdo(syntaxtree, arg_info);
    TRAVpop();

    arg_info = FreeInfo(arg_info);

    DBUG_RETURN(syntaxtree);
}