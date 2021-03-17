#ifndef _CHANGE_VAR_INIT_TO_REGULAR_H_
#define _CHANGE_VAR_INIT_TO_REGULAR_H_
#include "types.h"

extern node *CIprogram(node *arg_node, info *arg_info);
extern node *CIglobdef(node *arg_node, info *arg_info);
extern node *CIvardecl(node *arg_node, info *arg_info);
extern node *CIfunbody(node *arg_node, info *arg_info);
void helper(node *arg_node, info *arg_info, node *assign, int type);

extern node *CIdoChangeVariableInitToRegular(node *syntaxtree);

#endif