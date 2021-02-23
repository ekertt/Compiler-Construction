
/**
 * @file node_basic.h
 *
 * Functions to allocate node structures
 *
 * THIS FILE HAS BEEN GENERATED USING
 * $Id: node_basic.h.xsl 14593 2006-01-31 17:09:55Z cg $.
 * DO NOT EDIT THIS FILE AS MIGHT BE CHANGED IN A LATER VERSION.
 *
 * ALL CHANGES MADE TO THIS FILE WILL BE OVERWRITTEN!
 *
 */

#ifndef _SAC_NODE_BASIC_H_
#define _SAC_NODE_BASIC_H_

#include "types.h"


#define _SAC_AST_VERSION_ "0.9"


/*****************************************************************************
 * macros and functions for N_program
 *****************************************************************************/

#define PROGRAM_DECLS( n) ((n)->sons.N_program->Decls)
extern node    *TBmakeProgram(node * Decls);

/*****************************************************************************
 * macros and functions for N_decls
 *****************************************************************************/

#define DECLS_DECL( n) ((n)->sons.N_decls->Decl)
#define DECLS_NEXT( n) ((n)->sons.N_decls->Next)
extern node    *TBmakeDecls(node * Decl, node * Next);

/*****************************************************************************
 * macros and functions for N_fundec
 *****************************************************************************/

#define FUNDEC_FUNHEADER( n) ((n)->sons.N_fundec->FunHeader)
#define FUNDEC_FLAGSTRUCTURE( n) ((n)->attribs.N_fundec->flags)
#define FUNDEC_ISEXTERN( n) ((n)->attribs.N_fundec->flags.IsExtern)
extern node    *TBmakeFundec(node * FunHeader);

/*****************************************************************************
 * macros and functions for N_fundef
 *****************************************************************************/

#define FUNDEF_FUNHEADER( n) ((n)->sons.N_fundef->FunHeader)
#define FUNDEF_FUNBODY( n) ((n)->sons.N_fundef->FunBody)
#define FUNDEF_FLAGSTRUCTURE( n) ((n)->attribs.N_fundef->flags)
#define FUNDEF_ISEXPORT( n) ((n)->attribs.N_fundef->flags.IsExport)
extern node    *TBmakeFundef(node * FunHeader, node * FunBody);

/*****************************************************************************
 * macros and functions for N_fundefs
 *****************************************************************************/

#define FUNDEFS_FUNDEF( n) ((n)->sons.N_fundefs->Fundef)
#define FUNDEFS_NEXT( n) ((n)->sons.N_fundefs->Next)
extern node    *TBmakeFundefs(node * Fundef, node * Next);

/*****************************************************************************
 * macros and functions for N_funbody
 *****************************************************************************/

#define FUNBODY_VARDECLS( n) ((n)->sons.N_funbody->Vardecls)
#define FUNBODY_LOCALFUNDEFS( n) ((n)->sons.N_funbody->Localfundefs)
#define FUNBODY_STMTS( n) ((n)->sons.N_funbody->Stmts)
extern node    *TBmakeFunbody(node * Vardecls, node * Localfundefs, node * Stmts);

/*****************************************************************************
 * macros and functions for N_funheader
 *****************************************************************************/

#define FUNHEADER_PARAMS( n) ((n)->sons.N_funheader->Params)
#define FUNHEADER_TYPE( n) ((n)->attribs.N_funheader->Type)
#define FUNHEADER_NAME( n) ((n)->attribs.N_funheader->Name)
extern node    *TBmakeFunheader(node * Params);

/*****************************************************************************
 * macros and functions for N_params
 *****************************************************************************/

#define PARAMS_PARAM( n) ((n)->sons.N_params->Param)
#define PARAMS_NEXT( n) ((n)->sons.N_params->Next)
#define PARAMS_NAME( n) ((n)->attribs.N_params->Name)
#define PARAMS_TYPE( n) ((n)->attribs.N_params->Type)
extern node    *TBmakeParams(char *Name, type Type, node * Param, node * Next);

/*****************************************************************************
 * macros and functions for N_globdec
 *****************************************************************************/

#define GLOBDEC_NAME( n) ((n)->attribs.N_globdec->Name)
#define GLOBDEC_TYPE( n) ((n)->attribs.N_globdec->Type)
#define GLOBDEC_FLAGSTRUCTURE( n) ((n)->attribs.N_globdec->flags)
#define GLOBDEC_ISEXTERN( n) ((n)->attribs.N_globdec->flags.IsExtern)
extern node    *TBmakeGlobdec(char *Name, type Type);

/*****************************************************************************
 * macros and functions for N_globdef
 *****************************************************************************/

#define GLOBDEF_EXPR( n) ((n)->sons.N_globdef->Expr)
#define GLOBDEF_NAME( n) ((n)->attribs.N_globdef->Name)
#define GLOBDEF_TYPE( n) ((n)->attribs.N_globdef->Type)
#define GLOBDEF_FLAGSTRUCTURE( n) ((n)->attribs.N_globdef->flags)
#define GLOBDEF_ISEXPORT( n) ((n)->attribs.N_globdef->flags.IsExport)
extern node    *TBmakeGlobdef(char *Name, type Type, node * Expr);

/*****************************************************************************
 * macros and functions for N_vardecls
 *****************************************************************************/

#define VARDECLS_VARDECL( n) ((n)->sons.N_vardecls->VarDecl)
#define VARDECLS_NEXT( n) ((n)->sons.N_vardecls->Next)
extern node    *TBmakeVardecls(node * VarDecl, node * Next);

/*****************************************************************************
 * macros and functions for N_vardecl
 *****************************************************************************/

