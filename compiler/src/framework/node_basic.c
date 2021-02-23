
/**
 * @file node_basic.c
 *
 * Functions to allocate node structures
 *
 * THIS FILE HAS BEEN GENERATED USING
 * $Id: node_basic.c.xsl 14593 2006-01-31 17:09:55Z cg $.
 * DO NOT EDIT THIS FILE AS MIGHT BE CHANGED IN A LATER VERSION.
 *
 * ALL CHANGES MADE TO THIS FILE WILL BE OVERWRITTEN!
 *
 */

#include "node_basic.h"
#include "tree_basic.h"
#include "memory.h"
#include "dbug.h"
#include "globals.h"
#include "ctinfo.h"

static node    *
MakeEmptyNode()
{
	node           *result;

	DBUG_ENTER("MakeEmptyNode");

	result = (node *) MEMmalloc(sizeof(node));

	NODE_LINE(result) = global.line;
	NODE_COL(result) = global.col;

	DBUG_RETURN(result);
}



/*****************************************************************************
 * N_Program :
 *****************************************************************************/

node           *TBmakeProgram(node * Decls) {
	node           *this;
	DBUG_ENTER("TBmakeProgram");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_program;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_program = MEMmalloc(sizeof(struct SONS_N_PROGRAM));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_program = MEMmalloc(sizeof(struct ATTRIBS_N_PROGRAM));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_program;
	DBUG_PRINT("MAKE", ("assigning son Decls initial value: %s ", Decls));
	PROGRAM_DECLS(this) = Decls;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((PROGRAM_DECLS(this) != NULL) && (NODE_TYPE(PROGRAM_DECLS(this)) != N_decls)) {
		CTIwarn("Field Decls of node N_Program has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_Decls :
 *****************************************************************************/

node           *TBmakeDecls(node * Decl, node * Next) {
	node           *this;
	DBUG_ENTER("TBmakeDecls");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_decls;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_decls = MEMmalloc(sizeof(struct SONS_N_DECLS));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_decls = MEMmalloc(sizeof(struct ATTRIBS_N_DECLS));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_decls;
	DBUG_PRINT("MAKE", ("assigning son Decl initial value: %s ", Decl));
	DECLS_DECL(this) = Decl;
	DBUG_PRINT("MAKE", ("assigning son Next initial value: %s ", Next));
	DECLS_NEXT(this) = Next;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((DECLS_DECL(this) != NULL) && (NODE_TYPE(DECLS_DECL(this)) != N_globdef) && (NODE_TYPE(DECLS_DECL(this)) != N_globdec) && (NODE_TYPE(DECLS_DECL(this)) != N_fundef) && (NODE_TYPE(DECLS_DECL(this)) != N_fundec)) {
		CTIwarn("Field Decl of node N_Decls has non-allowed target node.");
	}
	if ((DECLS_NEXT(this) != NULL) && (NODE_TYPE(DECLS_NEXT(this)) != N_decls)) {
		CTIwarn("Field Next of node N_Decls has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_FunDec :
 *****************************************************************************/

node           *TBmakeFundec(node * FunHeader) {
	node           *this;
	DBUG_ENTER("TBmakeFundec");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_fundec;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_fundec = MEMmalloc(sizeof(struct SONS_N_FUNDEC));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_fundec = MEMmalloc(sizeof(struct ATTRIBS_N_FUNDEC));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_fundec;
	DBUG_PRINT("MAKE", ("assigning son FunHeader initial value: %s ", FunHeader));
	FUNDEC_FUNHEADER(this) = FunHeader;
	FUNDEC_ISEXTERN(this) = FALSE;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((FUNDEC_FUNHEADER(this) != NULL) && (NODE_TYPE(FUNDEC_FUNHEADER(this)) != N_funheader)) {
		CTIwarn("Field FunHeader of node N_FunDec has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_FunDef :
 *****************************************************************************/

node           *TBmakeFundef(node * FunHeader, node * FunBody) {
	node           *this;
	DBUG_ENTER("TBmakeFundef");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_fundef;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_fundef = MEMmalloc(sizeof(struct SONS_N_FUNDEF));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_fundef = MEMmalloc(sizeof(struct ATTRIBS_N_FUNDEF));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_fundef;
	DBUG_PRINT("MAKE", ("assigning son FunHeader initial value: %s ", FunHeader));
	FUNDEF_FUNHEADER(this) = FunHeader;
	DBUG_PRINT("MAKE", ("assigning son FunBody initial value: %s ", FunBody));
	FUNDEF_FUNBODY(this) = FunBody;
	FUNDEF_ISEXPORT(this) = FALSE;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((FUNDEF_FUNHEADER(this) != NULL) && (NODE_TYPE(FUNDEF_FUNHEADER(this)) != N_funheader)) {
		CTIwarn("Field FunHeader of node N_FunDef has non-allowed target node.");
	}
	if ((FUNDEF_FUNBODY(this) != NULL) && (NODE_TYPE(FUNDEF_FUNBODY(this)) != N_funbody)) {
		CTIwarn("Field FunBody of node N_FunDef has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_FunDefs :
 *****************************************************************************/

node           *TBmakeFundefs(node * Fundef, node * Next) {
	node           *this;
	DBUG_ENTER("TBmakeFundefs");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_fundefs;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_fundefs = MEMmalloc(sizeof(struct SONS_N_FUNDEFS));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_fundefs = MEMmalloc(sizeof(struct ATTRIBS_N_FUNDEFS));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_fundefs;
	DBUG_PRINT("MAKE", ("assigning son Fundef initial value: %s ", Fundef));
	FUNDEFS_FUNDEF(this) = Fundef;
	DBUG_PRINT("MAKE", ("assigning son Next initial value: %s ", Next));
	FUNDEFS_NEXT(this) = Next;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((FUNDEFS_FUNDEF(this) != NULL) && (NODE_TYPE(FUNDEFS_FUNDEF(this)) != N_fundef)) {
		CTIwarn("Field Fundef of node N_FunDefs has non-allowed target node.");
	}
	if ((FUNDEFS_NEXT(this) != NULL) && (NODE_TYPE(FUNDEFS_NEXT(this)) != N_fundefs)) {
		CTIwarn("Field Next of node N_FunDefs has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_FunBody :
 *****************************************************************************/

node           *TBmakeFunbody(node * Vardecls, node * Localfundefs, node * Stmts) {
	node           *this;
	DBUG_ENTER("TBmakeFunbody");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_funbody;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_funbody = MEMmalloc(sizeof(struct SONS_N_FUNBODY));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_funbody = MEMmalloc(sizeof(struct ATTRIBS_N_FUNBODY));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_funbody;
	DBUG_PRINT("MAKE", ("assigning son Vardecls initial value: %s ", Vardecls));
	FUNBODY_VARDECLS(this) = Vardecls;
	DBUG_PRINT("MAKE", ("assigning son Localfundefs initial value: %s ", Localfundefs));
	FUNBODY_LOCALFUNDEFS(this) = Localfundefs;
	DBUG_PRINT("MAKE", ("assigning son Stmts initial value: %s ", Stmts));
	FUNBODY_STMTS(this) = Stmts;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((FUNBODY_VARDECLS(this) != NULL) && (NODE_TYPE(FUNBODY_VARDECLS(this)) != N_vardecl)) {
		CTIwarn("Field Vardecls of node N_FunBody has non-allowed target node.");
	}
	if ((FUNBODY_LOCALFUNDEFS(this) != NULL) && (NODE_TYPE(FUNBODY_LOCALFUNDEFS(this)) != N_fundefs)) {
		CTIwarn("Field Localfundefs of node N_FunBody has non-allowed target node.");
	}
	if ((FUNBODY_STMTS(this) != NULL) && (NODE_TYPE(FUNBODY_STMTS(this)) != N_stmts)) {
		CTIwarn("Field Stmts of node N_FunBody has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_FunHeader :
 *****************************************************************************/

node           *TBmakeFunheader(node * Params) {
	node           *this;
	DBUG_ENTER("TBmakeFunheader");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_funheader;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_funheader = MEMmalloc(sizeof(struct SONS_N_FUNHEADER));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_funheader = MEMmalloc(sizeof(struct ATTRIBS_N_FUNHEADER));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_funheader;
	DBUG_PRINT("MAKE", ("assigning son Params initial value: %s ", Params));
	FUNHEADER_PARAMS(this) = Params;
	FUNHEADER_TYPE(this) = TY_unknown;
	FUNHEADER_NAME(this) = NULL;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((FUNHEADER_PARAMS(this) != NULL) && (NODE_TYPE(FUNHEADER_PARAMS(this)) != N_params)) {
		CTIwarn("Field Params of node N_FunHeader has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_Params :
 *****************************************************************************/

node           *TBmakeParams(char *Name, type Type, node * Param, node * Next){
	node           *this;
	DBUG_ENTER("TBmakeParams");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_params;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_params = MEMmalloc(sizeof(struct SONS_N_PARAMS));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_params = MEMmalloc(sizeof(struct ATTRIBS_N_PARAMS));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_params;
	DBUG_PRINT("MAKE", ("assigning son Param initial value: %s ", Param));
	PARAMS_PARAM(this) = Param;
	DBUG_PRINT("MAKE", ("assigning son Next initial value: %s ", Next));
	PARAMS_NEXT(this) = Next;
	PARAMS_NAME(this) = Name;
	PARAMS_TYPE(this) = Type;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((PARAMS_PARAM(this) != NULL) && (NODE_TYPE(PARAMS_PARAM(this)) != N_param)) {
		CTIwarn("Field Param of node N_Params has non-allowed target node.");
	}
	if ((PARAMS_NEXT(this) != NULL) && (NODE_TYPE(PARAMS_NEXT(this)) != N_params)) {
		CTIwarn("Field Next of node N_Params has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_GlobDec :
 *****************************************************************************/

node           *TBmakeGlobdec(char *Name, type Type){
	node           *this;
	DBUG_ENTER("TBmakeGlobdec");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_globdec;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_globdec = MEMmalloc(sizeof(struct SONS_N_GLOBDEC));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_globdec = MEMmalloc(sizeof(struct ATTRIBS_N_GLOBDEC));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_globdec;
	GLOBDEC_NAME(this) = Name;
	GLOBDEC_TYPE(this) = Type;
	GLOBDEC_ISEXTERN(this) = FALSE;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_GlobDef :
 *****************************************************************************/

node           *TBmakeGlobdef(char *Name, type Type, node * Expr){
	node           *this;
	DBUG_ENTER("TBmakeGlobdef");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_globdef;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_globdef = MEMmalloc(sizeof(struct SONS_N_GLOBDEF));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_globdef = MEMmalloc(sizeof(struct ATTRIBS_N_GLOBDEF));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_globdef;
	DBUG_PRINT("MAKE", ("assigning son Expr initial value: %s ", Expr));
	GLOBDEF_EXPR(this) = Expr;
	GLOBDEF_NAME(this) = Name;
	GLOBDEF_TYPE(this) = Type;
	GLOBDEF_ISEXPORT(this) = FALSE;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((GLOBDEF_EXPR(this) != NULL) && (NODE_TYPE(GLOBDEF_EXPR(this)) != N_binop) && (NODE_TYPE(GLOBDEF_EXPR(this)) != N_monop) && (NODE_TYPE(GLOBDEF_EXPR(this)) != N_var) && (NODE_TYPE(GLOBDEF_EXPR(this)) != N_num) && (NODE_TYPE(GLOBDEF_EXPR(this)) != N_float) && (NODE_TYPE(GLOBDEF_EXPR(this)) != N_bool)) {
		CTIwarn("Field Expr of node N_GlobDef has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_VarDecls :
 *****************************************************************************/

node           *TBmakeVardecls(node * VarDecl, node * Next) {
	node           *this;
	DBUG_ENTER("TBmakeVardecls");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_vardecls;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_vardecls = MEMmalloc(sizeof(struct SONS_N_VARDECLS));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_vardecls = MEMmalloc(sizeof(struct ATTRIBS_N_VARDECLS));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_vardecls;
	DBUG_PRINT("MAKE", ("assigning son VarDecl initial value: %s ", VarDecl));
	VARDECLS_VARDECL(this) = VarDecl;
	DBUG_PRINT("MAKE", ("assigning son Next initial value: %s ", Next));
	VARDECLS_NEXT(this) = Next;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((VARDECLS_VARDECL(this) != NULL) && (NODE_TYPE(VARDECLS_VARDECL(this)) != N_vardecl)) {
		CTIwarn("Field VarDecl of node N_VarDecls has non-allowed target node.");
	}
	if ((VARDECLS_NEXT(this) != NULL) && (NODE_TYPE(VARDECLS_NEXT(this)) != N_vardecls)) {
		CTIwarn("Field Next of node N_VarDecls has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_VarDecl :
 *****************************************************************************/

node           *TBmakeVardecl(char *Name, type Type){
	node           *this;
	DBUG_ENTER("TBmakeVardecl");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_vardecl;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_vardecl = MEMmalloc(sizeof(struct SONS_N_VARDECL));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_vardecl = MEMmalloc(sizeof(struct ATTRIBS_N_VARDECL));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_vardecl;
	VARDECL_NAME(this) = Name;
	VARDECL_TYPE(this) = Type;
	VARDECL_ISEXPORT(this) = FALSE;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_IfElse :
 *****************************************************************************/

node           *TBmakeIfelse(node * Cond, node * Then, node * Else) {
	node           *this;
	DBUG_ENTER("TBmakeIfelse");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_ifelse;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_ifelse = MEMmalloc(sizeof(struct SONS_N_IFELSE));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_ifelse = MEMmalloc(sizeof(struct ATTRIBS_N_IFELSE));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_ifelse;
	DBUG_PRINT("MAKE", ("assigning son Cond initial value: %s ", Cond));
	IFELSE_COND(this) = Cond;
	DBUG_PRINT("MAKE", ("assigning son Then initial value: %s ", Then));
	IFELSE_THEN(this) = Then;
	DBUG_PRINT("MAKE", ("assigning son Else initial value: %s ", Else));
	IFELSE_ELSE(this) = Else;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((IFELSE_COND(this) != NULL) && (NODE_TYPE(IFELSE_COND(this)) != N_binop) && (NODE_TYPE(IFELSE_COND(this)) != N_monop) && (NODE_TYPE(IFELSE_COND(this)) != N_var) && (NODE_TYPE(IFELSE_COND(this)) != N_num) && (NODE_TYPE(IFELSE_COND(this)) != N_float) && (NODE_TYPE(IFELSE_COND(this)) != N_bool)) {
		CTIwarn("Field Cond of node N_IfElse has non-allowed target node.");
	}
	if ((IFELSE_THEN(this) != NULL) && (NODE_TYPE(IFELSE_THEN(this)) != N_stmts)) {
		CTIwarn("Field Then of node N_IfElse has non-allowed target node.");
	}
	if ((IFELSE_ELSE(this) != NULL) && (NODE_TYPE(IFELSE_ELSE(this)) != N_stmts)) {
		CTIwarn("Field Else of node N_IfElse has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_Param :
 *****************************************************************************/

node           *TBmakeParam(type Type) {
	node           *this;
	DBUG_ENTER("TBmakeParam");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_param;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_param = MEMmalloc(sizeof(struct SONS_N_PARAM));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_param = MEMmalloc(sizeof(struct ATTRIBS_N_PARAM));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_param;
	PARAM_TYPE(this) = Type;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_While :
 *****************************************************************************/

node           *TBmakeWhile(node * Cond, node * Block) {
	node           *this;
	DBUG_ENTER("TBmakeWhile");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_while;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_while = MEMmalloc(sizeof(struct SONS_N_WHILE));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_while = MEMmalloc(sizeof(struct ATTRIBS_N_WHILE));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_while;
	DBUG_PRINT("MAKE", ("assigning son Cond initial value: %s ", Cond));
	WHILE_COND(this) = Cond;
	DBUG_PRINT("MAKE", ("assigning son Block initial value: %s ", Block));
	WHILE_BLOCK(this) = Block;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((WHILE_COND(this) != NULL) && (NODE_TYPE(WHILE_COND(this)) != N_binop) && (NODE_TYPE(WHILE_COND(this)) != N_monop) && (NODE_TYPE(WHILE_COND(this)) != N_var) && (NODE_TYPE(WHILE_COND(this)) != N_num) && (NODE_TYPE(WHILE_COND(this)) != N_float) && (NODE_TYPE(WHILE_COND(this)) != N_bool)) {
		CTIwarn("Field Cond of node N_While has non-allowed target node.");
	}
	if ((WHILE_BLOCK(this) != NULL) && (NODE_TYPE(WHILE_BLOCK(this)) != N_stmts)) {
		CTIwarn("Field Block of node N_While has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_For :
 *****************************************************************************/

node           *TBmakeFor(char *LoopVar, node * Start, node * Stop, node * Step, node * Block){
	node           *this;
	DBUG_ENTER("TBmakeFor");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_for;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_for = MEMmalloc(sizeof(struct SONS_N_FOR));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_for = MEMmalloc(sizeof(struct ATTRIBS_N_FOR));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_for;
	DBUG_PRINT("MAKE", ("assigning son Start initial value: %s ", Start));
	FOR_START(this) = Start;
	DBUG_PRINT("MAKE", ("assigning son Stop initial value: %s ", Stop));
	FOR_STOP(this) = Stop;
	DBUG_PRINT("MAKE", ("assigning son Step initial value: %s ", Step));
	FOR_STEP(this) = Step;
	DBUG_PRINT("MAKE", ("assigning son Block initial value: %s ", Block));
	FOR_BLOCK(this) = Block;
	FOR_LOOPVAR(this) = LoopVar;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((FOR_START(this) != NULL) && (NODE_TYPE(FOR_START(this)) != N_binop) && (NODE_TYPE(FOR_START(this)) != N_monop) && (NODE_TYPE(FOR_START(this)) != N_var) && (NODE_TYPE(FOR_START(this)) != N_num) && (NODE_TYPE(FOR_START(this)) != N_float) && (NODE_TYPE(FOR_START(this)) != N_bool)) {
		CTIwarn("Field Start of node N_For has non-allowed target node.");
	}
	if ((FOR_STOP(this) != NULL) && (NODE_TYPE(FOR_STOP(this)) != N_binop) && (NODE_TYPE(FOR_STOP(this)) != N_monop) && (NODE_TYPE(FOR_STOP(this)) != N_var) && (NODE_TYPE(FOR_STOP(this)) != N_num) && (NODE_TYPE(FOR_STOP(this)) != N_float) && (NODE_TYPE(FOR_STOP(this)) != N_bool)) {
		CTIwarn("Field Stop of node N_For has non-allowed target node.");
	}
	if ((FOR_STEP(this) != NULL) && (NODE_TYPE(FOR_STEP(this)) != N_binop) && (NODE_TYPE(FOR_STEP(this)) != N_monop) && (NODE_TYPE(FOR_STEP(this)) != N_var) && (NODE_TYPE(FOR_STEP(this)) != N_num) && (NODE_TYPE(FOR_STEP(this)) != N_float) && (NODE_TYPE(FOR_STEP(this)) != N_bool)) {
		CTIwarn("Field Step of node N_For has non-allowed target node.");
	}
	if ((FOR_BLOCK(this) != NULL) && (NODE_TYPE(FOR_BLOCK(this)) != N_stmts)) {
		CTIwarn("Field Block of node N_For has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_DoWhile :
 *****************************************************************************/

node           *TBmakeDowhile(node * Cond, node * Block) {
	node           *this;
	DBUG_ENTER("TBmakeDowhile");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_dowhile;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_dowhile = MEMmalloc(sizeof(struct SONS_N_DOWHILE));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_dowhile = MEMmalloc(sizeof(struct ATTRIBS_N_DOWHILE));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_dowhile;
	DBUG_PRINT("MAKE", ("assigning son Cond initial value: %s ", Cond));
	DOWHILE_COND(this) = Cond;
	DBUG_PRINT("MAKE", ("assigning son Block initial value: %s ", Block));
	DOWHILE_BLOCK(this) = Block;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((DOWHILE_COND(this) != NULL) && (NODE_TYPE(DOWHILE_COND(this)) != N_binop) && (NODE_TYPE(DOWHILE_COND(this)) != N_monop) && (NODE_TYPE(DOWHILE_COND(this)) != N_var) && (NODE_TYPE(DOWHILE_COND(this)) != N_num) && (NODE_TYPE(DOWHILE_COND(this)) != N_float) && (NODE_TYPE(DOWHILE_COND(this)) != N_bool)) {
		CTIwarn("Field Cond of node N_DoWhile has non-allowed target node.");
	}
	if ((DOWHILE_BLOCK(this) != NULL) && (NODE_TYPE(DOWHILE_BLOCK(this)) != N_stmts)) {
		CTIwarn("Field Block of node N_DoWhile has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_Return :
 *****************************************************************************/

node           *TBmakeReturn(node * Expr) {
	node           *this;
	DBUG_ENTER("TBmakeReturn");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_return;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_return = MEMmalloc(sizeof(struct SONS_N_RETURN));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_return = MEMmalloc(sizeof(struct ATTRIBS_N_RETURN));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_return;
	DBUG_PRINT("MAKE", ("assigning son Expr initial value: %s ", Expr));
	RETURN_EXPR(this) = Expr;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((RETURN_EXPR(this) != NULL) && (NODE_TYPE(RETURN_EXPR(this)) != N_binop) && (NODE_TYPE(RETURN_EXPR(this)) != N_monop) && (NODE_TYPE(RETURN_EXPR(this)) != N_var) && (NODE_TYPE(RETURN_EXPR(this)) != N_num) && (NODE_TYPE(RETURN_EXPR(this)) != N_float) && (NODE_TYPE(RETURN_EXPR(this)) != N_bool)) {
		CTIwarn("Field Expr of node N_Return has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_Stmts :
 *****************************************************************************/

node           *TBmakeStmts(node * Stmt, node * Next) {
	node           *this;
	DBUG_ENTER("TBmakeStmts");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_stmts;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_stmts = MEMmalloc(sizeof(struct SONS_N_STMTS));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_stmts = MEMmalloc(sizeof(struct ATTRIBS_N_STMTS));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_stmts;
	DBUG_PRINT("MAKE", ("assigning son Stmt initial value: %s ", Stmt));
	STMTS_STMT(this) = Stmt;
	DBUG_PRINT("MAKE", ("assigning son Next initial value: %s ", Next));
	STMTS_NEXT(this) = Next;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((STMTS_STMT(this) != NULL) && (NODE_TYPE(STMTS_STMT(this)) != N_assign) && (NODE_TYPE(STMTS_STMT(this)) != N_ifelse) && (NODE_TYPE(STMTS_STMT(this)) != N_while) && (NODE_TYPE(STMTS_STMT(this)) != N_dowhile) && (NODE_TYPE(STMTS_STMT(this)) != N_for) && (NODE_TYPE(STMTS_STMT(this)) != N_return)) {
		CTIwarn("Field Stmt of node N_Stmts has non-allowed target node.");
	}
	if ((STMTS_NEXT(this) != NULL) && (NODE_TYPE(STMTS_NEXT(this)) != N_stmts)) {
		CTIwarn("Field Next of node N_Stmts has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_Assign :
 *****************************************************************************/

node           *TBmakeAssign(node * Let, node * Expr) {
	node           *this;
	DBUG_ENTER("TBmakeAssign");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_assign;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_assign = MEMmalloc(sizeof(struct SONS_N_ASSIGN));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_assign = MEMmalloc(sizeof(struct ATTRIBS_N_ASSIGN));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_assign;
	DBUG_PRINT("MAKE", ("assigning son Let initial value: %s ", Let));
	ASSIGN_LET(this) = Let;
	DBUG_PRINT("MAKE", ("assigning son Expr initial value: %s ", Expr));
	ASSIGN_EXPR(this) = Expr;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((ASSIGN_LET(this) != NULL) && (NODE_TYPE(ASSIGN_LET(this)) != N_varlet)) {
		CTIwarn("Field Let of node N_Assign has non-allowed target node.");
	}
	if ((ASSIGN_EXPR(this) != NULL) && (NODE_TYPE(ASSIGN_EXPR(this)) != N_binop) && (NODE_TYPE(ASSIGN_EXPR(this)) != N_monop) && (NODE_TYPE(ASSIGN_EXPR(this)) != N_var) && (NODE_TYPE(ASSIGN_EXPR(this)) != N_num) && (NODE_TYPE(ASSIGN_EXPR(this)) != N_float) && (NODE_TYPE(ASSIGN_EXPR(this)) != N_bool)) {
		CTIwarn("Field Expr of node N_Assign has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_BinOp :
 *****************************************************************************/

node           *TBmakeBinop(binop Op, node * Left, node * Right) {
	node           *this;
	DBUG_ENTER("TBmakeBinop");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_binop;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_binop = MEMmalloc(sizeof(struct SONS_N_BINOP));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_binop = MEMmalloc(sizeof(struct ATTRIBS_N_BINOP));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_binop;
	DBUG_PRINT("MAKE", ("assigning son Left initial value: %s ", Left));
	BINOP_LEFT(this) = Left;
	DBUG_PRINT("MAKE", ("assigning son Right initial value: %s ", Right));
	BINOP_RIGHT(this) = Right;
	BINOP_OP(this) = Op;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((BINOP_LEFT(this) != NULL) && (NODE_TYPE(BINOP_LEFT(this)) != N_binop) && (NODE_TYPE(BINOP_LEFT(this)) != N_monop) && (NODE_TYPE(BINOP_LEFT(this)) != N_var) && (NODE_TYPE(BINOP_LEFT(this)) != N_num) && (NODE_TYPE(BINOP_LEFT(this)) != N_float) && (NODE_TYPE(BINOP_LEFT(this)) != N_bool)) {
		CTIwarn("Field Left of node N_BinOp has non-allowed target node.");
	}
	if ((BINOP_RIGHT(this) != NULL) && (NODE_TYPE(BINOP_RIGHT(this)) != N_binop) && (NODE_TYPE(BINOP_RIGHT(this)) != N_monop) && (NODE_TYPE(BINOP_RIGHT(this)) != N_var) && (NODE_TYPE(BINOP_RIGHT(this)) != N_num) && (NODE_TYPE(BINOP_RIGHT(this)) != N_float) && (NODE_TYPE(BINOP_RIGHT(this)) != N_bool)) {
		CTIwarn("Field Right of node N_BinOp has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_MonOp :
 *****************************************************************************/

node           *TBmakeMonop(monop Op, node * Operand) {
	node           *this;
	DBUG_ENTER("TBmakeMonop");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_monop;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_monop = MEMmalloc(sizeof(struct SONS_N_MONOP));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_monop = MEMmalloc(sizeof(struct ATTRIBS_N_MONOP));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_monop;
	DBUG_PRINT("MAKE", ("assigning son Operand initial value: %s ", Operand));
	MONOP_OPERAND(this) = Operand;
	MONOP_OP(this) = Op;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((MONOP_OPERAND(this) != NULL) && (NODE_TYPE(MONOP_OPERAND(this)) != N_binop) && (NODE_TYPE(MONOP_OPERAND(this)) != N_monop) && (NODE_TYPE(MONOP_OPERAND(this)) != N_var) && (NODE_TYPE(MONOP_OPERAND(this)) != N_num) && (NODE_TYPE(MONOP_OPERAND(this)) != N_float) && (NODE_TYPE(MONOP_OPERAND(this)) != N_bool)) {
		CTIwarn("Field Operand of node N_MonOp has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_VarLet :
 *****************************************************************************/

node           *TBmakeVarlet(char *Name){
	node           *this;
	DBUG_ENTER("TBmakeVarlet");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_varlet;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_varlet = MEMmalloc(sizeof(struct SONS_N_VARLET));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_varlet = MEMmalloc(sizeof(struct ATTRIBS_N_VARLET));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_varlet;
	VARLET_NAME(this) = Name;
	VARLET_DECL(this) = NULL;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_Var :
 *****************************************************************************/

node           *TBmakeVar(char *Name){
	node           *this;
	DBUG_ENTER("TBmakeVar");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_var;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_var = MEMmalloc(sizeof(struct SONS_N_VAR));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_var = MEMmalloc(sizeof(struct ATTRIBS_N_VAR));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_var;
	VAR_NAME(this) = Name;
	VAR_DECL(this) = NULL;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_Num :
 *****************************************************************************/

node           *TBmakeNum(int Value){
	node           *this;
	DBUG_ENTER("TBmakeNum");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_num;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_num = MEMmalloc(sizeof(struct SONS_N_NUM));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_num = MEMmalloc(sizeof(struct ATTRIBS_N_NUM));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_num;
	NUM_VALUE(this) = Value;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_Float :
 *****************************************************************************/

node           *TBmakeFloat(float Value){
	node           *this;
	DBUG_ENTER("TBmakeFloat");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_float;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_float = MEMmalloc(sizeof(struct SONS_N_FLOAT));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_float = MEMmalloc(sizeof(struct ATTRIBS_N_FLOAT));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_float;
	FLOAT_VALUE(this) = Value;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_Bool :
 *****************************************************************************/

node           *TBmakeBool(bool Value) {
	node           *this;
	DBUG_ENTER("TBmakeBool");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_bool;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_bool = MEMmalloc(sizeof(struct SONS_N_BOOL));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_bool = MEMmalloc(sizeof(struct ATTRIBS_N_BOOL));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_bool;
	BOOL_VALUE(this) = Value;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_SymbolTableEntry :
 *****************************************************************************/

node           *TBmakeSymboltableentry() {
	node           *this;
	DBUG_ENTER("TBmakeSymboltableentry");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_symboltableentry;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_symboltableentry = MEMmalloc(sizeof(struct SONS_N_SYMBOLTABLEENTRY));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_symboltableentry = MEMmalloc(sizeof(struct ATTRIBS_N_SYMBOLTABLEENTRY));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_symboltableentry;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}

/*****************************************************************************
 * N_Error :
 *****************************************************************************/

node           *TBmakeError(char *message, compiler_phase_t anyphase, node * Next){
	node           *this;
	DBUG_ENTER("TBmakeError");
	DBUG_PRINT("MAKE", ("allocating node structure"));
	this = MakeEmptyNode();
	NODE_TYPE(this) = N_error;
	DBUG_PRINT("MAKE", ("address: %s ", this));
	DBUG_PRINT("MAKE", ("allocating sons structure"));
	this->sons.N_error = MEMmalloc(sizeof(struct SONS_N_ERROR));
	DBUG_PRINT("MAKE", ("allocating attrib structure"));
	this->attribs.N_error = MEMmalloc(sizeof(struct ATTRIBS_N_ERROR));
	DBUG_PRINT("MAKE", ("setting node type"));
	NODE_TYPE(this) = N_error;
	DBUG_PRINT("MAKE", ("assigning son Next initial value: %s ", Next));
	ERROR_NEXT(this) = Next;
	ERROR_MESSAGE(this) = message;
	ERROR_ANYPHASE(this) = anyphase;
#ifndef DBUG_OFF
	DBUG_PRINT("MAKE", ("doing son target checks"));
	if ((ERROR_NEXT(this) != NULL) && (NODE_TYPE(ERROR_NEXT(this)) != N_error)) {
		CTIwarn("Field Next of node N_Error has non-allowed target node.");
	}
#endif				/* DBUG_OFF */
	DBUG_RETURN(this);
}
/* end of file */
