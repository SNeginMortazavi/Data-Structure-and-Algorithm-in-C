/*
 * merge_sort_linked_list.c
 *
 * This file provides implementations of functions that use Merge Sort to sort
 * a linked list. One uses the recursive top-down algorithm, and the other the
 * iterative bottom-up algorithm described in the Wikipedia article:
 * https://en.wikipedia.org/wiki/Merge_sort
 *
 * Splitting a linked list for the top-down algorithm uses the slow/fast
 * pointer technique to step down the list in a single iteration to find the
 * midpoint, rather than stepping down the list once to find the size, then
 * again to find the mid-point. For details see:
 * https://www.quora.com/What-is-a-slow-pointer-and-a-fast-pointer-in-a-linked-list
 *
 * The merge link lists routine is shared by the top-down and bottom up
 * versions of the functions.
 *
 * @since 2017-04-09
 * @author philip gust
 */

#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include "mergesort_linked_list.h"

/**
 * Split the list at its midpoint and return a pointer to the tail list.
 * If the list length is odd, the extra node goes with the head list.
 *
 * Uses the slow/fast pointer technique to step down the list in a single
 * iteration to find the midpoint, rather than stepping down the list once
 * to find the size, then again to find the mid-point. For details see:
 * https://www.quora.com/What-is-a-slow-pointer-and-a-fast-pointer-in-a-linked-list
 *
 * @param listHead the head of the list to split
 * @return the tail list split from the head list at its midpoint
 */
static LinkedListNode* splitLinkedList(LinkedListNode* listHead) {

	LinkedListNode* fast = listHead;
	LinkedListNode* slow = listHead;
	while(slow != (LinkedListNode*)NULL && fast != (LinkedListNode*)NULL){
		slow = slow->next;
		if(fast->next != (LinkedListNode*)NULL){
			fast = fast->next->next;
		}else{
			fast = fast->next;
		}
	}
	return slow;
}


/**
 * Merge two sorted linked lists.
 *
 * @param list1 the first list
 * @param list2 the second list
 * @return a pointer to the merged list
 */
static LinkedListNode* mergeSortedLinkedLists(LinkedListNode* list1, LinkedListNode* list2) {

	if(list1 == (LinkedListNode*)NULL && list2 == (LinkedListNode*)NULL){
		return (LinkedListNode*)NULL;
	}

	if(list1 == (LinkedListNode*)NULL){
		return list2;
	}

	if(list2 == (LinkedListNode*)NULL){
		return list1;
	}

	LinkedListNode* tmp;
	LinkedListNode* cur;

	tmp = createNode((char*) NULL);
	cur = tmp;

	while(list1 != (LinkedListNode*)NULL && list2 != (LinkedListNode*)NULL){
		if(strcmp(list1->data,list2->data) <= 0){
		   cur->next = list1;
		   list1 = list1->next;
		   cur = cur->next;
		}else{
		   cur->next = list2;
		   list2 = list2->next;
		   cur = cur->next;
		}
	}

	cur->next = (list1 == (LinkedListNode*)NULL) ? list2 : list1;
	LinkedListNode* result = tmp->next;

	tmp->next = (LinkedListNode*) NULL;
	free(tmp);
	return result;
}

/**
 * Sort a linked list using the recursive top-down Merge Sort algorithm.
 *
 * @param listHead the head of the list
 * @return the head of the sorted list
 * @see https://en.wikipedia.org/wiki/Merge_sort
 */
LinkedListNode* mergeSortLinkedListTD(LinkedListNode* listHead) {

	if(getListSize(listHead) <= 1){
		return listHead;
	}

	LinkedListNode* middle = splitLinkedList(listHead);
	LinkedListNode* tmp = (LinkedListNode*)NULL;
	LinkedListNode* half = listHead;
	tmp = half;
	while(tmp->next != middle){
		tmp->next = listHead->next;
		tmp = tmp->next;
		listHead = listHead->next;
	}
	tmp->next = (LinkedListNode*)NULL;

	LinkedListNode* left = mergeSortLinkedListTD(half);
	LinkedListNode* right = mergeSortLinkedListTD(middle);
	return mergeSortedLinkedLists(left, right);
}

/**
 * Sort a linked list using the iterative bottom-up Merge Sort algorithm.
 *
 * @param listHead the head of the list
 * @return the head of the sorted list
 * @see https://en.wikipedia.org/wiki/Merge_sort
 */
LinkedListNode* mergeSortLinkedListBU(LinkedListNode* listHead) {

	if (listHead == (LinkedListNode*) NULL){
		return (LinkedListNode*) NULL;
	}

	LinkedListNode* array[32];
	for (int i = 0; i < 32; i++) {
		array[i] = (LinkedListNode*) NULL;
	}

	LinkedListNode* result;
	LinkedListNode* next;
	int i;
	result = listHead;

	while (result != (LinkedListNode*) NULL) {
		next = result->next;
		result->next = (LinkedListNode*) NULL;
		for (i = 0; i < 32 && array[i] != (LinkedListNode*) NULL; i++) {
			result = mergeSortedLinkedLists(array[i], result);
			array[i] = (LinkedListNode*) NULL;
		}
		if (i == 32){
			i -= 1;
		}
		array[i] = result;
		result = next;
	}

	result = (LinkedListNode*) NULL;
	for (i = 0; i < 32; i += 1) {
		result = mergeSortedLinkedLists(array[i], result);
	}
	return result;
}
