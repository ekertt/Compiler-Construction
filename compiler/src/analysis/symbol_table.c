/*****************************************************************************
 *
 * Module: symbol table
 *
 * Prefix: ST
 *
 * Description: this initializes the symbol table
 *
 *****************************************************************************/
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
    node *table;
    int params;
    int arguments;
};

/*
 * INFO macros
 */

#define INFO_SYMBOL_TABLE(n) ((n)->table)
#define INFO_ARGUMENTS(n) ((n)->arguments)

/*
 * INFO functions
 */

static info *MakeInfo(node *parent)
{
    info *result;

    DBUG_ENTER("MakeInfo");

    result = (info *)MEMmalloc(sizeof(info));
    node *table = TBmakeSymboltable(NULL);
    SYMBOLTABLE_RETURNTYPE(table) = T_unknown;
    SYMBOLTABLE_PARENT(table) = parent;
    INFO_SYMBOL_TABLE(result) = table;
    INFO_ARGUMENTS(result) = 0;

    DBUG_RETURN(result);
}

static info *FreeInfo(info *info)
{
    DBUG_ENTER("FreeInfo");

    info = MEMfree(info);

    DBUG_RETURN(info);
}

//Helper functions
node *STadd(node *table, node *entry)
{
    DBUG_ENTER("STadd");

    if ((STfind(table, SYMBOLTABLEENTRY_NAME(entry)) != NULL) ||
        (STfindFundef(table, SYMBOLTABLEENTRY_NAME(entry)) != NULL))
    {
        return NULL;
    }

    node *link = SYMBOLTABLEENTRY_LINK(entry);

    if (NODE_TYPE(link) == N_globdef && GLOBDEF_ISEXTERN(link))
    {
        SYMBOLTABLEENTRY_OFFSET(entry) = STcountGlobDecls(table);
    }
    else if (NODE_TYPE(link) == N_fundef && FUNDEF_ISEXTERN(link))
    {
        SYMBOLTABLEENTRY_OFFSET(entry) = STcountFunDecls(table);
    }
    else
    {
        SYMBOLTABLEENTRY_OFFSET(entry) = STcount(table);
    }

    node *latestEntry = STlatestEntry(SYMBOLTABLE_ENTRY(table));

    if (!latestEntry)
    {
        return SYMBOLTABLE_ENTRY(table) = entry;
    }

    SYMBOLTABLEENTRY_NEXT(latestEntry) = entry;

    DBUG_RETURN(entry);
}

size_t STcountVarDecls(node *table)
{
    size_t count = 0;
    node *entry = SYMBOLTABLE_ENTRY(table);

    for (; entry; entry = SYMBOLTABLEENTRY_NEXT(entry))
    {
        if (SYMBOLTABLEENTRY_PARAM(entry))
        {
            continue;
        }

        count++;
    }

    return count;
}

node *STfindByNode(node *table, node *link)
{
    node *entry = SYMBOLTABLE_ENTRY(table);

    for (; entry; entry = SYMBOLTABLEENTRY_NEXT(entry))
    {
        node *n = SYMBOLTABLEENTRY_LINK(entry);

        if (NODE_TYPE(link) != NODE_TYPE(n))
        {
            continue;
        }

        if ((NODE_TYPE(n) == N_globdef && STReq(GLOBDEF_NAME(n), GLOBDEF_NAME(link))) ||
            (NODE_TYPE(n) == N_fundef && STReq(FUNDEF_NAME(n), FUNDEF_NAME(link))) ||
            (NODE_TYPE(n) == N_vardecl && STReq(VARDECL_NAME(n), VARDECL_NAME(link))) ||
            (NODE_TYPE(n) == N_param && STReq(PARAM_NAME(n), PARAM_NAME(link))))
        {
            return entry;
        }
    }

    if (!SYMBOLTABLE_PARENT(table))
    {
        return NULL;
    }

    return STfindByNode(SYMBOLTABLE_PARENT(table), link);
}

node *STfind(node *symboltable, const char *name)
{
    node *symboltableentry = SYMBOLTABLE_ENTRY(symboltable);

    return STfindEntry(symboltableentry, name, T_unknown);
}

