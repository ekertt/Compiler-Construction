#ifndef _STRENGTH_REDUCTION_H_
#define _STRENGTH_REDUCTION_H_
#include "types.h"

extern node *SRbinop (node *arg_node, info *arg_info);
extern node *SRdoStrenghtReduction( node *syntaxtree);

#endif
