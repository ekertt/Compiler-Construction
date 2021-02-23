
/**
 * @file check.h
 *
 * Functions to check node structures
 *
 * THIS FILE HAS BEEN GENERATED USING
 * $Id: check.h.xsl 15657 2007-11-13 13:57:30Z cg $.
 * DO NOT EDIT THIS FILE. EDIT THE AST SPEC IN ast.xml INSTEAD!
 *
 * ALL CHANGES MADE TO THIS FILE WILL BE OVERWRITTEN!
 *
 */

#ifndef _SAC_CHECK_H_
#define _SAC_CHECK_H_

#include "types.h"

extern node    *CHKdoTreeCheck(node * syntax_tree);


extern node    *CHKassign(node * arg_node, info * arg_info);
extern node    *CHKbinop(node * arg_node, info * arg_info);
extern node    *CHKbool(node * arg_node, info * arg_info);
extern node    *CHKdecls(node * arg_node, info * arg_info);
extern node    *CHKdowhile(node * arg_node, info * arg_info);
extern node    *CHKerror(node * arg_node, info * arg_info);
extern node    *CHKfloat(node * arg_node, info * arg_info);
extern node    *CHKfor(node * arg_node, info * arg_info);
extern node    *CHKfunbody(node * arg_node, info * arg_info);
extern node    *CHKfundec(node * arg_node, info * arg_info);
extern node    *CHKfundef(node * arg_node, info * arg_info);
extern node    *CHKfundefs(node * arg_node, info * arg_info);
extern node    *CHKfunheader(node * arg_node, info * arg_info);
extern node    *CHKglobdec(node * arg_node, info * arg_info);
extern node    *CHKglobdef(node * arg_node, info * arg_info);
extern node    *CHKifelse(node * arg_node, info * arg_info);
extern node    *CHKmonop(node * arg_node, info * arg_info);
extern node    *CHKnum(node * arg_node, info * arg_info);
extern node    *CHKparam(node * arg_node, info * arg_info);
extern node    *CHKparams(node * arg_node, info * arg_info);
extern node    *CHKprogram(node * arg_node, info * arg_info);
extern node    *CHKreturn(node * arg_node, info * arg_info);
extern node    *CHKstmts(node * arg_node, info * arg_info);
extern node    *CHKsymboltableentry(node * arg_node, info * arg_info);
extern node    *CHKvar(node * arg_node, info * arg_info);
extern node    *CHKvardecl(node * arg_node, info * arg_info);
extern node    *CHKvardecls(node * arg_node, info * arg_info);
extern node    *CHKvarlet(node * arg_node, info * arg_info);
extern node    *CHKwhile(node * arg_node, info * arg_info);
extern node    *CHKglobdef(node * arg_node, info * arg_info);
extern node    *CHKglobdec(node * arg_node, info * arg_info);
extern node    *CHKfundef(node * arg_node, info * arg_info);
extern node    *CHKfundec(node * arg_node, info * arg_info);
extern node    *CHKbinop(node * arg_node, info * arg_info);
extern node    *CHKmonop(node * arg_node, info * arg_info);
extern node    *CHKvar(node * arg_node, info * arg_info);
extern node    *CHKnum(node * arg_node, info * arg_info);
extern node    *CHKfloat(node * arg_node, info * arg_info);
extern node    *CHKbool(node * arg_node, info * arg_info);
extern node    *CHKassign(node * arg_node, info * arg_info);
extern node    *CHKifelse(node * arg_node, info * arg_info);
extern node    *CHKwhile(node * arg_node, info * arg_info);
extern node    *CHKdowhile(node * arg_node, info * arg_info);
extern node    *CHKfor(node * arg_node, info * arg_info);
extern node    *CHKreturn(node * arg_node, info * arg_info);


#endif				/* _SAC_CHECK_H_ */
