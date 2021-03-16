
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


travtables_t	travtables = {
	/* TR_undefined */
	{&TRAVerror
	,&TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror, &TRAVerror}

	/* TR_prt */
	,{&TRAVerror, &PRTprogram, &PRTsymboltable, &PRTsymboltableentry, &PRTdecls, &PRTexprs, &PRTarrexpr, &PRTids, &PRTexprstmt, &PRTreturn, &PRTfuncall, &PRTcast, &PRTfundefs, &PRTfundef, &PRTfunbody, &PRTifelse, &PRTwhile, &PRTdowhile, &PRTfor, &PRTglobdecl, &PRTglobdef, &PRTparam, &PRTvardecl, &PRTstmts, &PRTassign, &PRTbinop, &PRTmonop, &PRTvarlet, &PRTvar, &PRTnum, &PRTfloat, &PRTbool, &PRTerror}

	/* TR_copy */
	,{&TRAVerror, &COPYprogram, &COPYsymboltable, &COPYsymboltableentry, &COPYdecls, &COPYexprs, &COPYarrexpr, &COPYids, &COPYexprstmt, &COPYreturn, &COPYfuncall, &COPYcast, &COPYfundefs, &COPYfundef, &COPYfunbody, &COPYifelse, &COPYwhile, &COPYdowhile, &COPYfor, &COPYglobdecl, &COPYglobdef, &COPYparam, &COPYvardecl, &COPYstmts, &COPYassign, &COPYbinop, &COPYmonop, &COPYvarlet, &COPYvar, &COPYnum, &COPYfloat, &COPYbool, &COPYerror}

	/* TR_free */
	,{&TRAVerror, &FREEprogram, &FREEsymboltable, &FREEsymboltableentry, &FREEdecls, &FREEexprs, &FREEarrexpr, &FREEids, &FREEexprstmt, &FREEreturn, &FREEfuncall, &FREEcast, &FREEfundefs, &FREEfundef, &FREEfunbody, &FREEifelse, &FREEwhile, &FREEdowhile, &FREEfor, &FREEglobdecl, &FREEglobdef, &FREEparam, &FREEvardecl, &FREEstmts, &FREEassign, &FREEbinop, &FREEmonop, &FREEvarlet, &FREEvar, &FREEnum, &FREEfloat, &FREEbool, &FREEerror}

	/* TR_chk */
	,{&TRAVerror, &CHKprogram, &CHKsymboltable, &CHKsymboltableentry, &CHKdecls, &CHKexprs, &CHKarrexpr, &CHKids, &CHKexprstmt, &CHKreturn, &CHKfuncall, &CHKcast, &CHKfundefs, &CHKfundef, &CHKfunbody, &CHKifelse, &CHKwhile, &CHKdowhile, &CHKfor, &CHKglobdecl, &CHKglobdef, &CHKparam, &CHKvardecl, &CHKstmts, &CHKassign, &CHKbinop, &CHKmonop, &CHKvarlet, &CHKvar, &CHKnum, &CHKfloat, &CHKbool, &CHKerror}

	/* TR_st */
	,{&TRAVerror, &STprogram, &TRAVsons, &TRAVsons, &TRAVsons, &STexprs, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &STfundef, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &STglobdef, &STparam, &STvardecl, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons, &STvarlet, &STvar, &TRAVsons, &TRAVsons, &TRAVsons, &TRAVsons}
};

preposttable_t	pretable = {
	NULL
	,NULL, NULL, NULL, NULL, NULL
};

preposttable_t	posttable = {
	NULL
	,NULL, NULL, NULL, NULL, NULL
};

const char     *travnames[6] = {
	"unknown"
	,"prt", "copy", "free", "chk", "st"
};
