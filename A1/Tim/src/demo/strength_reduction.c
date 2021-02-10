/*****************************************************************************
 *
 * Module: rename_identifiers
 *
 * Prefix: RI
 *
 * Description:
 *
 * This module implements a demo traversal of the abstract syntax tree that 
 * prefixes any variable found by two underscores.
 *
 *****************************************************************************/

#include "strength_reduction.h"

#include "types.h"
#include "tree_basic.h"
#include "traverse.h"
#include "dbug.h"

#include "str.h"
#include "memory.h"
#include "ctinfo.h"
#include "free.h"

#include "stdio.h"

/*
 * Traversal functions
 */

/*
 * Traversal function Binop
 * Strenght reduction: 4K = k + k + k + k
 */
node *SRbinop(node *arg_node, info *arg_info)
{
  DBUG_ENTER("SRbinop");

  // check if binop is multiplier
  if (BINOP_OP(arg_node) == BO_mul)
  {
    // create variables
    int NUM;
    char *VAR;

    // check if left node is num and right node is var
    if ((NODE_TYPE(BINOP_LEFT(arg_node)) == N_num) && (NODE_TYPE(BINOP_RIGHT(arg_node)) == N_var))
    {
      NUM = NUM_VALUE(BINOP_LEFT(arg_node));
      VAR = VAR_NAME(BINOP_RIGHT(arg_node));
    }
    // check if left node is var and right node is num
    else if ((NODE_TYPE(BINOP_RIGHT(arg_node)) == N_num) && (NODE_TYPE(BINOP_LEFT(arg_node)) == N_var))
    {
      NUM = NUM_VALUE(BINOP_RIGHT(arg_node));
      VAR = VAR_NAME(BINOP_LEFT(arg_node));
    }
    else
    {
      DBUG_RETURN(arg_node);
    }

    // if num equals 2 end of road is there, replace the numbers wit vars
    if (NUM == 2)
    {
      arg_node = TBmakeBinop(BO_add, TBmakeVar(STRcpy(VAR)), TBmakeVar(STRcpy(VAR)));
    }
    // if num doesn't equal 2 place the left node num -1 and the right node with a var
    else
    {
      BINOP_OP(arg_node) = BO_add;
      BINOP_RIGHT(arg_node) = TBmakeVar(STRcpy(VAR));

      BINOP_LEFT(arg_node) = TBmakeBinop(BO_mul, TBmakeNum(NUM - 1), TBmakeVar(STRcpy(VAR)));
    }
  }

  /*
   * Extremely important:
   *  we must continue to traverse the abstract syntax tree !!
   */
  BINOP_RIGHT(arg_node) = TRAVdo(BINOP_RIGHT(arg_node), arg_info);
  BINOP_LEFT(arg_node) = TRAVdo(BINOP_LEFT(arg_node), arg_info);

  DBUG_RETURN(arg_node);
}

/*
 * Traversal start function
 */

node *SRdoStrenghtReduction(node *syntaxtree)
{
  DBUG_ENTER("SRdoStrenghtReduction");
  TRAVpush(TR_sr);
  syntaxtree = TRAVdo(syntaxtree, NULL);
  TRAVpop();

  DBUG_RETURN(syntaxtree);
}