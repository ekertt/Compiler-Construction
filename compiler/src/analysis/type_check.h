#ifndef _TYPE_CHECK_H_
#define _TYPE_CHECK_H_
#include "types.h"

extern node *TCprogram(node *arg_node, info *arg_info);
extern node *TCnum(node *arg_node, info *arg_info);
extern node *TCfloat(node *arg_node, info *arg_info);
extern node *TCbool(node *arg_node, info *arg_info);
extern node *TCfundef(node *arg_node, info *arg_info);
extern node *TCreturn(node *arg_node, info *arg_info);
extern node *TCexprstmt(node *arg_node, info *arg_info);
// extern node *TCassign(node *arg_node, info *arg_info);
extern node *TCbinop(node *arg_node, info *arg_info);

extern node *TCdoTypeCheck(node *syntaxtree);

#endif