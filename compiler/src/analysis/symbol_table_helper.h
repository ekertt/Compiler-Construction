#ifndef _SYMBOL_TABLE_HELPER_H_
#define _SYMBOL_TABLE_HELPER_H_
#include "types.h"

extern node *STcheckForDuplicates(node *list, const char *name);
extern node *STadd(node *table, node *entry);
extern node *STsearchLink(node *linkedlist, const char *name, type type);
extern node *STlatestEntry(node *linkedlist);

extern void STdisplay(node *table, size_t tabs);
extern void STprint(node *list, size_t tabs);
#endif


