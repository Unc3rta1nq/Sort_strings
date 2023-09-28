#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "string_list.h"


// инициализация из строки нового элемента списка строк
StringListEntry* CreateAndInitNewStringListEntry(char* str) {

	StringListEntry* entry = (StringListEntry*)malloc(sizeof(StringListEntry));

	if (entry == NULL) {
		return NULL;
	}
	// Allocate memory for the string value and copy the input string
	entry->value = (char*)malloc(strlen(str) + 1);
	if (!entry->value) {
		free(entry);
		return NULL;
	}
	// Initialize the list pointers
	entry->listEntry.next = NULL;

	strcpy(entry->value, str);

	return entry;

}


// удаление элемента списка
void FreeStringListEntry(StringListEntry* entry) {
	// Remove the entry from the list
	RemoveEntry(&entry->listEntry);
	// Free the string value and the entry itself
	free(entry->value);
	free(entry);

	return;

}


// добавление строки в конец списка
void AddStringTailStringList(StringListEntry* stringList, char* str) {

	StringListEntry* sLEntry;
	sLEntry = CreateAndInitNewStringListEntry(str);
	// Insert the new entry at the tail of the list
	InsertTailList(&stringList->listEntry, &sLEntry->listEntry);

	return;

}


// удаление списка
void FreeStringList(StringListEntry* stringList) {
	// Free the entire list, including the string values and entries
	FreeList(&stringList->listEntry);
	free(stringList->value);
	free(stringList);

	return;

}


// генератор случайных строк
void GenerateRandomStringList(unsigned int size, StringListEntry* stringList) {
	// Initialize the list
	InitList(&stringList->listEntry);

	srand(time(NULL));
	for (int i = 0; i < size; ++i) {
		int length = 10 + rand() % 10;
		char* str = (char*)malloc(sizeof(char) * (length + 1));
		for (int j = 0; j < length; ++j) {
			str[j] = 65 + rand() % 26;

		}
		str[length] = '\0';
		if (i == 0) {
			// Initialize the first entry with the generated string
			stringList->value = (char*)malloc(sizeof(char) * (length + 1));
			strcpy(stringList->value, str);
			stringList->listEntry.next = NULL;
			stringList->listEntry.prev = NULL;
		}
		else
			// Add the generated string to the list
			AddStringTailStringList(stringList, str);
	}

	return;

}