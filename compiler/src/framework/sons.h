
/**
 * @file sons.h
 *
 * Defines the NodesUnion and node structures.
 *
 * THIS FILE HAS BEEN GENERATED USING
 * $Id: sons.h.xsl 14593 2006-01-31 17:09:55Z cg $.
 * DO NOT EDIT THIS FILE AS MIGHT BE CHANGED IN A LATER VERSION.
 *
 * ALL CHANGES MADE TO THIS FILE WILL BE OVERWRITTEN!
 *
 */

#ifndef _SAC_SONS_H_
#define _SAC_SONS_H_

#include "types.h"


/******************************************************************************
 * For each node a structure of its sons is defined, named
 * SONS_<nodename>
 *****************************************************************************/
struct SONS_N_ASSIGN {
	node           *Let;
	node           *Expr;
};
struct SONS_N_BINOP {
	node           *Left;
	node           *Right;
};
struct SONS_N_BOOL {
};
struct SONS_N_DECLARATIONS {
	node           *Declaration;
	node           *Next;
};
struct SONS_N_DOWHILE {
	node           *Condition;
	node           *Block;
};
struct SONS_N_ERROR {
	node           *Next;
};
struct SONS_N_EXPRESSIONS {
	node           *Expr;
	node           *Next;
};
struct SONS_N_FLOAT {
};
struct SONS_N_FOR {
	node           *First;
	node           *Second;
	node           *Third;
	node           *Block;
};
struct SONS_N_FUNBODY {
	node           *Vardec;
	node           *LocalFundefs;
	node           *Stmts;
};
struct SONS_N_FUNDEC {
	node           *FunHeader;
};
struct SONS_N_FUNDEF {
	node           *FunBody;
	node           *FunHeader;
	node           *Params;
};
struct SONS_N_FUNDEFS {
	node           *FunDef;
	node           *Next;
};
struct SONS_N_FUNHEADER {
	node           *Param;
};
struct SONS_N_GLOBALDEC {
	node           *Ids;
};
struct SONS_N_GLOBALDEF {
	node           *Ids;
};
struct SONS_N_IDS {
	node           *Expr;
};
struct SONS_N_IFELSE {
	node           *Condition;
	node           *Then;
	node           *Else;
};
struct SONS_N_MONOP {
	node           *Operand;
};
struct SONS_N_NUM {
};
struct SONS_N_PARAM {
	node           *Id;
	node           *Next;
};
struct SONS_N_PROGRAM {
	node           *Declarations;
};
struct SONS_N_RETURN {
	node           *Expr;
};
struct SONS_N_STMTS {
	node           *Stmt;
	node           *Next;
};
struct SONS_N_SYMBOLTABLEENTRY {
};
struct SONS_N_VAR {
};
struct SONS_N_VARDEC {
	node           *Expressions;
	node           *Next;
};
struct SONS_N_VARLET {
};
struct SONS_N_WHILE {
	node           *Condition;
	node           *Block;
};
/*****************************************************************************
 * This union handles all different types of sons. Its members are
 * called N_nodename.
 ****************************************************************************/
struct SONUNION {
	struct SONS_N_ASSIGN *N_assign;
	struct SONS_N_BINOP *N_binop;
	struct SONS_N_BOOL *N_bool;
	struct SONS_N_DECLARATIONS *N_declarations;
	struct SONS_N_DOWHILE *N_dowhile;
	struct SONS_N_ERROR *N_error;
	struct SONS_N_EXPRESSIONS *N_expressions;
	struct SONS_N_FLOAT *N_float;
	struct SONS_N_FOR *N_for;
	struct SONS_N_FUNBODY *N_funbody;
	struct SONS_N_FUNDEC *N_fundec;
	struct SONS_N_FUNDEF *N_fundef;
	struct SONS_N_FUNDEFS *N_fundefs;
	struct SONS_N_FUNHEADER *N_funheader;
	struct SONS_N_GLOBALDEC *N_globaldec;
	struct SONS_N_GLOBALDEF *N_globaldef;
	struct SONS_N_IDS *N_ids;
	struct SONS_N_IFELSE *N_ifelse;
	struct SONS_N_MONOP *N_monop;
	struct SONS_N_NUM *N_num;
	struct SONS_N_PARAM *N_param;
	struct SONS_N_PROGRAM *N_program;
	struct SONS_N_RETURN *N_return;
	struct SONS_N_STMTS *N_stmts;
	struct SONS_N_SYMBOLTABLEENTRY *N_symboltableentry;
	struct SONS_N_VAR *N_var;
	struct SONS_N_VARDEC *N_vardec;
	struct SONS_N_VARLET *N_varlet;
	struct SONS_N_WHILE *N_while;
};
#endif				/* _SAC_SONS_H_ */
