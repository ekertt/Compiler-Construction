/*****************************************************************************
 *
 * Module: strength_reduction
 *
 * Prefix: SR
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

#include "memory.h"
#include "free.h"
#include "str.h"


/*
 * Traversal functions
 */

node *SRbinop( node *arg_node, info *arg_info)
{

    DBUG_ENTER("SRbinop");
    
    // The number used for multiplication
    int multiplicationNumber;
    // Minimal multiplication number
    int MINMULTIPLIER = 2;
    // The variable that is being multiplied
    char *anyVariable;

    if (BINOP_OP( arg_node) == BO_mul) {

        // Base case 
        if (!((NODE_TYPE( BINOP_LEFT( arg_node)) == N_var)
            && (NODE_TYPE( BINOP_RIGHT( arg_node)) == N_num))
            && !((NODE_TYPE( BINOP_LEFT( arg_node)) == N_num)
            && (NODE_TYPE( BINOP_RIGHT( arg_node)) == N_var))) {

            DBUG_RETURN(arg_node);
        }

        // Check if BINOP left num and right var
        if ((NODE_TYPE( BINOP_LEFT( arg_node)) == N_num)
        && (NODE_TYPE( BINOP_RIGHT( arg_node)) == N_var)) {

            multiplicationNumber = NUM_VALUE( BINOP_LEFT( arg_node));
            anyVariable = VAR_NAME( BINOP_RIGHT( arg_node));
        }  
        
        // Check if BINOP left var and right num
        if ((NODE_TYPE( BINOP_LEFT( arg_node)) == N_var)
        && (NODE_TYPE( BINOP_RIGHT( arg_node)) == N_num)) {
            
            multiplicationNumber = NUM_VALUE( BINOP_RIGHT( arg_node));
            anyVariable = VAR_NAME( BINOP_LEFT( arg_node));
        }

        if (multiplicationNumber > MINMULTIPLIER) {
            
            // Make the top BINOP an add BINOP
            BINOP_OP(arg_node) = BO_add;

            // Put the variable in the right BINOP
            BINOP_RIGHT(arg_node) = TBmakeVar(STRcpy(anyVariable));

            // Make a new multiplication BINOP and add the variable and multiplication
            BINOP_LEFT(arg_node) = TBmakeBinop(BO_mul, TBmakeVar(STRcpy(anyVariable)), TBmakeNum(multiplicationNumber - 1));
        } else {

            // No multiplication needed 
            arg_node = TBmakeBinop(BO_add, TBmakeVar(STRcpy(anyVariable)), TBmakeVar(STRcpy(anyVariable)));
        }
        
    }

    // Continue to traverse the abstract syntax tree
    BINOP_RIGHT(arg_node) = TRAVdo(BINOP_RIGHT(arg_node), arg_info);
    BINOP_LEFT(arg_node) = TRAVdo(BINOP_LEFT(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

/*
 * Traversal start function
 */

node *SRdoStrengthReduction( node *syntaxtree)
{
  DBUG_ENTER("SRdoStrengthReduction");

  TRAVpush(TR_sr);   // Push traversal "sr" as defined in ast.xml

  syntaxtree = TRAVdo( syntaxtree, NULL);   // Initiate ast traversal

  TRAVpop();          // Pop current traversal

  DBUG_RETURN( syntaxtree);
}
