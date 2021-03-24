
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
#define PROGRAM_SYMBOLTABLE( n) ((n)->sons.N_program->SymbolTable)
extern node    *TBmakeProgram(node * Decls, node * SymbolTable);

/*****************************************************************************
 * macros and functions for N_symboltable
 *****************************************************************************/

#define SYMBOLTABLE_ENTRY( n) ((n)->sons.N_symboltable->Entry)
#define SYMBOLTABLE_PARENT( n) ((n)->attribs.N_symboltable->Parent)
#define SYMBOLTABLE_RETURNTYPE( n) ((n)->attribs.N_symboltable->ReturnType)
extern node    *TBmakeSymboltable(node * Entry);

/*****************************************************************************
 * macros and functions for N_symboltableentry
 *****************************************************************************/

#define SYMBOLTABLEENTRY_NEXT( n) ((n)->sons.N_symboltableentry->Next)
#define SYMBOLTABLEENTRY_TABLE( n) ((n)->sons.N_symboltableentry->Table)
#define SYMBOLTABLEENTRY_NAME( n) ((n)->attribs.N_symboltableentry->Name)
#define SYMBOLTABLEENTRY_TYPE( n) ((n)->attribs.N_symboltableentry->Type)
#define SYMBOLTABLEENTRY_OFFSET( n) ((n)->attribs.N_symboltableentry->Offset)
#define SYMBOLTABLEENTRY_DEPTH( n) ((n)->attribs.N_symboltableentry->Depth)
#define SYMBOLTABLEENTRY_PARAM( n) ((n)->attribs.N_symboltableentry->Param)
#define SYMBOLTABLEENTRY_LINK( n) ((n)->attribs.N_symboltableentry->Link)
extern node    *TBmakeSymboltableentry(char *Name, type Type, int Offset, int Depth, node * Link, node * Next, node * Table);

/*****************************************************************************
 * macros and functions for N_decls
 *****************************************************************************/

#define DECLS_DECL( n) ((n)->sons.N_decls->Decl)
#define DECLS_NEXT( n) ((n)->sons.N_decls->Next)
extern node    *TBmakeDecls(node * Decl, node * Next);

/*****************************************************************************
 * macros and functions for N_exprs
 *****************************************************************************/

#define EXPRS_EXPR( n) ((n)->sons.N_exprs->Expr)
#define EXPRS_NEXT( n) ((n)->sons.N_exprs->Next)
extern node    *TBmakeExprs(node * Expr, node * Next);

/*****************************************************************************
 * macros and functions for N_arrexpr
 *****************************************************************************/

#define ARREXPR_EXPRS( n) ((n)->sons.N_arrexpr->Exprs)
extern node    *TBmakeArrexpr(node * Exprs);

/*****************************************************************************
 * macros and functions for N_ids
 *****************************************************************************/

#define IDS_NEXT( n) ((n)->sons.N_ids->Next)
#define IDS_NAME( n) ((n)->attribs.N_ids->Name)
extern node    *TBmakeIds(char *Name, node * Next);

/*****************************************************************************
 * macros and functions for N_exprstmt
 *****************************************************************************/

#define EXPRSTMT_EXPR( n) ((n)->sons.N_exprstmt->Expr)
extern node    *TBmakeExprstmt(node * Expr);

/*****************************************************************************
 * macros and functions for N_return
 *****************************************************************************/

#define RETURN_EXPR( n) ((n)->sons.N_return->Expr)
extern node    *TBmakeReturn(node * Expr);

/*****************************************************************************
 * macros and functions for N_funcall
 *****************************************************************************/

#define FUNCALL_ARGS( n) ((n)->sons.N_funcall->Args)
#define FUNCALL_NAME( n) ((n)->attribs.N_funcall->Name)
#define FUNCALL_DECL( n) ((n)->attribs.N_funcall->Decl)
extern node    *TBmakeFuncall(char *Name, node * Decl, node * Args);

/*****************************************************************************
 * macros and functions for N_cast
 *****************************************************************************/

#define CAST_EXPR( n) ((n)->sons.N_cast->Expr)
#define CAST_TYPE( n) ((n)->attribs.N_cast->Type)
extern node    *TBmakeCast(type Type, node * Expr);

/*****************************************************************************
 * macros and functions for N_fundefs
 *****************************************************************************/

#define FUNDEFS_FUNDEF( n) ((n)->sons.N_fundefs->Fundef)
#define FUNDEFS_NEXT( n) ((n)->sons.N_fundefs->Next)
extern node    *TBmakeFundefs(node * Fundef, node * Next);

/*****************************************************************************
 * macros and functions for N_fundef
 *****************************************************************************/

#define FUNDEF_FUNBODY( n) ((n)->sons.N_fundef->FunBody)
#define FUNDEF_PARAMS( n) ((n)->sons.N_fundef->Params)
#define FUNDEF_TYPE( n) ((n)->attribs.N_fundef->Type)
#define FUNDEF_NAME( n) ((n)->attribs.N_fundef->Name)
#define FUNDEF_FLAGSTRUCTURE( n) ((n)->attribs.N_fundef->flags)
#define FUNDEF_ISEXPORT( n) ((n)->attribs.N_fundef->flags.IsExport)
#define FUNDEF_ISEXTERN( n) ((n)->attribs.N_fundef->flags.IsExtern)
extern node    *TBmakeFundef(type Type, char *Name, node * FunBody, node * Params);

/*****************************************************************************
 * macros and functions for N_funbody
 *****************************************************************************/

