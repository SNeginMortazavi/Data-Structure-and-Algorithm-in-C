/*
 * linked_list.h
 *
 * This file provides the structure and function definitions for a
 * singly linked list. The methods can be used in one of two ways.
 *
 * If the empty list is represented by a NULL list pointer, then
 * add the first item by setting the list pointer to the first item
 * and delete the final item by freeing the node and setting the
 * list pointer to NULL.
 *
 * If the empty list is represented by a dummy first node, then
 * add the first item by calling addAfter() with the dummy node and
 * the first node, delete the last item by calling deleteAfter()
 * with the dummy first node, and get the size excluding the dummy
 * node by passing the dummy node's next pointer to getListSize().
 *
 * @since 2017-02-08
 * @author philip gust
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdlib.h>

/**
 * Singly linked list node
 * Note peculiar way the "C" requires node next field to be declared
 */
typedef struct _LinkedListNode {
	char* data;
	struct _LinkedListNode* next;
} LinkedListNode;

/**
 * Create and initialize new node.
 *
 * @param data the node data
 * @return Node with fields set to NULL
 */
LinkedListNode* createNode(char* data);

/**
 * Freeing node storage.  The node must be removed from its list
 * by calling deleteNode() first.
 *
 * @param node the LinkedListNode to delete
 */
void freeNode(LinkedListNode* node);

/**
 * Returns last node in list, or NULL if list is NULL.
 *
 * @param the list of Nodes
 * @return the last node in the list or NULL
 */
LinkedListNode* getLastNode(LinkedListNode* list);

/**
 * Return the size of the list. If the list has a dummy first node, pass
 * its next pointer to this function.
 *
 * @param list the list to be measured
 * @return the size of the list
 */
int getListSize(LinkedListNode* list);

/**
 * Add new node after the specified node in the list.
 *
 * @param list the list node after which new node will be added
 * @param the new node to insert
 */
void addAfterNode(LinkedListNode* list, LinkedListNode* newNode);

/**
 * Delete node after specified list node. Caller is responsible for
 * freeing the deleted node by calling freeNode().
 *
 * @param the list node after which node will be deleted
 * @return the deleted node that the caller must free, or NULL if
 *   list has no next node
 */
LinkedListNode* deleteAfterNode(LinkedListNode* list);


#endif /* LINKED_LIST_H_ */
