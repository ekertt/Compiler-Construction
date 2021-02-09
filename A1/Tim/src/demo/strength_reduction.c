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

node *SRbinop(node *arg_node, info *arg_info)
{
  DBUG_ENTER("SRbinop");

  /*
   * Extremely important:
   *  we must continue to traverse the abstract syntax tree !!
   */
  BINOP_RIGHT(arg_node) = TRAVdo(BINOP_RIGHT(arg_node), arg_info);
  BINOP_LEFT(arg_node) = TRAVdo(BINOP_LEFT(arg_node), arg_info);

  if (BINOP_OP(arg_node) == BO_mul)
  {
    if ((NODE_TYPE(BINOP_LEFT(arg_node)) == N_num) && (NODE_TYPE(BINOP_RIGHT(arg_node)) == N_num))
    {
      BINOP_OP(arg_node) = BO_add;
      int MULTIPLIER = NUM_VALUE(BINOP_LEFT(arg_node));
      int VAR = NUM_VALUE(BINOP_RIGHT(arg_node));

      for (int i = 0; i < MULTIPLIER; i++)
      {
        printf("%d", i);
        node *node = TBmakeBinop(BO_mul, TBmakeNum(i), TBmakeNum(MULTIPLIER));
        
        BINOP_LEFT(arg_node) = node;
      }
    }
    else
    {
      DBUG_RETURN(arg_node);
    }
  }

  DBUG_RETURN(arg_node);
}

// node *OSbinop (node *arg_node, info *arg_info)
// {
//   DBUG_ENTER("OSbinop");

//   BINOP_LEFT( arg_node) = TRAVdo( BINOP_LEFT( arg_node), arg_info);
//   BINOP_RIGHT( arg_node) = TRAVdo( BINOP_RIGHT( arg_node), arg_info);

//   if (BINOP_OP( arg_node) == BO_sub) {
//     if ((NODE_TYPE( BINOP_LEFT( arg_node)) == N_var)
// 	&& (NODE_TYPE( BINOP_RIGHT( arg_node)) == N_var)
// 	&& STReq( VAR_NAME( BINOP_LEFT( arg_node)), VAR_NAME( BINOP_RIGHT( arg_node)))) {
//       arg_node = FREEdoFreeTree( arg_node);
//       arg_node = TBmakeNum( 0);
//     }
//     else if  ((NODE_TYPE( BINOP_LEFT( arg_node)) == N_num)
// 	      && (NODE_TYPE( BINOP_RIGHT( arg_node)) == N_num)
// 	      && (NUM_VALUE( BINOP_LEFT( arg_node)) == NUM_VALUE( BINOP_RIGHT( arg_node)))) {
//       arg_node = FREEdoFreeTree( arg_node);
//       arg_node = TBmakeNum( 0);
//     }
//   }

//   DBUG_RETURN( arg_node);
// }

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