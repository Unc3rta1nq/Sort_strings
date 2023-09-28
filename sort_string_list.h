
#ifndef _SORT_STRING_LIST_
#define _SORT_STRING_LIST_


#include "string_list.h"


#define OFFSET_OF(TypeName, entryName)  \
    (unsigned char*)&((TypeName*)0)->entryName

#define GET_CONTENT_RECORD(TypeName, entryName, addr)    \
    ((TypeName*)((unsigned char*)addr - OFFSET_OF(TypeName, entryName)))


void quickSortStringList(ListEntry* head, ListEntry* first, ListEntry* last, int (*comparator)(char*, char*));

int comparatorLexicographic(char* str1, char* str2);

void ListSwap(ListEntry* entry1, ListEntry* entry2);

#endif  //_SORT_STRING_LIST_