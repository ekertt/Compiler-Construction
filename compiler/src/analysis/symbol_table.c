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

struct INFO {
  node *table;
  int params;
  int arguments;
};


/*
 * INFO macros
 */

#define INFO_SYMBOL_TABLE(n)  ((n)->table)
#define INFO_PARAMS(n)  ((n)->params)
#define INFO_ARGUMENTS(n)  ((n)->arguments)



/*
 * INFO functions
 */

static info *MakeInfo(node *parent)
{
  info *result;

  DBUG_ENTER( "MakeInfo");

  DBUG_RETURN( result);
}

static info *FreeInfo( info *info)
{
  DBUG_ENTER ("FreeInfo");

  info = MEMfree( info);

  DBUG_RETURN( info);
}

node *STprogram(node * arg_node, info * arg_info)
{
    DBUG_ENTER("STprogram");
    DBUG_PRINT ("ST", ("STprogram"));


    DBUG_RETURN( arg_node);
}

node *STglobdef(node * arg_node, info * arg_info)
{
    DBUG_ENTER("STglobdef");
    DBUG_PRINT ("ST", ("STglobdef"));

    DBUG_RETURN( arg_node);
}

node *STfundef(node * arg_node, info * arg_info)
{
    DBUG_ENTER("STfundef");
    DBUG_PRINT ("ST", ("STglobdef"));

    DBUG_RETURN( arg_node);
}

node *STparam(node * arg_node, info * arg_info)
{
    DBUG_ENTER("STparam");
    DBUG_PRINT ("ST", ("STparam"));

    DBUG_RETURN( arg_node);
}

node *STfuncall(node * arg_node, info * arg_info)
{
    DBUG_ENTER("STfuncall");
    DBUG_PRINT ("ST", ("STfuncall"));
   
    DBUG_RETURN( arg_node);
}

node *STexprs (node * arg_node, info * arg_info)
{
    DBUG_ENTER("STexprs");
    DBUG_PRINT ("STexprs", ("STexprs"));

    DBUG_RETURN( arg_node);
}

node *STvar(node * arg_node, info * arg_info)
{
    DBUG_ENTER("STvar");
    DBUG_PRINT ("ST", ("STvar"));

    DBUG_RETURN( arg_node);
}

node *STvardecl(node * arg_node, info * arg_info)
{
    DBUG_ENTER("STvardecl");
    DBUG_PRINT ("ST", ("STvardecl"));

    DBUG_RETURN( arg_node);
}

node *STvarlet(node * arg_node, info * arg_info)
{
    DBUG_ENTER("STvarlet");
    DBUG_PRINT ("ST", ("STvarlet"));

    DBUG_RETURN( arg_node);
}

/*
 * Traversal start function
 */
node *STdoProcessSymbolTable(node *syntaxtree) {
    DBUG_ENTER("STdoProcessSymbolTable");
    DBUG_PRINT ("ST", ("STdoProcessSymbolTable"));

    DBUG_RETURN(syntaxtree);
}