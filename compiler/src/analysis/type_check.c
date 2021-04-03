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
/*
 * INFO structure
 */

struct INFO
{
    node *symboltable;
    type type;
    size_t returntype;
};

/*
 * INFO macros
 */

#define INFO_SYMBOL_TABLE(n) ((n)->symboltable)
#define INFO_TYPE(n) ((n)->type)
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

    INFO_SYMBOL_TABLE(arg_info) = SYMBOLTABLEENTRY_TABLE(STfindFundef(symboltable, FUNDEF_NAME(arg_node)));
    FUNDEF_FUNBODY(arg_node) = TRAVopt(FUNDEF_FUNBODY(arg_node), arg_info);

    if (INFO_RETURN(arg_info) == 0 && FUNDEF_ISEXTERN(arg_node) < 1 && FUNDEF_TYPE(arg_node) != T_void)
    {
        CTIerrorLine(NODE_LINE(arg_node), "No return type expected");
    }

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

    if (INFO_TYPE(arg_info) != SYMBOLTABLE_RETURNTYPE(symboltable))
    {
            CTIerrorLine(NODE_LINE(arg_node), "Invalid return statement from %s to %s", SYMBOLTABLE_RETURNTYPE(symboltable), INFO_TYPE(arg_info));
    }

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

    if (leftype != righttype)
    {
        CTIerrorLine(NODE_LINE(arg_node), "Unequal type error\n");
    }

    binop op = BINOP_OP(arg_node);

    if ((op == BO_sub || op == BO_div || op == BO_lt || op == BO_le || op == BO_gt || op == BO_ge) && righttype == T_bool)
    {
        CTIerror("TypeError\n");
    }

    if (op == BO_mod && righttype != T_int)
    {
        CTIerror("TypeError\n");
    }

    DBUG_RETURN(arg_node);
}

node *TCfuncall(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCfuncall");
    DBUG_PRINT("TC", ("TCfuncall"));

    node *symboltableentry = STdeepFindFundef(INFO_SYMBOL_TABLE(arg_info), FUNCALL_NAME(arg_node));

    FUNCALL_ARGS(arg_node) = TRAVopt(FUNCALL_ARGS(arg_node), arg_info);
    INFO_TYPE(arg_info) = SYMBOLTABLEENTRY_TYPE(symboltableentry);

    DBUG_RETURN(arg_node);
}

node *TCexprs(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCexprs");
    DBUG_PRINT("TC", ("TCexprs"));

    EXPRS_EXPR(arg_node) = TRAVdo(EXPRS_EXPR(arg_node), arg_info);
    EXPRS_NEXT(arg_node) = TRAVopt(EXPRS_NEXT(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *TCvar(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCvar");
    DBUG_PRINT("TC", ("TCvar"));

    node *node = STfindInParent(INFO_SYMBOL_TABLE(arg_info), VAR_NAME(arg_node));
    INFO_TYPE(arg_info) = SYMBOLTABLEENTRY_TYPE(node);

    DBUG_RETURN(arg_node);
}

node *TCcast(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCcast");
    DBUG_PRINT("TC", ("TCcast"));

    CAST_EXPR(arg_node) = TRAVdo(CAST_EXPR(arg_node), arg_info);

    if (INFO_TYPE(arg_info) == T_void)
    {
        CTIerrorLine(NODE_LINE(arg_node), "Cast type error\n");
    }

    INFO_TYPE(arg_info) = CAST_TYPE(arg_node);

    DBUG_RETURN(arg_node);
}

node *TCassign(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCassign");
    DBUG_PRINT("TC", ("TCassign"));

    type type = INFO_TYPE(arg_info);
    node *varlet = ASSIGN_LET(arg_node);
    node *node = STfindInParent(INFO_SYMBOL_TABLE(arg_info), VARLET_NAME(varlet));

    INFO_TYPE(arg_info) = SYMBOLTABLEENTRY_TYPE(node);
    ASSIGN_EXPR(arg_node) = TRAVdo(ASSIGN_EXPR(arg_node), arg_info);
    INFO_TYPE(arg_info) = type;

    DBUG_RETURN(arg_node);
}

node *TCmonop(node *arg_node, info *arg_info)
{
    DBUG_ENTER("TCmonop");

    monop op = MONOP_OP(arg_node);
    MONOP_OPERAND(arg_node) = TRAVdo(MONOP_OPERAND(arg_node), arg_info);
    type type = INFO_TYPE(arg_info);

    if ((op == MO_neg && type != T_bool) || (op == MO_minus && type == T_bool))
    {
        CTIerror("TypeError: Assigning %u to %u at line: %d", op, type, NODE_LINE(arg_node));
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