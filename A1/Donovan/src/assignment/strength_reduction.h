#ifndef _STRENGTH_REDUCTION_H
#define _STRENGTH_REDUCTION_H

#include "types.h"

extern node *SRdoStrengthReduction( node* syntax_tree);
extern node *SRbinop( node* arg_node, info* arg_info);

#endif