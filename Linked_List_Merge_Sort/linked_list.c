/*
 * linked_lists.c
 *
 * This file implements a singly linked list. The methods can be
 * used in one of two ways.
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
 * @return Node with fields set to NULL
 */
LinkedListNode* createNode(char* data) {
	// allocate node
	LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));

	// initialize fields
	newNode->data = (data == (char*)NULL) ? (char*)NULL : strdup(data);
	//newNode->data = (char*)NULL;
	newNode->next = (LinkedListNode*)NULL;
	//newNode = NULL;

	return newNode;
}

/**
 * Freeing node storage.  The node must be removed from its list
 * by calling deleteNode() first.
 *
 * @param node the LinkedListNode to delete
 */
void freeNode(LinkedListNode* node) {
	if (node != (LinkedListNode*)NULL) {
		// free pointer to data string
		free(node->data);  // free ok with NULL
		node->data = (char*)NULL;

		// reset the next pointer
		node->next = (LinkedListNode*)NULL;

		// now free the node
		free(node);
	}
}

/**
 * Returns last node in list, or NULL if list is NULL.
 *
 * @param the list of LinkedListNodes
 * @return the last node in the list or NULL
 */
LinkedListNode* getLastNode(LinkedListNode* list) {
	LinkedListNode* n = list;
	if (n != (LinkedListNode*)NULL) {
		for ( ; n->next != (LinkedListNode*)NULL; n = n->next) {}
	}
	return n;
}

/**
 * Return the size of the list. If the list has a dummy first node, pass
 * its next pointer to this function.
 *
 * @param list the list to be measured
 * @return the size of the list
 */
int getListSize(LinkedListNode* list) {
	int size = 0;
	// traverse down the list, counting as it goes
	for (LinkedListNode* node = list; node != (LinkedListNode*)NULL; node= node->next, size++) {
	}
	return size;
}

/**
 * Add new node after the specified node in the list.
 *
 * @param list the list node after which new node will be added
 * @param the new node to insert
 */
void addAfterNode(LinkedListNode* list, LinkedListNode* newNode) {  // note: refactored from addLast()
	if (list != (LinkedListNode*)NULL) {
		// make new node point to successor of list node
		newNode->next = list->next;
		// make list node point to new node
		list->next = newNode;
	} else {
		// first node in list

		//list->next = newNode;
		newNode->next = (LinkedListNode*)NULL;
	}
}

/**
 * Delete node after specified list node. Caller is responsible for
 * freeing the deleted node by calling freeNode().
 *
 * @param the list node after which node will be deleted
 * @return the deleted node that the caller must free, or NULL if
 *   list has no next node
 */
LinkedListNode* deleteAfterNode(LinkedListNode* list) {
	LinkedListNode *deletedNode = (LinkedListNode*)NULL;

	if (list != (LinkedListNode*)NULL) {
		// pointer to next node that will to be deleted
		deletedNode = list->next;

		// only need to do if there is a next node to delete
		if (deletedNode != (LinkedListNode*)NULL) {
			// make list node point to where next node pointed
			list->next = deletedNode->next;

			// reset next pointer of deletedNode node
			deletedNode->next = (LinkedListNode*)NULL;
		}
	}
	return deletedNode;
}

/**
 * Print the list data.
 *
 * @param list the list to print
 */
void printList(LinkedListNode *list) {
	printf("( ");
	for (LinkedListNode* n = list; n != (LinkedListNode*)NULL; n = n->next) {
		printf("\"%s\" ", n->data);
	}
	printf(")\n");
}

