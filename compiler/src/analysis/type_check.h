#ifndef _TYPE_CHECK_H_
#define _TYPE_CHECK_H_
#include "types.h"

extern node *TCprogram(node *arg_node, info *arg_info);
extern node *TCint(node *arg_node, info *arg_info);
extern node *TCfloat(node *arg_node, info *arg_info);
extern node *TCbool(node *arg_node, info *arg_info);

extern node *TCdoTypeCheck(node *syntaxtree);

#endif