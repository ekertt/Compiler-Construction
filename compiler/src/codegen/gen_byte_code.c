#include "globals.h"
#include "gen_byte_code.h"
#include "linked_list.h"
#include "symbol_table.h"

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

/*
 * INFO structure
 */
struct INFO
{
    FILE *fptr;
    node *symbol_table;
    node *symbol_table_entry;

    linkedlist *pool_const;
    linkedlist *pool_export;
    linkedlist *pool_import;
    linkedlist *pool_global;

    int load_counter;
    int branch_count;
    int current_type;
};

#define INFO_FILE(n) ((n)->fptr)
#define INFO_SYMBOL_TABLE(n) ((n)->symbol_table)
#define INFO_SYMBOL_TABLE_ENTRY(n) ((n)->symbol_table_entry)

#define INFO_POOL_CONST(n) ((n)->pool_const)
#define INFO_POOL_EXPORT(n) ((n)->pool_export)
#define INFO_POOL_IMPORT(n) ((n)->pool_import)
#define INFO_POOL_GLOBAL(n) ((n)->pool_global)
#define INFO_LOAD_COUNTER(n) ((n)->load_counter)
#define INFO_BRANCH_COUNT(n) ((n)->branch_count)
#define INFO_CURRENT_TYPE(n) ((n)->current_type)

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
    INFO_POOL_CONST(result) = NULL;
    INFO_POOL_EXPORT(result) = NULL;
    INFO_POOL_IMPORT(result) = NULL;
    INFO_POOL_GLOBAL(result) = NULL;
    INFO_LOAD_COUNTER(result) = 0;
    INFO_BRANCH_COUNT(result) = 0;
    INFO_CURRENT_TYPE(result) = T_unknown;

    DBUG_RETURN(result);
}

static info *FreeInfo(info *info)
{
    DBUG_ENTER("FreeInfo");

    dipsose(INFO_POOL_CONST(info));
    dipsose(INFO_POOL_EXPORT(info));
    dipsose(INFO_POOL_IMPORT(info));
    dipsose(INFO_POOL_GLOBAL(info));

    info = MEMfree(info);

    DBUG_RETURN(info);
}

char *createBranch(const char *name, info *info)
{
    INFO_BRANCH_COUNT(info) += 1;
    char *index = STRitoa(INFO_BRANCH_COUNT(info));
    char *branch = STRcatn(3, index, "_", name);

    free(index);

    return branch;
}

void putInPoolGlobal(info *arg_info, char *value)
{
    if (INFO_POOL_GLOBAL(arg_info) == NULL)
    {
        INFO_POOL_GLOBAL(arg_info) = push(value, 0, NULL);
    }
    else
    {
        add(INFO_POOL_GLOBAL(arg_info), value, 0);
    }
}

void putInPoolConst(info *arg_info, char *value)
{
    if (INFO_POOL_CONST(arg_info) == NULL)
    {
        INFO_POOL_CONST(arg_info) = push(value, INFO_LOAD_COUNTER(arg_info), NULL);
    }
    else
    {
        add(INFO_POOL_CONST(arg_info), value, INFO_LOAD_COUNTER(arg_info));
    }

    INFO_LOAD_COUNTER(arg_info) += 1;
}

void putInPoolExport(info *arg_info, char *value)
{
    if (INFO_POOL_EXPORT(arg_info) == NULL)
    {
        INFO_POOL_EXPORT(arg_info) = push(value, 0, NULL);
    }
    else
    {
        add(INFO_POOL_EXPORT(arg_info), value, 0);
    }
}

void putInPoolImport(info *arg_info, char *value)
{
    if (INFO_POOL_IMPORT(arg_info) == NULL)
    {
        INFO_POOL_IMPORT(arg_info) = push(value, 0, NULL);
    }
    else
    {
        add(INFO_POOL_IMPORT(arg_info), value, 0);
    }
}

