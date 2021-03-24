#ifndef _TRANSFORM_CAST_EXPR_H_
#define _TRANSFORM_CAST_EXPR_H_
#include "types.h"

extern node *TCEnum(node *arg_node, info *arg_info);
extern node *TCEfloat(node *arg_node, info *arg_info);
extern node *TCEbool(node *arg_node, info *arg_info);
extern node *TCEprogram(node *arg_node, info *arg_info);
extern node *TCEfundef(node * arg_node, info * arg_info);
extern node *TCEbinop (node * arg_node, info * arg_info);
extern node *TCEvar(node *arg_node, info *arg_info);
extern node *TCEcast ( node *arg_node, info *arg_info);

extern node *TCEdoTransform(node *syntaxtree);

#endif