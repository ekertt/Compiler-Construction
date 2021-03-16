#ifndef _SYMBOL_TABLE_HELPER_H_
#define _SYMBOL_TABLE_HELPER_H_
#include "types.h"

extern node *STcheckForDuplicates(node *list, const char *name);
extern node *STadd(node *table, node *entry);
extern node *STlatestEntry(node *linkedlist);

extern node *STfind(node *symbol_table, const char *name);
node *STfindEntry(node *entry, const char *name);

extern void STdisplay(node *table, size_t tabs);
extern void STprint(node *list, size_t tabs);
// extern size_t countParams(node *table);
// extern node *findFundef(node *table, const char *name);
// extern node *STsearchFundefEntry(node *table, const char *name);

#endif