#define FUNBODY_VARDECLS( n) ((n)->sons.N_funbody->Vardecls)
#define FUNBODY_LOCALFUNDEFS( n) ((n)->sons.N_funbody->LocalFundefs)
#define FUNBODY_STMTS( n) ((n)->sons.N_funbody->Stmts)
extern node    *TBmakeFunbody(node * Vardecls, node * LocalFundefs, node * Stmts);

/*****************************************************************************
 * macros and functions for N_ternary
 *****************************************************************************/

#define TERNARY_EXPR( n) ((n)->sons.N_ternary->Expr)
#define TERNARY_THEN( n) ((n)->sons.N_ternary->Then)
#define TERNARY_ELSE( n) ((n)->sons.N_ternary->Else)
extern node    *TBmakeTernary(node * Expr, node * Then, node * Else);

/*****************************************************************************
 * macros and functions for N_ifelse
 *****************************************************************************/

#define IFELSE_COND( n) ((n)->sons.N_ifelse->Cond)
#define IFELSE_THEN( n) ((n)->sons.N_ifelse->Then)
#define IFELSE_ELSE( n) ((n)->sons.N_ifelse->Else)
extern node    *TBmakeIfelse(node * Cond, node * Then, node * Else);

/*****************************************************************************
 * macros and functions for N_while
 *****************************************************************************/

#define WHILE_COND( n) ((n)->sons.N_while->Cond)
#define WHILE_BLOCK( n) ((n)->sons.N_while->Block)
extern node    *TBmakeWhile(node * Cond, node * Block);

/*****************************************************************************
 * macros and functions for N_dowhile
 *****************************************************************************/

#define DOWHILE_COND( n) ((n)->sons.N_dowhile->Cond)
#define DOWHILE_BLOCK( n) ((n)->sons.N_dowhile->Block)
extern node    *TBmakeDowhile(node * Cond, node * Block);

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
 * macros and functions for N_globdecl
 *****************************************************************************/

#define GLOBDECL_DIMS( n) ((n)->sons.N_globdecl->Dims)
#define GLOBDECL_TYPE( n) ((n)->attribs.N_globdecl->Type)
#define GLOBDECL_NAME( n) ((n)->attribs.N_globdecl->Name)
extern node    *TBmakeGlobdecl(type Type, char *Name, node * Dims);

/*****************************************************************************
 * macros and functions for N_globdef
 *****************************************************************************/

#define GLOBDEF_DIMS( n) ((n)->sons.N_globdef->Dims)
#define GLOBDEF_INIT( n) ((n)->sons.N_globdef->Init)
#define GLOBDEF_TYPE( n) ((n)->attribs.N_globdef->Type)
#define GLOBDEF_NAME( n) ((n)->attribs.N_globdef->Name)
#define GLOBDEF_FLAGSTRUCTURE( n) ((n)->attribs.N_globdef->flags)
#define GLOBDEF_ISEXPORT( n) ((n)->attribs.N_globdef->flags.IsExport)
#define GLOBDEF_ISEXTERN( n) ((n)->attribs.N_globdef->flags.IsExtern)
extern node    *TBmakeGlobdef(type Type, char *Name, node * Dims, node * Init);

/*****************************************************************************
 * macros and functions for N_param
 *****************************************************************************/

#define PARAM_DIMS( n) ((n)->sons.N_param->Dims)
#define PARAM_NEXT( n) ((n)->sons.N_param->Next)
#define PARAM_NAME( n) ((n)->attribs.N_param->Name)
#define PARAM_TYPE( n) ((n)->attribs.N_param->Type)
extern node    *TBmakeParam(char *Name, type Type, node * Dims, node * Next);

/*****************************************************************************
 * macros and functions for N_vardecl
 *****************************************************************************/

#define VARDECL_DIMS( n) ((n)->sons.N_vardecl->Dims)
#define VARDECL_INIT( n) ((n)->sons.N_vardecl->Init)
#define VARDECL_NEXT( n) ((n)->sons.N_vardecl->Next)
#define VARDECL_NAME( n) ((n)->attribs.N_vardecl->Name)
#define VARDECL_TYPE( n) ((n)->attribs.N_vardecl->Type)
extern node    *TBmakeVardecl(char *Name, type Type, node * Dims, node * Init, node * Next);

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

#define VARLET_INDICES( n) ((n)->sons.N_varlet->Indices)
#define VARLET_NAME( n) ((n)->attribs.N_varlet->Name)
#define VARLET_DECL( n) ((n)->attribs.N_varlet->Decl)
extern node    *TBmakeVarlet(char *Name, node * Decl, node * Indices);

/*****************************************************************************
 * macros and functions for N_var
 *****************************************************************************/

#define VAR_INDICES( n) ((n)->sons.N_var->Indices)
#define VAR_NAME( n) ((n)->attribs.N_var->Name)
#define VAR_DECL( n) ((n)->attribs.N_var->Decl)
extern node    *TBmakeVar(char *Name, node * Decl, node * Indices);

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
 * macros and functions for N_error
 *****************************************************************************/

#define ERROR_NEXT( n) ((n)->sons.N_error->Next)
#define ERROR_MESSAGE( n) ((n)->attribs.N_error->message)
#define ERROR_ANYPHASE( n) ((n)->attribs.N_error->anyphase)
extern node    *TBmakeError(char *message, compiler_phase_t anyphase, node * Next);

#endif				/* _SAC_NODE_BASIC_H_ */
