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

        // Define nodetypes for readability
        nodetype TYPEBINOPLEFT = NODE_TYPE( BINOP_LEFT( arg_node));
        nodetype TYPEBINOPRIGHT = NODE_TYPE( BINOP_RIGHT( arg_node));

        // Base case 
        if (!((TYPEBINOPLEFT == N_var)
            && (TYPEBINOPRIGHT == N_num))
            && 
            !((TYPEBINOPLEFT == N_num)
            && (TYPEBINOPRIGHT == N_var))
            &&
            !((TYPEBINOPLEFT == N_varlet)
            && (TYPEBINOPRIGHT == N_num))
            && 
            !((TYPEBINOPLEFT == N_num)
            && (TYPEBINOPRIGHT == N_varlet))) {

            DBUG_RETURN(arg_node);
        }

        // Check if BINOP left num and right var
        if ((TYPEBINOPLEFT == N_num)
        && (TYPEBINOPRIGHT == N_var)) {

            multiplicationNumber = NUM_VALUE( BINOP_LEFT( arg_node));
            anyVariable = VAR_NAME( BINOP_RIGHT( arg_node));
        }  
        
        // Check if BINOP left var and right num
        if ((TYPEBINOPLEFT == N_var)
        && (TYPEBINOPRIGHT == N_num)) {
            
            anyVariable = VAR_NAME( BINOP_LEFT( arg_node));
            multiplicationNumber = NUM_VALUE( BINOP_RIGHT( arg_node));
        }

        // Check if BINOP left num and right varlet
        if ((TYPEBINOPLEFT == N_num)
        && (TYPEBINOPRIGHT == N_varlet)) {

            multiplicationNumber = NUM_VALUE( BINOP_LEFT( arg_node));
            anyVariable = VARLET_NAME( BINOP_RIGHT( arg_node));
        }  
        
        // Check if BINOP left varlet and right num
        if ((TYPEBINOPLEFT == N_varlet)
        && (TYPEBINOPRIGHT == N_num)) {
            
            anyVariable = VARLET_NAME( BINOP_LEFT( arg_node));
            multiplicationNumber = NUM_VALUE( BINOP_RIGHT( arg_node));
        }

        if (multiplicationNumber > MINMULTIPLIER && (TYPEBINOPLEFT == N_var || TYPEBINOPRIGHT == N_var)) {
            
            // Make the top BINOP an add BINOP
            BINOP_OP(arg_node) = BO_add;

            // Put the variable in the right BINOP
            BINOP_RIGHT(arg_node) = TBmakeVar(STRcpy(anyVariable));

            // Make a new multiplication BINOP and add the variable and multiplication number
            BINOP_LEFT(arg_node) = TBmakeBinop(BO_mul, TBmakeVar(STRcpy(anyVariable)), TBmakeNum(multiplicationNumber - 1));
        } else if (TYPEBINOPLEFT == N_var || TYPEBINOPRIGHT == N_var) {

            // No multiplication needed make an add BINOP
            arg_node = TBmakeBinop(BO_add, TBmakeVar(STRcpy(anyVariable)), TBmakeVar(STRcpy(anyVariable)));
        }

        if (multiplicationNumber > MINMULTIPLIER && (TYPEBINOPLEFT == N_varlet || TYPEBINOPRIGHT == N_varlet)) {
            
            // Make the top BINOP an add BINOP
            BINOP_OP(arg_node) = BO_add;

            // Put the variable in the right BINOP
            BINOP_RIGHT(arg_node) = TBmakeVarlet(STRcpy(anyVariable));

            // Make a new multiplication BINOP and add the variable and multiplication number
            BINOP_LEFT(arg_node) = TBmakeBinop(BO_mul, TBmakeVarlet(STRcpy(anyVariable)), TBmakeNum(multiplicationNumber - 1));
        } else if (TYPEBINOPLEFT == N_varlet || TYPEBINOPRIGHT == N_varlet) {

            // No multiplication needed make an add BINOP
            arg_node = TBmakeBinop(BO_add, TBmakeVarlet(STRcpy(anyVariable)), TBmakeVarlet(STRcpy(anyVariable)));
        }
    } 

    /*
     * Continue to traverse the syntax tree
     */
    BINOP_LEFT(arg_node) = TRAVdo(BINOP_LEFT(arg_node), arg_info);
    BINOP_RIGHT(arg_node) = TRAVdo(BINOP_RIGHT(arg_node), arg_info);

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
