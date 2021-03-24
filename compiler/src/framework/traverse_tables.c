
/**
 * @file traverse_tables.c
 *
 * This file defines the function tables for traversal.
 *
 * THIS FILE HAS BEEN GENERATED USING
 * $Id: traverse_tables.c.xsl 14593 2006-01-31 17:09:55Z cg $.
 * DO NOT EDIT THIS FILE AS MIGHT BE CHANGED IN A LATER VERSION.
 *
 * ALL CHANGES MADE TO THIS FILE WILL BE OVERWRITTEN!
 *
 */

#include "traverse_tables.h"
#include "traverse_helper.h"
#include "print.h"
#include "copy_node.h"
#include "free_node.h"
#include "check.h"
#include "symbol_table.h"
#include "change_var_init_to_regular.h"
#include "type_check.h"
#include "compiling_boolean_dis_and_conjunction.h"
#include "transform_cast_expr.h"


travtables_t	travtables = {
	/* TR_undefined */
	{&TRAVerror
	,&TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror}

	/* TR_prt */
	,{&TRAVerror, &PRTprogram, &PRTsymboltable, &PRTsymboltableentry, &PRTdecls, &PRTexprs, &PRTarrexpr, &PRTids, &PRTexprstmt, &PRTreturn, &PRTfuncall, &PRTcast, &PRTfundefs, &PRTfundef, &PRTfunbody, &PRTternary, &PRTifelse, &PRTwhile, &PRTdowhile, &PRTfor, &PRTglobdecl, &PRTglobdef, &PRTparam, &PRTvardecl, &PRTstmts, &PRTassign, &PRTbinop, &PRTmonop, &PRTvarlet, &PRTvar, &PRTnum, &PRTfloat, &PRTbool, &PRTerror}

	/* TR_copy */
	,{&TRAVerror, &COPYprogram, &COPYsymboltable, &COPYsymboltableentry, &COPYdecls, &COPYexprs, &COPYarrexpr, &COPYids, &COPYexprstmt, &COPYreturn, &COPYfuncall, &COPYcast, &COPYfundefs, &COPYfundef, &COPYfunbody, &COPYternary, &COPYifelse, &COPYwhile, &COPYdowhile, &COPYfor, &COPYglobdecl, &COPYglobdef, &COPYparam, &COPYvardecl, &COPYstmts, &COPYassign, &COPYbinop, &COPYmonop, &COPYvarlet, &COPYvar, &COPYnum, &COPYfloat, &COPYbool, &COPYerror}

	/* TR_free */
	,{&TRAVerror, &FREEprogram, &FREEsymboltable, &FREEsymboltableentry, &FREEdecls, &FREEexprs, &FREEarrexpr, &FREEids, &FREEexprstmt, &FREEreturn, &FREEfuncall, &FREEcast, &FREEfundefs, &FREEfundef, &FREEfunbody, &FREEternary, &FREEifelse, &FREEwhile, &FREEdowhile, &FREEfor, &FREEglobdecl, &FREEglobdef, &FREEparam, &FREEvardecl, &FREEstmts, &FREEassign, &FREEbinop, &FREEmonop, &FREEvarlet, &FREEvar, &FREEnum, &FREEfloat, &FREEbool, &FREEerror}

	/* TR_chk */
	,{&TRAVerror, &CHKprogram, &CHKsymboltable, &CHKsymboltableentry, &CHKdecls, &CHKexprs, &CHKarrexpr, &CHKids, &CHKexprstmt, &CHKreturn, &CHKfuncall, &CHKcast, &CHKfundefs, &CHKfundef, &CHKfunbody, &CHKternary, &CHKifelse, &CHKwhile, &CHKdowhile, &CHKfor, &CHKglobdecl, &CHKglobdef, &CHKparam, &CHKvardecl, &CHKstmts, &CHKassign, &CHKbinop, &CHKmonop, &CHKvarlet, &CHKvar, &CHKnum, &CHKfloat, &CHKbool, &CHKerror}

	/* TR_st */
	,{&TRAVerror, &STprogram, &TRAVsons, &TRAVsons, &TRAVsons, &STexprs, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &STfuncall, &TRAVsons, &TRAVsons, &STfundef, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &STglobdef, &STparam, &STvardecl, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &STvarlet, &STvar, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons}

	/* TR_ci */
	,{&TRAVerror, &CIprogram, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &CIfunbody, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &CIglobdef, &TRAVsons, &CIvardecl, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons}

	/* TR_tc */
	,{&TRAVerror, &TCprogram, &TRAVsons, &TRAVsons, &TRAVsons, &TCexprs, &TRAVsons, &TRAVsons, &TRAVsons, &TCreturn, &TCfuncall, &TCcast, &TRAVsons, &TCfundef, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TCassign, &TCbinop, &TCmonop, &TRAVsons, &TCvar, &TCnum, &TCfloat, &TCbool, &TRAVsons}

	/* TR_cb */
	,{&TRAVerror, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &CBbinop, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons}

	/* TR_tce */
	,{&TRAVerror, &TCEprogram, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons}
};

preposttable_t	pretable = {
	NULL
	,NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

preposttable_t	posttable = {
	NULL
	,NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

const char     *travnames[10] = {
	"unknown"
	,"prt", "copy", "free", "chk", "st", "ci", "tc", "cb", "tce"
};
