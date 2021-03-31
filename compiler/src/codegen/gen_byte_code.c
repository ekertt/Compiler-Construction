#include "linked_list.h"
#include "symbol_table.h"
#include "gen_byte_code.h"

#include "types.h"
#include "tree_basic.h"
#include "traverse.h"
#include "dbug.h"

#include "ctinfo.h"
#include <stdio.h>
#include "memory.h"
#include "free.h"
#include "str.h"
#include "print.h"
#include <unistd.h>
#include "globals.h"

/*
 * INFO structure
 */
struct INFO
{
    FILE *file;
    node *symbol_table;
    node *symbol_table_entry;

    int counter;
    int branch_count;
    int type;

    linkedlist *global;
    linkedlist *constant;
    linkedlist *import;
    linkedlist *export;
};

#define INFO_FILE(n) ((n)->file)
#define INFO_SYMBOL_TABLE(n) ((n)->symbol_table)
#define INFO_SYMBOL_TABLE_ENTRY(n) ((n)->symbol_table_entry)

#define INFO_COUNTER(n) ((n)->counter)
#define INFO_BRANCH_COUNT(n) ((n)->branch_count)
#define INFO_TYPE(n) ((n)->type)

#define INFO_GLOBAL(n) ((n)->global)
#define INFO_CONSTANT(n) ((n)->constant)
#define INFO_IMPORT(n) ((n)->import)
#define INFO_EXPORT(n) ((n)->export)

/*
 * INFO functions
 */

static info *MakeInfo()
{
    info *result;

    DBUG_ENTER("MakeInfo");

    result = (info *)MEMmalloc(sizeof(info));
    INFO_FILE(result) = NULL;
    INFO_SYMBOL_TABLE(result) = NULL;
    INFO_SYMBOL_TABLE_ENTRY(result) = NULL;

    INFO_GLOBAL(result) = NULL;
    INFO_CONSTANT(result) = NULL;
    INFO_IMPORT(result) = NULL;
    INFO_EXPORT(result) = NULL;

    INFO_COUNTER(result) = 0;
    INFO_BRANCH_COUNT(result) = 0;
    INFO_TYPE(result) = T_unknown;

    DBUG_RETURN(result);
}

static info *FreeInfo(info *info)
{
    DBUG_ENTER("FreeInfo");

    dipsose(INFO_GLOBAL(info));
    dipsose(INFO_CONSTANT(info));
    dipsose(INFO_IMPORT(info));
    dipsose(INFO_EXPORT(info));

    info = MEMfree(info);

    DBUG_RETURN(info);
}

char *generateBranch(const char *type, info *info)
{
    char *branch = STRcatn(3, STRitoa(INFO_BRANCH_COUNT(info)), "_", type);
    INFO_BRANCH_COUNT(info)
    ++;

    return branch;
}

void addToConstant(info *arg_info, char *value)
{
    if (INFO_CONSTANT(arg_info))
    {
        INFO_COUNTER(arg_info) += 1;
        add(INFO_CONSTANT(arg_info), value, INFO_COUNTER(arg_info));
    }
    else
    {
        INFO_COUNTER(arg_info) += 1;
        INFO_CONSTANT(arg_info) = push(value, INFO_COUNTER(arg_info), NULL);
    }
}

void writeGlobals(info *arg_info)
{
    linkedlist *global = INFO_GLOBAL(arg_info);
    linkedlist *constant = INFO_CONSTANT(arg_info);
    linkedlist *export = INFO_EXPORT(arg_info);
    linkedlist *import = INFO_IMPORT(arg_info);
    FILE *file = INFO_FILE(arg_info);

    while (global)
    {
        fprintf(file, ".global %s\n", global->val);
        global = global->next;
    }

    while (constant)
    {
        fprintf(file, ".const %s\n", constant->val);
        constant = constant->next;
    }

    while (export)
    {
        fprintf(file, ".export%s\n", export->val);
        export = export->next;
    }

    while (import)
    {
        fprintf(file, ".import%s\n", import->val);
        import = import->next;
    }
}

