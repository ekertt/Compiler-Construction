
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

#define MAX_NODES 29
typedef enum {
N_undefined = 0, N_program = 1, N_decls = 2, N_fundec = 3, N_fundef = 4, N_fundefs = 5, N_funbody = 6, N_funheader = 7, N_params = 8, N_globdec = 9, N_globdef = 10, N_vardecls = 11, N_vardecl = 12, N_ifelse = 13, N_param = 14, N_while = 15, N_for = 16, N_dowhile = 17, N_return = 18, N_stmts = 19, N_assign = 20, N_binop = 21, N_monop = 22, N_varlet = 23, N_var = 24, N_num = 25, N_float = 26, N_bool = 27, N_symboltableentry = 28, N_error = 29} nodetype;

#endif				/* _SAC_TYPES_NODETYPE_H_ */
