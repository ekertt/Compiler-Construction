
/**
 * @file types_nodetype.h
 *
 * This file defines the nodetype node enumeration.
 *
 * THIS FILE HAS BEEN GENERATED USING
 * $Id: types_nodetype.h.xsl 14593 2006-01-31 17:09:55Z cg $.
 * DO NOT EDIT THIS FILE AS MIGHT BE CHANGED IN A LATER VERSION.
 *
 * ALL CHANGES MADE TO THIS FILE WILL BE OVERWRITTEN!
 *
 */

#ifndef _SAC_TYPES_NODETYPE_H_
#define _SAC_TYPES_NODETYPE_H_

#define MAX_NODES 32
typedef enum {
N_undefined = 0, N_program = 1, N_symboltable = 2, N_symboltableentry = 3, N_decls = 4, N_exprs = 5, N_ids = 6, N_exprstmt = 7, N_return = 8, N_funcall = 9, N_cast = 10, N_fundefs = 11, N_fundef = 12, N_funbody = 13, N_ternary = 14, N_ifelse = 15, N_while = 16, N_dowhile = 17, N_for = 18, N_globdecl = 19, N_globdef = 20, N_param = 21, N_vardecl = 22, N_stmts = 23, N_assign = 24, N_binop = 25, N_monop = 26, N_varlet = 27, N_var = 28, N_num = 29, N_float = 30, N_bool = 31, N_error = 32} nodetype;

#endif				/* _SAC_TYPES_NODETYPE_H_ */
