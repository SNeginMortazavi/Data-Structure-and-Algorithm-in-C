/*
 * binary_tree_node_queue.h
 *
 *  Created on: Mar 7, 2017
 *      Author: Negin Mortazavi
 */

#ifndef BINARY_TREE_NODE_QUEUE_H_
#define BINARY_TREE_NODE_QUEUE_H_

#include "binary_tree_node.h"
#include <stdbool.h>


/**
 * A struct representing a BinaryTreeNodeQueue.
 */
typedef struct _BinaryTreeNodeQueue{
	int size;                  // length of allocated array
	int numElement;			  // number of elements in the queue
	BinaryTreeNode** nodes;  // array of node pointers
}BinaryTreeNodeQueue;


/**
 * Create a new node queue
 */
BinaryTreeNodeQueue* newBinaryTreeNodeQueue(void);

/**
 * Deallocate the memory for the queue.
 */
void deleteBinaryTreeNodeQueue(BinaryTreeNodeQueue* queue);

/**
 * Add a number to the queue.
 */
void enqueueBinaryTreeNodeQueue(BinaryTreeNodeQueue* queue, BinaryTreeNode* node);

/**
 * Remove and return the first element in the queue.
 */
BinaryTreeNode* dequeueBinaryTreeNodeQueue(BinaryTreeNodeQueue* queue);

/**
 * Check if the queue is empty
 */
bool isEmptyBinaryTreeNodeQueue(BinaryTreeNodeQueue* queue);

/**
 * Get the current number of elements in the queue.
 */
int getNumElementsBinaryTreeNodeQueue(BinaryTreeNodeQueue* queue);




#endif /* BINARY_TREE_NODE_QUEUE_H_ */