void writeGlobals(info *arg_info)
{
    linkedlist *pool_global = INFO_POOL_GLOBAL(arg_info);
    linkedlist *pool_const = INFO_POOL_CONST(arg_info);
    linkedlist *pool_export = INFO_POOL_EXPORT(arg_info);
    linkedlist *pool_import = INFO_POOL_IMPORT(arg_info);
    FILE *fileptr = INFO_FILE(arg_info);

    while (pool_global != NULL)
    {
        fprintf(fileptr, ".global %s\n", pool_global->val);
        pool_global = pool_global->next;
    }

    while (pool_const != NULL)
    {
        fprintf(fileptr, ".const %s\n", pool_const->val);
        pool_const = pool_const->next;
    }

    while (pool_export != NULL)
    {
        fprintf(fileptr, ".export%s\n", pool_export->val);
        pool_export = pool_export->next;
    }

    while (pool_import != NULL)
    {
        fprintf(fileptr, ".import%s\n", pool_import->val);
        pool_import = pool_import->next;
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

    DBUG_RETURN(arg_node);
}

node *GBCsymboltableentry(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCsymboltableentry");
    DBUG_PRINT("GBC", ("GBCsymboltableentry"));

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

    DBUG_RETURN(arg_node);
}

node *GBCexprstmt(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCexprstmt");
    DBUG_PRINT("GBC", ("GBCexprstmt"));

    node *expr = EXPRSTMT_EXPR(arg_node);
    TRAVdo(expr, arg_info);

    DBUG_PRINT("GBC", ("GBCexprstmt 2"));

    if (NODE_TYPE(expr) != N_funcall)
    {
        DBUG_RETURN(arg_node);
    }

    DBUG_PRINT("GBC", ("GBCexprstmt 3"));

    node *entry = STdeepFindFundef(INFO_SYMBOL_TABLE(arg_info), FUNCALL_NAME(expr));
    node *link = SYMBOLTABLEENTRY_LINK(entry);

    if (FUNDEF_ISEXTERN(link))
    {
        DBUG_RETURN(arg_node);
    }

    DBUG_PRINT("GBC", ("GBCexprstmt 4"));

    switch (SYMBOLTABLEENTRY_TYPE(entry))
    {
    case T_int:
        fprintf(INFO_FILE(arg_info), "\tipop\n");
        break;
    case T_float:
        fprintf(INFO_FILE(arg_info), "\tfpop\n");
        break;
    case T_bool:
        fprintf(INFO_FILE(arg_info), "\tbpop\n");
        break;
    case T_void:
        break;
    case T_unknown:
        break;
    }

    DBUG_RETURN(arg_node);
}

node *GBCfuncall(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCfuncall");
    DBUG_PRINT("GBC", ("GBCfuncall"));

    node *entry = STdeepFindFundef(INFO_SYMBOL_TABLE(arg_info), FUNCALL_NAME(arg_node));
    node *table = SYMBOLTABLEENTRY_TABLE(entry);
    node *link = SYMBOLTABLEENTRY_LINK(entry);  

    fprintf(INFO_FILE(arg_info), "\tisrg\n");
    TRAVopt(FUNCALL_ARGS(arg_node), arg_info);
    INFO_CURRENT_TYPE(arg_info) = SYMBOLTABLEENTRY_TYPE(entry);

    if (FUNDEF_ISEXTERN(link) == 1)
    {
        fprintf(INFO_FILE(arg_info), "\tjsre %d\n", SYMBOLTABLEENTRY_OFFSET(entry));
    }
    else
    {
        fprintf(INFO_FILE(arg_info), "\tjsr %ld %s\n", STcountParams(table), FUNCALL_NAME(arg_node));
    }

    DBUG_RETURN(arg_node);
}

node *GBCfundef(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCfundef");
    DBUG_PRINT("GBC", ("GBCfundef"));

    node *table = INFO_SYMBOL_TABLE(arg_info);
    node *entry = STfindFundef(table, FUNDEF_NAME(arg_node));

    if (FUNDEF_ISEXTERN(arg_node))
    {
        node *fentry = SYMBOLTABLE_ENTRY(SYMBOLTABLEENTRY_TABLE(entry));
        char *params = NULL;

        for (; fentry != NULL; fentry = SYMBOLTABLEENTRY_NEXT(fentry))
        {
            if (!SYMBOLTABLEENTRY_PARAM(fentry))
            {
                continue;
            }

            char *temp = STRcatn(3, params, " ", typeToString(SYMBOLTABLEENTRY_TYPE(fentry)));

            params = temp;
        }

        int length = snprintf(
            NULL,
            0,
            "fun \"%s\" %s %s",
            FUNDEF_NAME(arg_node),
            typeToString(FUNDEF_TYPE(arg_node)),
            params == NULL ? "" : params);

        char *str = (char *)malloc(length + 1);

        snprintf(
            str,
            length + 1,
            "fun \"%s\" %s %s",
            FUNDEF_NAME(arg_node),
            typeToString(FUNDEF_TYPE(arg_node)),
            params == NULL ? "" : params);

        putInPoolImport(arg_info, str);
        free(params);
    }
    else
    {
        fprintf(INFO_FILE(arg_info), "%s:\n", FUNDEF_NAME(arg_node));

        if (FUNDEF_ISEXPORT(arg_node))
        {
            node *fentry = SYMBOLTABLE_ENTRY(SYMBOLTABLEENTRY_TABLE(entry));
            char *params = NULL;

            for (; fentry != NULL; fentry = SYMBOLTABLEENTRY_NEXT(fentry))
            {
                if (!SYMBOLTABLEENTRY_PARAM(fentry))
                {
                    continue;
                }

                char *temp = STRcatn(3, params, " ", typeToString(SYMBOLTABLEENTRY_TYPE(fentry)));
                free(params);

                params = temp;
            }

            int length = snprintf(
                NULL,
                0,
                "fun \"%s\" %s %s %s",
                FUNDEF_NAME(arg_node),
                typeToString(FUNDEF_TYPE(arg_node)),
                params == NULL ? "" : params,
                FUNDEF_NAME(arg_node));

            char *str = (char *)malloc(length + 1);

            snprintf(
                str,
                length + 1,
                "fun \"%s\" %s %s %s",
                FUNDEF_NAME(arg_node),
                typeToString(FUNDEF_TYPE(arg_node)),
                params == NULL ? "" : params,
                FUNDEF_NAME(arg_node));

            putInPoolExport(arg_info, str);
        }

        INFO_SYMBOL_TABLE(arg_info) = SYMBOLTABLEENTRY_TABLE(entry);
        size_t registers = STcountVarDecls(INFO_SYMBOL_TABLE(arg_info));

        if (registers > 0)
        {
            fprintf(
                INFO_FILE(arg_info),
                "\tesr %ld\n",
                registers);
        }

        TRAVopt(FUNDEF_PARAMS(arg_node), arg_info);
        TRAVopt(FUNDEF_FUNBODY(arg_node), arg_info);

        if (FUNDEF_TYPE(arg_node) == T_void)
        {
            fprintf(INFO_FILE(arg_info), "\t%s\n", "return");
        }

        INFO_SYMBOL_TABLE(arg_info) = table;

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
        fprintf(INFO_FILE(arg_info), "\t%s\n", "ireturn");
    }
    else if (SYMBOLTABLE_RETURNTYPE(table) == T_float)
    {
        fprintf(INFO_FILE(arg_info), "\t%s\n", "freturn");
    }
    else if (SYMBOLTABLE_RETURNTYPE(table) == T_bool)
    {
        fprintf(INFO_FILE(arg_info), "\t%s\n", "breturn");
    }
    else if (SYMBOLTABLE_RETURNTYPE(table) == T_void)
    {
        fprintf(INFO_FILE(arg_info), "\t%s\n", "return");
    }
    else if (SYMBOLTABLE_RETURNTYPE(table) == T_unknown)
    {
        CTIabort("Unknown type found in file: %s, line: %s", __FILE__, __LINE__);
    }

    DBUG_RETURN(arg_node);
}

node *GBCifelse(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCifelse");
    DBUG_PRINT("GBC", ("GBCifelse"));

    TRAVdo(IFELSE_COND(arg_node), arg_info);

    char *branch = createBranch(IFELSE_ELSE(arg_node) == NULL ? "end" : "else", arg_info);
    char *end = IFELSE_ELSE(arg_node) != NULL ? createBranch("end", arg_info) : branch;

    fprintf(INFO_FILE(arg_info), "\tbranch_f %s\n\n", branch);

    TRAVopt(IFELSE_THEN(arg_node), arg_info);

    if (IFELSE_ELSE(arg_node) != NULL)
    {
        fprintf(INFO_FILE(arg_info), "\tjump %s\n\n", end);
        fprintf(INFO_FILE(arg_info), "%s:\n", branch);
        TRAVopt(IFELSE_ELSE(arg_node), arg_info);
        fputc('\n', INFO_FILE(arg_info));
    }

    fprintf(INFO_FILE(arg_info), "%s:\n", end);
    free(branch);

    if (IFELSE_ELSE(arg_node) != NULL)
    {
        free(end);
    }

    DBUG_RETURN(arg_node);
}

node *GBCfor(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCfor");
    DBUG_PRINT("GBC", ("GBCfor"));

    TRAVdo(FOR_START(arg_node), arg_info);
    TRAVdo(FOR_STOP(arg_node), arg_info);
    TRAVopt(FOR_STEP(arg_node), arg_info);
    TRAVopt(FOR_BLOCK(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *GBCwhile(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCwhile");
    DBUG_PRINT("GBC", ("GBCwhile"));

    char *branch = createBranch("while", arg_info);
    char *end = createBranch("end", arg_info);

    fprintf(INFO_FILE(arg_info), "\n%s:\n", branch);
    
    TRAVdo(WHILE_COND(arg_node), arg_info);

    fprintf(INFO_FILE(arg_info), "\tbranch_f %s\n", end);

    TRAVopt(WHILE_BLOCK(arg_node), arg_info);

    fprintf(INFO_FILE(arg_info), "\tjump %s\n", branch);
    fprintf(INFO_FILE(arg_info), "%s:\n\n", end);

    free(branch);
    free(end);

    DBUG_RETURN(arg_node);
}

node *GBCdowhile(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCdowhile");
    DBUG_PRINT("GBC", ("GBCdowhile"));

    char *branch = createBranch("dowhile", arg_info);

    fprintf(INFO_FILE(arg_info), "\n%s:\n", branch);

    TRAVopt(DOWHILE_BLOCK(arg_node), arg_info);
    TRAVdo(DOWHILE_COND(arg_node), arg_info);

    fprintf(INFO_FILE(arg_info), "\tbranch_t %s\n", branch);

    free(branch);

    DBUG_RETURN(arg_node);
}

node *GBCglobdef(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCglobdef");
    DBUG_PRINT("GBC", ("GBCglobdef"));

    if (GLOBDEF_ISEXTERN(arg_node))
    {
        char *str = STRcatn(4, "var \"", GLOBDEF_NAME(arg_node), "\" ", typeToString(GLOBDEF_TYPE(arg_node)));
        putInPoolImport(arg_info, str);
    }
    else if (GLOBDEF_ISEXPORT(arg_node))
    {
        node *entry = STfindInParent(INFO_SYMBOL_TABLE(arg_info), GLOBDEF_NAME(arg_node));

        char *offset = STRitoa(SYMBOLTABLEENTRY_OFFSET(entry));
        char *str = STRcatn(4, "var \"", GLOBDEF_NAME(arg_node), "\" ", offset);
        free(offset);
        putInPoolExport(arg_info, str);
    }

    if (!GLOBDEF_ISEXTERN(arg_node))
    {
        putInPoolGlobal(arg_info, STRcpy(typeToString(GLOBDEF_TYPE(arg_node))));
    }

    TRAVopt(GLOBDEF_DIMS(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *GBCglobdecl(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCglobdef");
    DBUG_PRINT("GBC", ("GBCglobdef"));

    if (GLOBDEF_ISEXTERN(arg_node))
    {
        char *str = STRcatn(4, "var \"", GLOBDEF_NAME(arg_node), "\" ", typeToString(GLOBDEF_TYPE(arg_node)));
        putInPoolImport(arg_info, str);
    }
    else if (GLOBDEF_ISEXPORT(arg_node))
    {
        node *entry = STfindInParent(INFO_SYMBOL_TABLE(arg_info), GLOBDEF_NAME(arg_node));

        char *offset = STRitoa(SYMBOLTABLEENTRY_OFFSET(entry));
        char *str = STRcatn(4, "var \"", GLOBDEF_NAME(arg_node), "\" ", offset);
        free(offset);
        putInPoolExport(arg_info, str);
    }

    if (!GLOBDEF_ISEXTERN(arg_node))
    {
        putInPoolGlobal(arg_info, STRcpy(typeToString(GLOBDEF_TYPE(arg_node))));
    }

    TRAVopt(GLOBDEF_DIMS(arg_node), arg_info);

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

    node *entry = INFO_SYMBOL_TABLE_ENTRY(arg_info);

    char type;

    if (SYMBOLTABLEENTRY_TYPE(entry) == T_int)
    {
        type = 'i';
    }
    else if (SYMBOLTABLEENTRY_TYPE(entry) == T_float)
    {
        type = 'f';
    }
    else if (SYMBOLTABLEENTRY_TYPE(entry) == T_bool)
    {
        type = 'b';
    }

    if (SYMBOLTABLEENTRY_DEPTH(entry) == 0)
    {
        fprintf(INFO_FILE(arg_info), "\t%cstoreg %d\n", type, SYMBOLTABLEENTRY_OFFSET(entry));
    }
    else
    {
        fprintf(INFO_FILE(arg_info), "\t%cstore %d\n", type, SYMBOLTABLEENTRY_OFFSET(entry));
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

    const char *operation;

    if (BINOP_OP(arg_node) == BO_add)
    {
        operation = "add";
    }
    else if (BINOP_OP(arg_node) == BO_sub)
    {
        operation = "sub";
    }
    else if (BINOP_OP(arg_node) == BO_mul)
    {
        operation = "mul";
    }
    else if (BINOP_OP(arg_node) == BO_div)
    {
        operation = "div";
    }
    else if (BINOP_OP(arg_node) == BO_mod)
    {
        operation = "rem";
    }
    else if (BINOP_OP(arg_node) == BO_lt)
    {
        operation = "lt";
    }
    else if (BINOP_OP(arg_node) == BO_le)
    {
        operation = "le";
    }
    else if (BINOP_OP(arg_node) == BO_gt)
    {
        operation = "gt";
    }
    else if (BINOP_OP(arg_node) == BO_ge)
    {
        operation = "ge";
    }
    else if (BINOP_OP(arg_node) == BO_eq)
    {
        operation = "eq";
    }
    else if (BINOP_OP(arg_node) == BO_ne)
    {
        operation = "ne";
    }
    else if (BINOP_OP(arg_node) == BO_unknown)
    {
        CTIabortLine(NODE_LINE(arg_node), "Unknown operator type found");
    }

    if (INFO_CURRENT_TYPE(arg_info) == T_int)
    {
        fprintf(INFO_FILE(arg_info), "\ti%s\n", operation);
    }
    else if (INFO_CURRENT_TYPE(arg_info) == T_float)
    {
        fprintf(INFO_FILE(arg_info), "\tf%s\n", operation);
    }
    else if (INFO_CURRENT_TYPE(arg_info) == T_bool)
    {
        fprintf(INFO_FILE(arg_info), "\tb%s\n", operation);
    }

    DBUG_RETURN(arg_node);
}

node *GBCmonop(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCmonop");
    DBUG_PRINT("GBC", ("GBCmonop"));

    TRAVdo(MONOP_OPERAND(arg_node), arg_info);

    const char *operation;

    if (MONOP_OP(arg_node) == MO_minus)
    {
        operation = "neg";
    }
    else if (MONOP_OP(arg_node) == MO_neg)
    {
        operation = "not";
    }
    else if (MONOP_OP(arg_node) == MO_unknown)
    {
        CTIabort("Unknown operator type found in file: %s, line: %s", __FILE__, __LINE__);
    }

    if (INFO_CURRENT_TYPE(arg_info) == T_int)
    {
        fprintf(INFO_FILE(arg_info), "\ti%s\n", operation);
    }
    else if (INFO_CURRENT_TYPE(arg_info) == T_float)
    {
        fprintf(INFO_FILE(arg_info), "\tf%s\n", operation);
    }
    else if (INFO_CURRENT_TYPE(arg_info) == T_bool)
    {
        fprintf(INFO_FILE(arg_info), "\tb%s\n", operation);
    }

    DBUG_RETURN(arg_node);
}

node *GBCcast(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCcast");
    DBUG_PRINT("GBC", ("GBCcast"));

    TRAVdo(CAST_EXPR(arg_node), arg_info);

    if (CAST_TYPE(arg_node) == T_int)
    {
        fprintf(INFO_FILE(arg_info), "\tf2i\n");
    }
    else if (CAST_TYPE(arg_node) == T_float)
    {
        fprintf(INFO_FILE(arg_info), "\ti2f\n");
    }
    else if (CAST_TYPE(arg_node) == T_bool)
    {
        fprintf(INFO_FILE(arg_info), "\tbi2f\n");
    }

    INFO_CURRENT_TYPE(arg_info) = CAST_TYPE(arg_node);

    DBUG_RETURN(arg_node);
}

node *GBCvar(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCvar");
    DBUG_PRINT("GBC", ("GBCvar"));

    node *decl = VAR_DECL(arg_node);
    node *entry = STfindByNode(INFO_SYMBOL_TABLE(arg_info), decl);

    INFO_CURRENT_TYPE(arg_info) = SYMBOLTABLEENTRY_TYPE(entry);

    if (NODE_TYPE(decl) == N_globdef)
    {
        char scope = GLOBDEF_ISEXTERN(decl) ? 'e' : 'g';

        if (GLOBDEF_TYPE(decl) == T_int)
        {
            fprintf(INFO_FILE(arg_info), "\tiload%c %d\n", scope, SYMBOLTABLEENTRY_OFFSET(entry));
        }
        else if (GLOBDEF_TYPE(decl) == T_float)
        {
            fprintf(INFO_FILE(arg_info), "\tfload%c %d\n", scope, SYMBOLTABLEENTRY_OFFSET(entry));
        }
    }
    else
    {
        switch (SYMBOLTABLEENTRY_TYPE(entry))
        {
            case T_int:
                fprintf(
                    INFO_FILE(arg_info),
                    SYMBOLTABLEENTRY_OFFSET(entry) < 4 ? "\tiload_%d\n" : "\tiload %d\n",
                    SYMBOLTABLEENTRY_OFFSET(entry));
                break;
            case T_float:
                fprintf(
                    INFO_FILE(arg_info),
                    SYMBOLTABLEENTRY_OFFSET(entry) < 4 ? "\tfload_%d\n" : "\tfload %d\n",
                    SYMBOLTABLEENTRY_OFFSET(entry));
                break;
            case T_bool:
                fprintf(
                    INFO_FILE(arg_info),
                    SYMBOLTABLEENTRY_OFFSET(entry) < 4 ? "\tbload_%d\n" : "\tbload %d\n",
                    SYMBOLTABLEENTRY_OFFSET(entry));
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

    node *table = INFO_SYMBOL_TABLE(arg_info);
    INFO_SYMBOL_TABLE_ENTRY(arg_info) = STfindInParent(table, VARLET_NAME(arg_node));

    DBUG_RETURN(arg_node);
}

node *GBCnum(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCnum");
    DBUG_PRINT("GBC", ("GBCnum"));

    char *str = STRcat("int ", STRitoa(NUM_VALUE(arg_node)));
    linkedlist *pool_const = search(INFO_POOL_CONST(arg_info), str);

    if (pool_const == NULL)
    {
        fprintf(INFO_FILE(arg_info), "\t%s %d\n", "iloadc", INFO_LOAD_COUNTER(arg_info));
        putInPoolConst(arg_info, str);
    }
    else
    {
        fprintf(INFO_FILE(arg_info), "\t%s %d\n", "iloadc", pool_const->count);
        free(str);
    }

    INFO_CURRENT_TYPE(arg_info) = T_int;

    DBUG_RETURN(arg_node);
}

node *GBCfloat(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCfloat");
    DBUG_PRINT("GBC", ("GBCfloat"));

    int length = snprintf(NULL, 0, "float %f", FLOAT_VALUE(arg_node));
    char *str = malloc(length + 1);
    snprintf(str, length + 1, "float %f", FLOAT_VALUE(arg_node));

    linkedlist *pool_const = search(INFO_POOL_CONST(arg_info), str);

    if (pool_const == NULL)
    {
        fprintf(INFO_FILE(arg_info), "\t%s %d\n", "floadc", INFO_LOAD_COUNTER(arg_info));
        putInPoolConst(arg_info, str);
    }
    else
    {
        fprintf(INFO_FILE(arg_info), "\t%s %d\n", "floadc", pool_const->count);
        free(str);
    }

    INFO_CURRENT_TYPE(arg_info) = T_float;

    DBUG_RETURN(arg_node);
}

node *GBCbool(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCbool");
    DBUG_PRINT("GBC", ("GBCbool"));

    char *str = STRcat("bool ", BOOL_VALUE(arg_node) ? "true" : "false");
    linkedlist *pool_const = search(INFO_POOL_CONST(arg_info), str);

    if (pool_const == NULL)
    {
        fprintf(INFO_FILE(arg_info), "\t%s %d\n", "bloadc", INFO_LOAD_COUNTER(arg_info));
        putInPoolConst(arg_info, str);
    }
    else
    {
        fprintf(INFO_FILE(arg_info), "\t%s %d\n", "bloadc", pool_const->count);
        free(str);
    }

    INFO_CURRENT_TYPE(arg_info) = T_bool;

    DBUG_RETURN(arg_node);
}

node *GBCternary(node *arg_node, info *arg_info)
{
    DBUG_ENTER("GBCternary");
    DBUG_PRINT("GBC", ("GBCternary"));

    char *branch = createBranch("false_expr", arg_info);
    char *end = createBranch("end", arg_info);

    TRAVopt(TERNARY_EXPR(arg_node), arg_info);

    fprintf(INFO_FILE(arg_info), "\tbranch_f %s\n", branch);

    TRAVopt(TERNARY_THEN(arg_node), arg_info);

    fprintf(INFO_FILE(arg_info), "\tjump %s\n", end);
    fprintf(INFO_FILE(arg_info), "%s:\n", branch);

    TRAVopt(TERNARY_ELSE(arg_node), arg_info);

    fprintf(INFO_FILE(arg_info), "%s:\n", end);

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
        CTIabort("Could not open file: %s", global.outfile);
    }

    TRAVpush(TR_gbc);
    syntaxtree = TRAVdo(syntaxtree, info);
    TRAVpop();

    writeGlobals(info);
    fclose(INFO_FILE(info));
    FreeInfo(info);

    DBUG_RETURN(syntaxtree);
}