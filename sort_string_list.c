#include <string.h>

#include "sort_string_list.h"


// приведение к нижнему регистру
int toLow(char symbol) {

	if (symbol >= 'A' && symbol <= 'Z')
		return symbol - 'A' + 'a';

	return symbol;

}


// компаратор
int comparatorLexicographic(char* str1, char* str2) {

	int i = 0;
	while (str1[i] != '\0' && str2[i] != '\0') {
		if (toLow(str1[i]) < toLow(str2[i]))
			return 1; // str1 is greater
		if (toLow(str1[i]) > toLow(str2[i]))
			return -1; // str2 is greater
		++i;
	}

	if (str2[i] != '\0')
		return 1; // str1 is shorter, but identical up to this point

	if (str2[i] != '\0')
		return -1; // str2 is shorter, but identical up to this point

	return 0; // Both strings are identical

}


// перестановка элементов списка строк
void strListSwap(StringListEntry* strEntry1, StringListEntry* strEntry2) {

	if (strEntry1 == strEntry2)
		return;

	if (strEntry1->listEntry.next == &strEntry2->listEntry) {
		// Swap adjacent entries in the list
		if (strEntry1->listEntry.prev != NULL)
			strEntry1->listEntry.prev->next = &strEntry2->listEntry;
		if (strEntry2->listEntry.next != NULL)
			strEntry2->listEntry.next->prev = &strEntry1->listEntry;
		strEntry1->listEntry.next = strEntry2->listEntry.next;
		strEntry2->listEntry.prev = strEntry1->listEntry.prev;

		strEntry1->listEntry.prev = &strEntry2->listEntry;
		strEntry2->listEntry.next = &strEntry1->listEntry;

		return;
	}
	else {
		// Swap non-adjacent entries in the list
		ListEntry tmp;
		tmp.next = strEntry1->listEntry.next;
		tmp.prev = strEntry1->listEntry.prev;

		strEntry1->listEntry.prev = strEntry2->listEntry.prev;
		strEntry1->listEntry.next = strEntry2->listEntry.next;

		if (tmp.prev != NULL)
			tmp.prev->next = &strEntry2->listEntry;
		if (tmp.next != NULL)
			tmp.next->prev = &strEntry2->listEntry;
		if (strEntry2->listEntry.prev != NULL)
			strEntry2->listEntry.prev->next = &strEntry1->listEntry;
		if (strEntry2->listEntry.next != NULL)
			strEntry2->listEntry.next->prev = &strEntry1->listEntry;

		strEntry2->listEntry.prev = tmp.prev;
		strEntry2->listEntry.next = tmp.next;

		return;

	}

	return;

}


// быстрая сортировка списка
void quickSortStringList(ListEntry* head, ListEntry* first, ListEntry* last, int (*comparator)(char*, char*)) {

	if (first == NULL || last == NULL || first == last)
		return;


	ListEntry* tmp = last;
	while (tmp != NULL) {
		if (tmp == first)
			return;
		tmp = tmp->next;
	}

	ListEntry* left = first;

	ListEntry* right = last;

	ListEntry* mid;
	int i;
	tmp = left;
	for (i = 0; tmp != right; tmp = tmp->next, ++i);
	tmp = left;
	for (int j = 0; j < i / 2; ++j, tmp = tmp->next);

	mid = tmp;
	int flag;

	if (i == 1) {
		// If there are only two elements in this segment
		if (comparator(GET_CONTENT_RECORD(StringListEntry, listEntry, right)->value, GET_CONTENT_RECORD(StringListEntry, listEntry, left)->value) == 1) {
			// Swap them if they are out of order

			ListSwap(left, right);
			head = right;

		}
		return;
	}
	do {
		while (comparator(GET_CONTENT_RECORD(StringListEntry, listEntry, left)->value, GET_CONTENT_RECORD(StringListEntry, listEntry, mid)->value) == 1) {
			left = left->next;
			i--;
		}
		while (comparator(GET_CONTENT_RECORD(StringListEntry, listEntry, mid)->value, GET_CONTENT_RECORD(StringListEntry, listEntry, right)->value) == 1) {
			right = right->prev;
			i--;
		}


		if (i >= 0) {
			// Swap elements if they are out of order
			ListSwap(left, right);
			// Update pointers
			tmp = left;
			left = right;
			right = tmp;

			if (head == left)
				head = right;
			else
				if (head == right)
					head = left;

			if (first == left)
				first = right;
			else
				if (first == right)
					first = left;

			if (last == right)
				last = left;
			else
				if (last == left)
					last = right;


			if (left->next != NULL) {
				left = left->next;
				i--;
			}


			if (right->prev != NULL) {
				right = right->prev;
				i--;
			}

		}

	} while (i >= 0);

	// Recursively sort the two partitions
	quickSortStringList(head, first, right, comparator);
	quickSortStringList(head, left, last, comparator);

	return;

}