node *STfindEntry(node *symboltableentry, const char *name, type type)
{
    if (!symboltableentry)
    {
        return NULL;
    }
    else if ((SYMBOLTABLEENTRY_TABLE(symboltableentry)) ||
             (!STReq(SYMBOLTABLEENTRY_NAME(symboltableentry), name)) ||
             (SYMBOLTABLEENTRY_TYPE(symboltableentry) != type && T_unknown != type))
    {
        return STfindEntry(SYMBOLTABLEENTRY_NEXT(symboltableentry), name, type);
    }

    return symboltableentry;
}

node *STfindInParent(node *symboltable, const char *name)
{
    node *variable = STfind(symboltable, name);
    node *parent = SYMBOLTABLE_PARENT(symboltable);

    if (variable)
    {
        return variable;
    }
    else if (!parent)
    {
        return NULL;
    }

    return STfindInParent(parent, name);
}

node *STlatestEntry(node *linkedlist)
{
    if (!linkedlist || !SYMBOLTABLEENTRY_NEXT(linkedlist))
    {
        return linkedlist;
    }

    return STlatestEntry(SYMBOLTABLEENTRY_NEXT(linkedlist));
}

void STdisplay(node *table, size_t tabs)
{
    STprint(SYMBOLTABLE_ENTRY(table), tabs);
}

void STprint(node *list, size_t tabs)
{
    if (!list)
    {
        return;
    }

    for (size_t i = 0; i < tabs; i++)
    {
        printf("\t");
    }

    printf("Type: %s, Name: %s\n", typeToString(SYMBOLTABLEENTRY_TYPE(list)), SYMBOLTABLEENTRY_NAME(list));

    if (SYMBOLTABLEENTRY_TABLE(list))
    {
        STdisplay(SYMBOLTABLEENTRY_TABLE(list), tabs + 1);
    }

    return STprint(SYMBOLTABLEENTRY_NEXT(list), tabs);
}

size_t STcountParams(node *table)
{
    size_t count = 0;
    node *entry = SYMBOLTABLE_ENTRY(table);

    for (; entry != NULL; entry = SYMBOLTABLEENTRY_NEXT(entry))
    {
        if (!SYMBOLTABLEENTRY_PARAM(entry))
        {
            continue;
        }

        count++;
    }

    return count;
}

size_t STcountGlobDecls(node *table)
{
    size_t count = 0;
    node *entry = SYMBOLTABLE_ENTRY(table);

    for (; entry != NULL; entry = SYMBOLTABLEENTRY_NEXT(entry))
    {
        node *link = SYMBOLTABLEENTRY_LINK(entry);

        if (NODE_TYPE(link) != N_globdef || !GLOBDEF_ISEXTERN(link))
        {
            continue;
        }

        count++;
    }

    return count;
}

size_t STcountFunDecls(node *table)
{
    size_t count = 0;
    node *entry = SYMBOLTABLE_ENTRY(table);

    for (; entry != NULL; entry = SYMBOLTABLEENTRY_NEXT(entry))
    {
        node *link = SYMBOLTABLEENTRY_LINK(entry);

        if (NODE_TYPE(link) != N_fundef || !FUNDEF_ISEXTERN(link))
        {
            continue;
        }

        count++;
    }

    return count;
}

size_t STcount(node *table)
{
    size_t count = 0;

    node *entry = SYMBOLTABLE_ENTRY(table);

    for (; entry; entry = SYMBOLTABLEENTRY_NEXT(entry))
    {
        node *link = SYMBOLTABLEENTRY_LINK(entry);

        if ((NODE_TYPE(link) == N_globdef && GLOBDEF_ISEXTERN(link)) ||
            (NODE_TYPE(link) == N_fundef && (FUNDEF_ISEXTERN(link) || FUNDEF_ISEXPORT(link))))
        {
            continue;
        }

        count++;
    }

    return count;
}

node *STfindFundef(node *table, const char *name)
{
    node *entry = SYMBOLTABLE_ENTRY(table);

    return STfindFundefEntry(entry, name);
}

