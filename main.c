// Шаблон для задания 4.1.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "string_list.h"
#include "sort_string_list.h"

// Macro to calculate the offset of a member in a struct
#define OFFSET_OF(TypeName, entryName)  \
    (unsigned char*)&((TypeName*)0)->entryName

// Macro to get the content record from an address
#define GET_CONTENT_RECORD(TypeName, entryName, addr)    \
    ((TypeName*)((unsigned char*)addr - OFFSET_OF(TypeName, entryName)))



int main() {
	// Create a StringListEntry to work with
	StringListEntry stringList;

	GenerateRandomStringList(100, &stringList);
	// Initialize pointers to the head and end of the list
	ListEntry* head = &stringList.listEntry;
	ListEntry* tmp = &stringList.listEntry;

	// Move tmp to the end of the list
	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;

	// Sort the list using quicksort with lexicographic comparator
	quickSortStringList(head, &stringList.listEntry, tmp, comparatorLexicographic);

	// Reset tmp to the head of the list
	tmp = head;
	while (tmp->prev != NULL)
		tmp = tmp->prev;

	// Print the sorted list
	do {
		char* tmpStr = GET_CONTENT_RECORD(StringListEntry, listEntry, tmp)->value;
		printf("%s\n", tmpStr);
		tmp = tmp->next;
	} while (tmp != NULL);
	printf("\n");

	return 0;
}
