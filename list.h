
#include <stdlib.h>


#ifndef _LIST_H_
#define _LIST_H_


typedef struct _ListEntry {

	struct _ListEntry* next;
	struct _ListEntry* prev;

} ListEntry;


ListEntry* GetNextEntry(ListEntry* entry);

void InitList(ListEntry* head);

void InsertTailList(ListEntry* head, ListEntry* newEntry);

void RemoveEntry(ListEntry* entry);

void FreeList(ListEntry* head);

void ListSwap(ListEntry* entry1, ListEntry* entry2);

#endif  // _LIST_H_