node *STfindFundefEntry(node *symboltableentry, const char *name)
{
    if (!symboltableentry)
    {
        return NULL;
    }
    else if (!SYMBOLTABLEENTRY_TABLE(symboltableentry) ||
             !STReq(SYMBOLTABLEENTRY_NAME(symboltableentry), name))
    {
        return STfindFundefEntry(SYMBOLTABLEENTRY_NEXT(symboltableentry), name);
    }

    return symboltableentry;
}

node *STdeepFindFundef(node *table, const char *name)
{
    node *found = STfindFundef(table, name);
    node *parent = SYMBOLTABLE_PARENT(table);

    if (found)
    {
        return found;
    }
    else if (!parent)
    {
        return NULL;
    }

    return STdeepFindFundef(parent, name);
}

//Stop helper functions

node *STprogram(node *arg_node, info *arg_info)
{
    DBUG_ENTER("STprogram");
    DBUG_PRINT("ST", ("STprogram"));

    PROGRAM_SYMBOLTABLE(arg_node) = INFO_SYMBOL_TABLE(arg_info);
    PROGRAM_DECLS(arg_node) = TRAVopt(PROGRAM_DECLS(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *STglobdef(node *arg_node, info *arg_info)
{
    DBUG_ENTER("STglobdef");
    DBUG_PRINT("ST", ("STglobdef"));

    node *symboltable = INFO_SYMBOL_TABLE(arg_info);
    node *symboltableentry = TBmakeSymboltableentry(STRcpy(GLOBDEF_NAME(arg_node)), GLOBDEF_TYPE(arg_node), 0, 0, arg_node, NULL, NULL);

    STadd(symboltable, symboltableentry);

    DBUG_RETURN(arg_node);
}

node *STfundef(node *arg_node, info *arg_info)
{
    DBUG_ENTER("STfundef");
    DBUG_PRINT("ST", ("STfundef"));

    node *symboltable = INFO_SYMBOL_TABLE(arg_info);
    info *symbolTableInfo = MakeInfo(symboltable);
    node *symboltableentry = TBmakeSymboltableentry(STRcpy(FUNDEF_NAME(arg_node)), FUNDEF_TYPE(arg_node), 0, 0, arg_node, NULL, INFO_SYMBOL_TABLE(symbolTableInfo));

    SYMBOLTABLE_RETURNTYPE(INFO_SYMBOL_TABLE(symbolTableInfo)) = FUNDEF_TYPE(arg_node);

    STadd(symboltable, symboltableentry);

    FUNDEF_PARAMS(arg_node) = TRAVopt(FUNDEF_PARAMS(arg_node), symbolTableInfo);
    FUNDEF_FUNBODY(arg_node) = TRAVopt(FUNDEF_FUNBODY(arg_node), symbolTableInfo);

    FreeInfo(symbolTableInfo);

    DBUG_RETURN(arg_node);
}

node *STparam(node *arg_node, info *arg_info)
{
    DBUG_ENTER("STparam");
    DBUG_PRINT("ST", ("STparam"));

    node *symboltable = INFO_SYMBOL_TABLE(arg_info);
    node *symboltableentry = TBmakeSymboltableentry(STRcpy(PARAM_NAME(arg_node)), PARAM_TYPE(arg_node), 0, 1, arg_node, NULL, NULL);

    SYMBOLTABLEENTRY_PARAM(symboltableentry) = TRUE;
    STadd(symboltable, symboltableentry);

    PARAM_NEXT(arg_node) = TRAVopt(PARAM_NEXT(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *STfuncall(node *arg_node, info *arg_info)
{
    DBUG_ENTER("STfuncall");
    DBUG_PRINT("ST", ("STfuncall"));

    node *table = INFO_SYMBOL_TABLE(arg_info);
    node *entry = STdeepFindFundef(table, FUNCALL_NAME(arg_node));

    if (entry)
    {
        FUNCALL_DECL(arg_node) = SYMBOLTABLEENTRY_LINK(entry);

        if (FUNCALL_ARGS(arg_node))
        {
            int backarguments = INFO_ARGUMENTS(arg_info);
            INFO_ARGUMENTS(arg_info) = 0;
            FUNCALL_ARGS(arg_node) = TRAVopt(FUNCALL_ARGS(arg_node), arg_info);
            size_t params = STcountParams(SYMBOLTABLEENTRY_TABLE(entry));

            if ((INFO_ARGUMENTS(arg_info) < params) ||
                (INFO_ARGUMENTS(arg_info) > params))
            {
                CTIerrorLine(NODE_LINE(arg_node), "Too few or too many arguments for function.\n");
            }

            INFO_ARGUMENTS(arg_info) = backarguments;
        }
        else if (STcountParams(SYMBOLTABLEENTRY_TABLE(entry)) > 0)
        {
            CTIerrorLine(NODE_LINE(arg_node), "Not enough arguments for function.\n");
        }
    }
    else
    {
        CTIerrorLine(NODE_LINE(arg_node), "`%s()` was declared in a different scope.\n", FUNCALL_NAME(arg_node));
    }

    DBUG_RETURN(arg_node);
}

node *STvardecl(node *arg_node, info *arg_info)
{
    DBUG_ENTER("STvardecl");
    DBUG_PRINT("ST", ("STvardecl"));

    node *symboltable = INFO_SYMBOL_TABLE(arg_info);

    if (VARDECL_INIT(arg_node))
    {
        VARDECL_INIT(arg_node) = TRAVopt(VARDECL_INIT(arg_node), arg_info);
    }

    node *symboltableentry = TBmakeSymboltableentry(STRcpy(VARDECL_NAME(arg_node)), VARDECL_TYPE(arg_node), 0, 1, arg_node, NULL, NULL);

    STadd(symboltable, symboltableentry);

    VARDECL_NEXT(arg_node) = TRAVopt(VARDECL_NEXT(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

node *STvarlet(node *arg_node, info *arg_info)
{
    DBUG_ENTER("STvarlet");
    DBUG_PRINT("ST", ("STvarlet"));

    node *variable = STfindInParent(INFO_SYMBOL_TABLE(arg_info), VARLET_NAME(arg_node));

    if (variable)
    {
        VARLET_DECL(arg_node) = SYMBOLTABLEENTRY_LINK(variable);
    }
    else
    {
        CTIerrorLine(NODE_LINE(arg_node), "`%s` is declared in a different scope\n", VARLET_NAME(arg_node));
    }

    DBUG_RETURN(arg_node);
}

node *STvar(node *arg_node, info *arg_info)
{
    DBUG_ENTER("STvar");
    DBUG_PRINT("ST", ("STvar"));

    node *entry = STfindInParent(INFO_SYMBOL_TABLE(arg_info), VAR_NAME(arg_node));

    if (entry)
    {
        VAR_DECL(arg_node) = SYMBOLTABLEENTRY_LINK(entry);
    }
    else
    {
        CTIerrorLine(NODE_LINE(arg_node), "`%s` is declared in a different scope\n", VAR_NAME(arg_node));
    }

    DBUG_RETURN(arg_node);
}

node *STexprs(node *arg_node, info *arg_info)
{
    DBUG_ENTER("STexprs");
    DBUG_PRINT("ST", ("STexprs"));

    INFO_ARGUMENTS(arg_info) += 1;

    EXPRS_EXPR(arg_node) = TRAVdo(EXPRS_EXPR(arg_node), arg_info);
    EXPRS_NEXT(arg_node) = TRAVopt(EXPRS_NEXT(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

/*
 * Traversal start function
 */
node *STdoProcessSymbolTable(node *syntaxtree)
{
    DBUG_ENTER("STdoProcessSymbolTable");
    DBUG_PRINT("ST", ("STdoProcessSymbolTable"));

    info *info = MakeInfo(NULL);

    TRAVpush(TR_st);
    syntaxtree = TRAVdo(syntaxtree, info);
    TRAVpop();

    STdisplay(INFO_SYMBOL_TABLE(info), 0);

    FreeInfo(info);

    DBUG_RETURN(syntaxtree);
}