node *GBCprogram(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCprogram");
    DBUG_PRINT("GBC", ("GBCprogram"));

    INFO_SYMBOL_TABLE(arg_info) = PROGRAM_SYMBOLTABLE(arg_node);
    TRAVdo(PROGRAM_DECLS(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *GBCsymboltable(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCsymboltable");
    DBUG_PRINT("GBC", ("GBCsymboltable"));

    // empty: no code gen

    DBUG_RETURN(arg_node);
}

node *GBCsymboltableentry(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCsymboltableentry");
    DBUG_PRINT("GBC", ("GBCsymboltableentry"));

    // empty: no code gen

    DBUG_RETURN(arg_node);
}

node *GBCids(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCids");
    DBUG_PRINT("GBC", ("GBCids"));

    TRAVopt(IDS_NEXT(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *GBCdecls(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCdecls");
    DBUG_PRINT("GBC", ("GBCdecls"));

    TRAVdo(DECLS_DECL(arg_node), arg_info);
    TRAVopt(DECLS_NEXT(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *GBCexprs(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCexprs");
    DBUG_PRINT("GBC", ("GBCexprs"));

    TRAVdo(EXPRS_EXPR(arg_node), arg_info);
    TRAVopt(EXPRS_NEXT(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *GBCarrexpr(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCarrexpr");
    DBUG_PRINT("GBC", ("GBCarrexpr"));

    // no array support

    DBUG_RETURN(arg_node);
}

node *GBCexprstmt(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCexprstmt");
    DBUG_PRINT("GBC", ("GBCexprstmt"));

    node *expr = EXPRSTMT_EXPR(arg_node);
    TRAVdo(expr, arg_info);

    if (NODE_TYPE(expr) == N_funcall)
    {
        node *symboltableEntry = STdeepFindFundef(INFO_SYMBOL_TABLE(arg_info), FUNCALL_NAME(expr));
        node *link = SYMBOLTABLEENTRY_LINK(symboltableEntry);

        if (FUNDEF_ISEXTERN(link))
        {
            DBUG_RETURN(arg_node);
        }

        switch (SYMBOLTABLEENTRY_TYPE(symboltableEntry))
        {
        case T_int:
            fprintf(INFO_FILE(arg_info), "  ipop\n");
            break;
        case T_float:
            fprintf(INFO_FILE(arg_info), "  fpop\n");
            break;
        case T_bool:
            fprintf(INFO_FILE(arg_info), "  bpop\n");
            break;
        case T_void:
            break;
        case T_unknown:
            break;
        }
    }

    DBUG_RETURN(arg_node);
}

node *GBCfuncall(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCfuncall");
    DBUG_PRINT("GBC", ("GBCfuncall"));

    node *symboltableEntry = STdeepFindFundef(INFO_SYMBOL_TABLE(arg_info), FUNCALL_NAME(arg_node));

    fprintf(INFO_FILE(arg_info), "  isrg\n");

    TRAVopt(FUNCALL_ARGS(arg_node), arg_info);
    INFO_TYPE(arg_info) = SYMBOLTABLEENTRY_TYPE(symboltableEntry);

    switch (FUNDEF_ISEXTERN(SYMBOLTABLEENTRY_LINK(symboltableEntry)))
    {
    case 0:
        fprintf(INFO_FILE(arg_info), "  jsr %ld %s\n", STcountParams(SYMBOLTABLEENTRY_TABLE(symboltableEntry)), FUNCALL_NAME(arg_node));
        break;
    case 1:
        fprintf(INFO_FILE(arg_info), "  jsre %d\n", SYMBOLTABLEENTRY_OFFSET(symboltableEntry));
        break;
    }

    DBUG_RETURN(arg_node);
}

node *GBCfundef(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCfundef");
    DBUG_PRINT("GBC", ("GBCfundef"));

    node *symboltable = INFO_SYMBOL_TABLE(arg_info);
    node *symboltableEntry = STfindFundef(INFO_SYMBOL_TABLE(arg_info), FUNDEF_NAME(arg_node));

    if (FUNDEF_ISEXTERN(arg_node))
    {
        node *symboltableEntryLoop = SYMBOLTABLE_ENTRY(SYMBOLTABLEENTRY_TABLE(symboltableEntry));
        char *params = NULL;

        for (; symboltableEntryLoop != NULL; symboltableEntryLoop = SYMBOLTABLEENTRY_NEXT(symboltableEntryLoop))
        {
            if (SYMBOLTABLEENTRY_PARAM(symboltableEntryLoop))
            {
                params = STRcatn(3, params, " ", typeToString(SYMBOLTABLEENTRY_TYPE(symboltableEntryLoop)));
            }
        }

        int length = snprintf(NULL, 0, "fun \"%s\" %s %s", FUNDEF_NAME(arg_node), typeToString(FUNDEF_TYPE(arg_node)), params == NULL ? "" : params);
        int lengthPlus = length + 1;
        char *str = (char *)malloc(lengthPlus);

        snprintf(str, lengthPlus, "fun \"%s\" %s %s", FUNDEF_NAME(arg_node), typeToString(FUNDEF_TYPE(arg_node)), params == NULL ? "" : params);

        if (INFO_IMPORT(arg_info))
        {
            add(INFO_IMPORT(arg_info), str, 0);
        }
        else
        {
            INFO_IMPORT(arg_info) = push(str, 0, NULL);
        }

        free(params);
    }
    else
    {
        fprintf(INFO_FILE(arg_info), "%s:\n", FUNDEF_NAME(arg_node));

        node *symboltableEntryLoop = SYMBOLTABLE_ENTRY(SYMBOLTABLEENTRY_TABLE(symboltableEntry));
        char *params = NULL;

        for (; symboltableEntryLoop != NULL; symboltableEntryLoop = SYMBOLTABLEENTRY_NEXT(symboltableEntryLoop))
        {
            if (SYMBOLTABLEENTRY_PARAM(symboltableEntryLoop))
            {
                params = STRcatn(3, params, " ", typeToString(SYMBOLTABLEENTRY_TYPE(symboltableEntryLoop)));
            }
        }

        int length = snprintf(NULL, 0, "fun \"%s\" %s %s %s", FUNDEF_NAME(arg_node), typeToString(FUNDEF_TYPE(arg_node)), params, FUNDEF_NAME(arg_node));
        int lengthPlus = length + 1;
        char *str = (char *)malloc(lengthPlus);

        snprintf(str, lengthPlus, "fun \"%s\" %s %s %s", FUNDEF_NAME(arg_node), typeToString(FUNDEF_TYPE(arg_node)), params == NULL ? "" : params, FUNDEF_NAME(arg_node));

        if (INFO_EXPORT(arg_info))
        {
            add(INFO_EXPORT(arg_info), str, 0);
        }
        else
        {
            INFO_EXPORT(arg_info) = push(str, 0, NULL);
        }

        INFO_SYMBOL_TABLE(arg_info) = SYMBOLTABLEENTRY_TABLE(symboltableEntry);

        if (STcountVarDecls(INFO_SYMBOL_TABLE(arg_info)) > 0)
        {
            fprintf(INFO_FILE(arg_info), "   esr %ld\n", STcountVarDecls(INFO_SYMBOL_TABLE(arg_info)));
        }

        TRAVopt(FUNDEF_PARAMS(arg_node), arg_info);
        TRAVopt(FUNDEF_FUNBODY(arg_node), arg_info);

        if (FUNDEF_TYPE(arg_node) == T_void)
        {
            fprintf(INFO_FILE(arg_info), "  %s\n", "return");
        }

        INFO_SYMBOL_TABLE(arg_info) = symboltable;

        fputc('\n', INFO_FILE(arg_info));
    }

    DBUG_RETURN(arg_node);
}

node *GBCfundefs(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCfundefs");
    DBUG_PRINT("GBC", ("GBCfundefs"));

    TRAVdo(FUNDEFS_FUNDEF(arg_node), arg_info);
    TRAVopt(FUNDEFS_NEXT(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *GBCfunbody(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCfunbody");
    DBUG_PRINT("GBC", ("GBCfunbody"));

    TRAVopt(FUNBODY_VARDECLS(arg_node), arg_info);
    TRAVopt(FUNBODY_STMTS(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *GBCreturn(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCreturn");
    DBUG_PRINT("GBC", ("GBCreturn"));

    node *table = INFO_SYMBOL_TABLE(arg_info);
    TRAVopt(RETURN_EXPR(arg_node), arg_info);

    if (SYMBOLTABLE_RETURNTYPE(table) == T_int)
    {
        fprintf(INFO_FILE(arg_info), "  %s\n", "ireturn");
    }
    else if (SYMBOLTABLE_RETURNTYPE(table) == T_float)
    {
        fprintf(INFO_FILE(arg_info), "  %s\n", "freturn");
    }
    else if (SYMBOLTABLE_RETURNTYPE(table) == T_bool)
    {
        fprintf(INFO_FILE(arg_info), "  %s\n", "breturn");
    }
    else if (SYMBOLTABLE_RETURNTYPE(table) == T_void)
    {
        fprintf(INFO_FILE(arg_info), "  %s\n", "return");
    }
    else if (SYMBOLTABLE_RETURNTYPE(table) == T_unknown)
    {
        CTIabort("Type unknown found, aborting system");
    }

    DBUG_RETURN(arg_node);
}

node *GBCifelse(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCifelse");
    DBUG_PRINT("GBC", ("GBCifelse"));

    TRAVdo(IFELSE_COND(arg_node), arg_info);

    char *elseBranch;
    bool elseBool = IFELSE_ELSE(arg_node) != NULL;

    if (elseBool)
    {
        elseBranch = generateBranch("else", arg_info);
    }
    else
    {
        elseBranch = generateBranch("end", arg_info);
    }

    char *endBranch = IFELSE_ELSE(arg_node) ? generateBranch("end", arg_info) : elseBranch;

    fprintf(INFO_FILE(arg_info), "  branch_f %s\n\n", elseBranch);

    TRAVopt(IFELSE_THEN(arg_node), arg_info);

    if (elseBool)
    {
        fprintf(INFO_FILE(arg_info), "  jump %s\n\n", endBranch);
        fprintf(INFO_FILE(arg_info), "%s:\n", elseBranch);
        TRAVopt(IFELSE_ELSE(arg_node), arg_info);
        fputc('\n', INFO_FILE(arg_info));
    }

    fprintf(INFO_FILE(arg_info), "%s:\n", endBranch);
    free(elseBranch);

    if (elseBool)
    {
        free(endBranch);
    }

    DBUG_RETURN(arg_node);
}

node *GBCfor(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCfor");
    DBUG_PRINT("GBC", ("GBCfor"));

    // do nothing since everything is coverted to a while

    DBUG_RETURN(arg_node);
}

node *GBCwhile(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCwhile");
    DBUG_PRINT("GBC", ("GBCwhile"));

    char *whileBranch = generateBranch("while", arg_info);
    char *endBranch = generateBranch("end", arg_info);

    fprintf(INFO_FILE(arg_info), "\n%s:\n", whileBranch);

    TRAVdo(WHILE_COND(arg_node), arg_info);

    fprintf(INFO_FILE(arg_info), "  branch_f %s\n", endBranch);

    TRAVopt(WHILE_BLOCK(arg_node), arg_info);

    fprintf(INFO_FILE(arg_info), "  jump %s\n", whileBranch);
    fprintf(INFO_FILE(arg_info), "%s:\n\n", endBranch);

    free(whileBranch);
    free(endBranch);

    DBUG_RETURN(arg_node);
}

node *GBCdowhile(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCdowhile");
    DBUG_PRINT("GBC", ("GBCdowhile"));

    char *branchName = generateBranch("dowhile", arg_info);
    fprintf(INFO_FILE(arg_info), "\n%s:\n", branchName);

    TRAVopt(DOWHILE_BLOCK(arg_node), arg_info);
    TRAVdo(DOWHILE_COND(arg_node), arg_info);

    fprintf(INFO_FILE(arg_info), "  branch_t %s\n", branchName);

    free(branchName);

    DBUG_RETURN(arg_node);
}

node *GBCglobdef(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCglobdef");
    DBUG_PRINT("GBC", ("GBCglobdef"));

    if (GLOBDEF_ISEXTERN(arg_node))
    {
        char *str = STRcatn(4, "var \"", GLOBDEF_NAME(arg_node), "\" ", typeToString(GLOBDEF_TYPE(arg_node)));

        if (INFO_IMPORT(arg_info))
        {
            add(INFO_IMPORT(arg_info), str, 0);
        }
        else
        {
            INFO_IMPORT(arg_info) = push(str, 0, NULL);
        }
    }
    else if (GLOBDEF_ISEXPORT(arg_node))
    {
        node *symboltableEntry = STfindInParent(INFO_SYMBOL_TABLE(arg_info), GLOBDEF_NAME(arg_node));

        char *str = STRcatn(4, "var \"", GLOBDEF_NAME(arg_node), "\" ", STRitoa(SYMBOLTABLEENTRY_OFFSET(symboltableEntry)));

        if (INFO_EXPORT(arg_info))
        {
            add(INFO_EXPORT(arg_info), str, 0);
        }
        else
        {
            INFO_EXPORT(arg_info) = push(str, 0, NULL);
        }
    }

    if (!GLOBDEF_ISEXTERN(arg_node))
    {
        if (INFO_GLOBAL(arg_info))
        {
            add(INFO_GLOBAL(arg_info), STRcpy(typeToString(GLOBDEF_TYPE(arg_node))), 0);
        }
        else
        {
            INFO_GLOBAL(arg_info) = push(STRcpy(typeToString(GLOBDEF_TYPE(arg_node))), 0, NULL);
        }
    }

    TRAVopt(GLOBDEF_DIMS(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *GBCglobdecl(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCglobdef");
    DBUG_PRINT("GBC", ("GBCglobdef"));

    // isn't needed

    DBUG_RETURN(arg_node);
}

node *GBCparam(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCparam");
    DBUG_PRINT("GBC", ("GBCparam"));

    TRAVopt(PARAM_DIMS(arg_node), arg_info);
    TRAVopt(PARAM_NEXT(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *GBCvardecl(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCvardecl");
    DBUG_PRINT("GBC", ("GBCvardecl"));

    TRAVopt(VARDECL_DIMS(arg_node), arg_info);
    TRAVopt(VARDECL_INIT(arg_node), arg_info);
    TRAVopt(VARDECL_NEXT(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *GBCstmts(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCstmts");
    DBUG_PRINT("GBC", ("GBCstmts"));

    TRAVdo(STMTS_STMT(arg_node), arg_info);
    TRAVopt(STMTS_NEXT(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *GBCassign(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCassign");
    DBUG_PRINT("GBC", ("GBCassign"));

    TRAVdo(ASSIGN_LET(arg_node), arg_info);
    TRAVdo(ASSIGN_EXPR(arg_node), arg_info);

    node *symboltableEntry = INFO_SYMBOL_TABLE_ENTRY(arg_info);

    if (SYMBOLTABLEENTRY_DEPTH(symboltableEntry) == 0)
    {
        if (SYMBOLTABLEENTRY_TYPE(symboltableEntry) == T_int)
        {
            fprintf(INFO_FILE(arg_info), "  %cstoreg %d\n", 'i', SYMBOLTABLEENTRY_OFFSET(symboltableEntry));
        }
        else if (SYMBOLTABLEENTRY_TYPE(symboltableEntry) == T_float)
        {
            fprintf(INFO_FILE(arg_info), "  %cstoreg %d\n", 'f', SYMBOLTABLEENTRY_OFFSET(symboltableEntry));
        }
        else if (SYMBOLTABLEENTRY_TYPE(symboltableEntry) == T_bool)
        {
            fprintf(INFO_FILE(arg_info), "  %cstoreg %d\n", 'b', SYMBOLTABLEENTRY_OFFSET(symboltableEntry));
        }
    }
    else
    {
        if (SYMBOLTABLEENTRY_TYPE(symboltableEntry) == T_int)
        {
            fprintf(INFO_FILE(arg_info), "  %cstore %d\n", 'i', SYMBOLTABLEENTRY_OFFSET(symboltableEntry));
        }
        else if (SYMBOLTABLEENTRY_TYPE(symboltableEntry) == T_float)
        {
            fprintf(INFO_FILE(arg_info), "  %cstore %d\n", 'f', SYMBOLTABLEENTRY_OFFSET(symboltableEntry));
        }
        else if (SYMBOLTABLEENTRY_TYPE(symboltableEntry) == T_bool)
        {
            fprintf(INFO_FILE(arg_info), "  %cstore %d\n", 'b', SYMBOLTABLEENTRY_OFFSET(symboltableEntry));
        }
    }

    INFO_SYMBOL_TABLE_ENTRY(arg_info) = NULL;

    DBUG_RETURN(arg_node);
}

node *GBCbinop(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCbinop");
    DBUG_PRINT("GBC", ("GBCbinop"));

    TRAVdo(BINOP_LEFT(arg_node), arg_info);
    TRAVdo(BINOP_RIGHT(arg_node), arg_info);

    const char *op;
    const char *type;
    const int binop = BINOP_OP(arg_node);
    const int infoType = INFO_TYPE(arg_info);

    if (binop == BO_add)
    {
        op = "add";
    }
    else if (binop == BO_sub)
    {
        op = "sub";
    }
    else if (binop == BO_mul)
    {
        op = "mul";
    }
    else if (binop == BO_div)
    {
        op = "div";
    }
    else if (binop == BO_mod)
    {
        op = "rem";
    }
    else if (binop == BO_lt)
    {
        op = "lt";
    }
    else if (binop == BO_le)
    {
        op = "le";
    }
    else if (binop == BO_gt)
    {
        op = "gt";
    }
    else if (binop == BO_ge)
    {
        op = "ge";
    }
    else if (binop == BO_eq)
    {
        op = "eq";
    }
    else if (binop == BO_ne)
    {
        op = "ne";
    }
    else if (binop == BO_unknown)
    {
        CTIabortLine(NODE_LINE(arg_node), "Operator not known");
    }

    if (infoType == T_int)
    {
        type = "i";
    }
    else if (infoType == T_float)
    {
        type = "f";
    }
    else if (infoType == T_bool)
    {
        type = "b";
    }

    fprintf(INFO_FILE(arg_info), "  %s%s\n", type, op);

    DBUG_RETURN(arg_node);
}

node *GBCmonop(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCmonop");
    DBUG_PRINT("GBC", ("GBCmonop"));

    TRAVdo(MONOP_OPERAND(arg_node), arg_info);

    const char *op;
    const char *type;
    const int monop = MONOP_OP(arg_node);
    const int infoType = INFO_TYPE(arg_info);

    if (monop == MO_minus)
    {
        op = "neg";
    }
    else if (monop == MO_neg)
    {
        op = "not";
    }
    else if (monop == MO_unknown)
    {
        CTIabortLine(NODE_LINE(arg_node), "Operator not known");
    }

    if (infoType == T_int)
    {
        type = "i";
    }
    else if (infoType == T_float)
    {
        type = "f";
    }
    else if (infoType == T_bool)
    {
        type = "b";
    }

    fprintf(INFO_FILE(arg_info), "  %s%s\n", type, op);

    DBUG_RETURN(arg_node);
}

node *GBCcast(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCcast");
    DBUG_PRINT("GBC", ("GBCcast"));

    TRAVdo(CAST_EXPR(arg_node), arg_info);

    if (CAST_TYPE(arg_node) == T_int)
    {
        fprintf(INFO_FILE(arg_info), "  f2i\n");
    }
    else if (CAST_TYPE(arg_node) == T_float)
    {
        fprintf(INFO_FILE(arg_info), "  i2f\n");
    }
    else if (CAST_TYPE(arg_node) == T_bool)
    {
        fprintf(INFO_FILE(arg_info), "  bi2f\n");
    }

    INFO_TYPE(arg_info) = CAST_TYPE(arg_node);

    DBUG_RETURN(arg_node);
}

node *GBCvar(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCvar");
    DBUG_PRINT("GBC", ("GBCvar"));

    node *decl = VAR_DECL(arg_node);
    node *symboltableEntry = STfindByNode(INFO_SYMBOL_TABLE(arg_info), decl);

    INFO_TYPE(arg_info) = SYMBOLTABLEENTRY_TYPE(symboltableEntry);

    if (NODE_TYPE(decl) == N_globdef)
    {
        char scope = GLOBDEF_ISEXTERN(decl) ? 'e' : 'g';

        if (GLOBDEF_TYPE(decl) == T_int)
        {
            fprintf(INFO_FILE(arg_info), "  iload%c %d\n", scope, SYMBOLTABLEENTRY_OFFSET(symboltableEntry));
        }
        else if (GLOBDEF_TYPE(decl) == T_float)
        {
            fprintf(INFO_FILE(arg_info), "  fload%c %d\n", scope, SYMBOLTABLEENTRY_OFFSET(symboltableEntry));
        }
    }
    else
    {
        switch (SYMBOLTABLEENTRY_TYPE(symboltableEntry))
        {
        case T_int:
            fprintf(
                INFO_FILE(arg_info),
                SYMBOLTABLEENTRY_OFFSET(symboltableEntry) < 4 ? "   iload_%d\n" : "    iload %d\n",
                SYMBOLTABLEENTRY_OFFSET(symboltableEntry));
            break;
        case T_float:
            fprintf(
                INFO_FILE(arg_info),
                SYMBOLTABLEENTRY_OFFSET(symboltableEntry) < 4 ? "   fload_%d\n" : "    fload %d\n",
                SYMBOLTABLEENTRY_OFFSET(symboltableEntry));
            break;
        case T_bool:
            fprintf(
                INFO_FILE(arg_info),
                SYMBOLTABLEENTRY_OFFSET(symboltableEntry) < 4 ? "   bload_%d\n" : "    bload %d\n",
                SYMBOLTABLEENTRY_OFFSET(symboltableEntry));
            break;
        case T_void:
            break;
        case T_unknown:
            break;
        }
    }

    DBUG_RETURN(arg_node);
}

node *GBCvarlet(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCvarlet");
    DBUG_PRINT("GBC", ("GBCvarlet"));

    node *symboltable = INFO_SYMBOL_TABLE(arg_info);
    INFO_SYMBOL_TABLE_ENTRY(arg_info) = STfindInParent(symboltable, VARLET_NAME(arg_node));

    DBUG_RETURN(arg_node);
}

node *GBCnum(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCnum");
    DBUG_PRINT("GBC", ("GBCnum"));

    char *str = STRcat("int ", STRitoa(NUM_VALUE(arg_node)));

    fprintf(INFO_FILE(arg_info), "  iloadc %d\n", INFO_COUNTER(arg_info));
    addToConstant(arg_info, str);

    INFO_TYPE(arg_info) = T_int;

    DBUG_RETURN(arg_node);
}

node *GBCfloat(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCfloat");
    DBUG_PRINT("GBC", ("GBCfloat"));

    int length = snprintf(NULL, 0, "float %f", FLOAT_VALUE(arg_node));
    char *str = malloc(length + 1);

    snprintf(str, length + 1, "float %f", FLOAT_VALUE(arg_node));

    fprintf(INFO_FILE(arg_info), "  floadc %d\n", INFO_COUNTER(arg_info));
    addToConstant(arg_info, str);

    INFO_TYPE(arg_info) = T_float;

    DBUG_RETURN(arg_node);
}

node *GBCbool(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCbool");
    DBUG_PRINT("GBC", ("GBCbool"));

    char *str = STRcat("bool ", BOOL_VALUE(arg_node) ? "true" : "false");

    fprintf(INFO_FILE(arg_info), "  bloadc %d\n", INFO_COUNTER(arg_info));
    addToConstant(arg_info, str);

    INFO_TYPE(arg_info) = T_bool;

    DBUG_RETURN(arg_node);
}

node *GBCternary(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCternary");
    DBUG_PRINT("GBC", ("GBCternary"));

    char *branchName = generateBranch("false_expr", arg_info);

    TRAVopt(TERNARY_EXPR(arg_node), arg_info);

    fprintf(INFO_FILE(arg_info), "  branch_f %s\n", branchName);

    TRAVopt(TERNARY_THEN(arg_node), arg_info);

    char *branchNameEnd = generateBranch("end", arg_info);

    fprintf(INFO_FILE(arg_info), "  jump %s\n", branchNameEnd);
    fprintf(INFO_FILE(arg_info), "%s:\n", branchName);

    TRAVopt(TERNARY_ELSE(arg_node), arg_info);

    fprintf(INFO_FILE(arg_info), "%s:\n", branchNameEnd);

    DBUG_RETURN(arg_node);
}

node *GBCerror(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCerror");
    DBUG_PRINT("GBC", ("GBCerror"));

    TRAVopt(ERROR_NEXT(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

/*
 * Traversal start function
 */

node *GBCdoGenByteCode(node *syntaxtree)
{
    DBUG_ENTER("GBCdoGenByteCode");
    DBUG_PRINT("GBC", ("GBCdoGenByteCode"));

    global.outfile = global.outfile ? global.outfile : STRcpy("a.out");

    info *info = MakeInfo();

    INFO_FILE(info) = fopen(global.outfile, "w");

    if (INFO_FILE(info) == NULL)
    {
        CTIabort("Could not open global outfile");
    }

    TRAVpush(TR_gbc);
    syntaxtree = TRAVdo(syntaxtree, info);
    TRAVpop();

    writeGlobals(info);
    FreeInfo(info);

    DBUG_RETURN(syntaxtree);
}