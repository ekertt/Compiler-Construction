#ifndef _FOR_TO_WHILE_H_
#define _FOR_TO_WHILE_H_
#include "types.h"

extern node *FTWdoNormalizeForLoops(node *syntaxtree);

extern node *FTWfor (node * arg_node, info * arg_info);
extern node *FTWfunbody (node * arg_node, info * arg_info);
extern node *FTWstmts (node * arg_node, info * arg_info);
extern node *FTWvarlet(node * arg_node, info * arg_info);
extern node *FTWvar(node * arg_node, info * arg_info);

#endif