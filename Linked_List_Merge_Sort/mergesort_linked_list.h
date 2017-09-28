/*
 * linked_list.h
 *
 * This file provides definitions of functions that use Merge Sort to sort
 * a linked list. One uses the recursive top-down algorithm, and the other the
 * iterative bottom-up algorithm described in the Wikipedia article:
 * https://en.wikipedia.org/wiki/Merge_sort
 *
 * @since 2017-04-09
 * @author philip gust
 */
#ifndef MERGESORT_LINKED_LIST_H_
#define MERGESORT_LINKED_LIST_H_

#include "linked_list.h"

/**
 * Sort a linked list using the recursive top-down Merge Sort algorithm.
 *
 * @param listHead the head of the list
 * @return the head of the sorted list
 * @see https://en.wikipedia.org/wiki/Merge_sort
 */
LinkedListNode* mergeSortLinkedListTD(LinkedListNode* listHead);

/**
 * Sort a linked list using the iterative bottom-up Merge Sort algorithm.
 *
 *
 * @param listHead the head of the list
 * @return the head of the sorted list
 * @see https://en.wikipedia.org/wiki/Merge_sort
 */
LinkedListNode* mergeSortLinkedListBU(LinkedListNode* listHead);

#endif /* MERGESORT_LINKED_LIST_H_ */
