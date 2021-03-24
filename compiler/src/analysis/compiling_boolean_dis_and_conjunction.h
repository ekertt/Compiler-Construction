#ifndef _COMPILING_BOOLEAN_DIS_AND_CONJUNCTION_H_
#define _COMPILING_BOOLEAN_DIS_AND_CONJUNCTION_H_
#include "types.h"

extern node *CBbinop(node *arg_node, info *arg_info);

extern node *CBdoCompileBoolean(node *syntaxtree);

#endif