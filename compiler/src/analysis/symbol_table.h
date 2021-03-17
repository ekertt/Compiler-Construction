#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_
#include "types.h"

extern node *STdoProcessSymbolTable(node *syntaxtree);

extern node *STprogram(node *arg_node, info *arg_info);
extern node *STglobdef(node *arg_node, info *arg_info);
extern node *STfundef(node *arg_node, info *arg_info);
extern node *STparam(node *arg_node, info *arg_info);
// extern node *STfuncall (node * arg_node, info * arg_info);
extern node *STexprs(node *arg_node, info *arg_info);
extern node *STvardecl(node *arg_node, info *arg_info);
extern node *STvarlet(node *arg_node, info *arg_info);
extern node *STvar(node *arg_node, info *arg_info);

//helper functions
extern node *STcheckForDuplicates(node *list, const char *name);
extern node *STadd(node *table, node *entry);
extern node *STlatestEntry(node *linkedlist);

extern node *STfind(node *symbol_table, const char *name);
node *STfindEntry(node *entry, const char *name);

extern void STdisplay(node *table, size_t tabs);
extern void STprint(node *list, size_t tabs);
extern node *STfindInParent(node *symboltable, const char *name);

#endif
