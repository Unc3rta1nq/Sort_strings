#include "list.h"


// инициализация пустого списка
void InitList(ListEntry* head) {

	head->next = NULL;
	head->prev = NULL;

	return;

}


// добавление нового элемента в конец списка
void InsertTailList(ListEntry* head, ListEntry* newEntry) {

	ListEntry* tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = newEntry;
	newEntry->next = NULL;
	newEntry->prev = tmp;

	return;

}


// добавление нового элемента в начало списка
void InsertHead(ListEntry* head, ListEntry* newEntry) {

	newEntry->prev = NULL;
	newEntry->next = head;
	head->prev = newEntry;

	return;

}


// удаление элемента
void RemoveEntry(ListEntry* entry) {

	if (entry->prev == NULL && entry->next != NULL) {
		entry->next->prev = NULL;
	}
	else {
		if (entry->next == NULL && entry->prev != NULL) {
			entry->prev->next = NULL;
		}
		else {
			if (entry->next != NULL && entry->prev != NULL) {
				entry->prev->next = entry->next;
				entry->next->prev = entry->prev;
			}
		}
	}

	free(entry);

	return;

}


// удаление списка
void FreeList(ListEntry* head) {

	while (head->next != NULL) {
		RemoveEntry(head->next);
	}
	free(head);

	return;

}


// получение следующего элемента
ListEntry* GetNextEntry(ListEntry* entry) {

	if (entry->next)
		return entry->next;

	return NULL;

}


// получение предыдущего элемента
ListEntry* GetPrevEntry(ListEntry* entry) {

	if (entry->prev)
		return entry->prev;

	return NULL;

}


// перестановка элементов
void ListSwap(ListEntry* entry1, ListEntry* entry2) {

	if (entry1 == entry2)
		return; // Nothing to swap if the entries are the same

	if (entry1->next == entry2) {
		// If the entries are adjacent in the list, swap them
		if (entry1->prev != NULL)
			entry1->prev->next = entry2;
		if (entry2->next != NULL)
			entry2->next->prev = entry1;
		entry1->next = entry2->next;
		entry2->prev = entry1->prev;

		entry1->prev = entry2;
		entry2->next = entry1;

		return;
	}
	else {
		// If the entries are not adjacent, swap them non-adjacent
		ListEntry tmp;
		tmp.next = entry1->next;
		tmp.prev = entry1->prev;

		entry1->prev = entry2->prev;
		entry1->next = entry2->next;

		if (tmp.prev != NULL)
			tmp.prev->next = entry2;
		if (tmp.next != NULL)
			tmp.next->prev = entry2;
		if (entry2->prev != NULL)
			entry2->prev->next = entry1;
		if (entry2->next != NULL)
			entry2->next->prev = entry1;

		entry2->prev = tmp.prev;
		entry2->next = tmp.next;

		return;

	}

	return;

}