#define VARDECL_NAME( n) ((n)->attribs.N_vardecl->Name)
#define VARDECL_TYPE( n) ((n)->attribs.N_vardecl->Type)
#define VARDECL_FLAGSTRUCTURE( n) ((n)->attribs.N_vardecl->flags)
#define VARDECL_ISEXPORT( n) ((n)->attribs.N_vardecl->flags.IsExport)
extern node    *TBmakeVardecl(char *Name, type Type);

/*****************************************************************************
 * macros and functions for N_ifelse
 *****************************************************************************/

#define IFELSE_COND( n) ((n)->sons.N_ifelse->Cond)
#define IFELSE_THEN( n) ((n)->sons.N_ifelse->Then)
#define IFELSE_ELSE( n) ((n)->sons.N_ifelse->Else)
extern node    *TBmakeIfelse(node * Cond, node * Then, node * Else);

/*****************************************************************************
 * macros and functions for N_param
 *****************************************************************************/

#define PARAM_TYPE( n) ((n)->attribs.N_param->Type)
extern node    *TBmakeParam(type Type);

/*****************************************************************************
 * macros and functions for N_while
 *****************************************************************************/

#define WHILE_COND( n) ((n)->sons.N_while->Cond)
#define WHILE_BLOCK( n) ((n)->sons.N_while->Block)
extern node    *TBmakeWhile(node * Cond, node * Block);

/*****************************************************************************
 * macros and functions for N_for
 *****************************************************************************/

#define FOR_START( n) ((n)->sons.N_for->Start)
#define FOR_STOP( n) ((n)->sons.N_for->Stop)
#define FOR_STEP( n) ((n)->sons.N_for->Step)
#define FOR_BLOCK( n) ((n)->sons.N_for->Block)
#define FOR_LOOPVAR( n) ((n)->attribs.N_for->LoopVar)
extern node    *TBmakeFor(char *LoopVar, node * Start, node * Stop, node * Step, node * Block);

/*****************************************************************************
 * macros and functions for N_dowhile
 *****************************************************************************/

#define DOWHILE_COND( n) ((n)->sons.N_dowhile->Cond)
#define DOWHILE_BLOCK( n) ((n)->sons.N_dowhile->Block)
extern node    *TBmakeDowhile(node * Cond, node * Block);

/*****************************************************************************
 * macros and functions for N_return
 *****************************************************************************/

#define RETURN_EXPR( n) ((n)->sons.N_return->Expr)
extern node    *TBmakeReturn(node * Expr);

/*****************************************************************************
 * macros and functions for N_stmts
 *****************************************************************************/

#define STMTS_STMT( n) ((n)->sons.N_stmts->Stmt)
#define STMTS_NEXT( n) ((n)->sons.N_stmts->Next)
extern node    *TBmakeStmts(node * Stmt, node * Next);

/*****************************************************************************
 * macros and functions for N_assign
 *****************************************************************************/

#define ASSIGN_LET( n) ((n)->sons.N_assign->Let)
#define ASSIGN_EXPR( n) ((n)->sons.N_assign->Expr)
extern node    *TBmakeAssign(node * Let, node * Expr);

/*****************************************************************************
 * macros and functions for N_binop
 *****************************************************************************/

#define BINOP_LEFT( n) ((n)->sons.N_binop->Left)
#define BINOP_RIGHT( n) ((n)->sons.N_binop->Right)
#define BINOP_OP( n) ((n)->attribs.N_binop->Op)
extern node    *TBmakeBinop(binop Op, node * Left, node * Right);

/*****************************************************************************
 * macros and functions for N_monop
 *****************************************************************************/

#define MONOP_OPERAND( n) ((n)->sons.N_monop->Operand)
#define MONOP_OP( n) ((n)->attribs.N_monop->Op)
extern node    *TBmakeMonop(monop Op, node * Operand);

/*****************************************************************************
 * macros and functions for N_varlet
 *****************************************************************************/

#define VARLET_NAME( n) ((n)->attribs.N_varlet->Name)
#define VARLET_DECL( n) ((n)->attribs.N_varlet->Decl)
extern node    *TBmakeVarlet(char *Name);

/*****************************************************************************
 * macros and functions for N_var
 *****************************************************************************/

#define VAR_NAME( n) ((n)->attribs.N_var->Name)
#define VAR_DECL( n) ((n)->attribs.N_var->Decl)
extern node    *TBmakeVar(char *Name);

/*****************************************************************************
 * macros and functions for N_num
 *****************************************************************************/

#define NUM_VALUE( n) ((n)->attribs.N_num->Value)
extern node    *TBmakeNum(int Value);

/*****************************************************************************
 * macros and functions for N_float
 *****************************************************************************/

#define FLOAT_VALUE( n) ((n)->attribs.N_float->Value)
extern node    *TBmakeFloat(float Value);

/*****************************************************************************
 * macros and functions for N_bool
 *****************************************************************************/

#define BOOL_VALUE( n) ((n)->attribs.N_bool->Value)
extern node    *TBmakeBool(bool Value);

/*****************************************************************************
 * macros and functions for N_symboltableentry
 *****************************************************************************/

extern node    *TBmakeSymboltableentry();

/*****************************************************************************
 * macros and functions for N_error
 *****************************************************************************/

#define ERROR_NEXT( n) ((n)->sons.N_error->Next)
#define ERROR_MESSAGE( n) ((n)->attribs.N_error->message)
#define ERROR_ANYPHASE( n) ((n)->attribs.N_error->anyphase)
extern node    *TBmakeError(char *message, compiler_phase_t anyphase, node * Next);

#endif				/* _SAC_NODE_BASIC_H_ */
