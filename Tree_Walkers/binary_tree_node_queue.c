/*
 * binary_tree_node_queue.h
 *
 *  Created on: Mar 7, 2017
 *      Author: Negin Mortazavi
 */

#include <stdlib.h>
#include <assert.h>
#include "binary_tree.h"
#include "binary_tree_node_queue.h"

/**
 * Create a new tree node queue
 *
 * @return the new BinaryTreeNodeQueue
 */

BinaryTreeNodeQueue* newBinaryTreeNodeQueue(void){
	BinaryTreeNodeQueue* myQueue = (BinaryTreeNodeQueue*)malloc(sizeof(BinaryTreeNodeQueue));
	assert(myQueue != (BinaryTreeNodeQueue*)NULL);

	 /**size of queue should be 2 to the power of height of the tree
	 since the input of the this function is void, I assume the size is reasonably
	 large enough. If the input was not void, I defined size as follow:
	 size = power(2, binaryTreeHeight(node)) with the following definition for power:


	int power(a, b){
	if(b == 0)
		return 1;
	return a * power(a, b - 1);
		}
	*/

	myQueue->size = 256;
	myQueue->numElement = 0;
	myQueue->nodes = (BinaryTreeNode**)malloc(sizeof(BinaryTreeNode*) * myQueue->size);
	assert(myQueue->nodes != (BinaryTreeNode**)NULL);
	return myQueue;
}


/**
 * Deallocate the memory for the queue.
 *
 * @param queue the BinaryTreeNodeQueue
 */
void deleteBinaryTreeNodeQueue(BinaryTreeNodeQueue* queue){
	assert(queue != (BinaryTreeNodeQueue*)NULL);
	if(queue->nodes != (BinaryTreeNodeQueue*)NULL){
		for(int i = 0; i < queue->numElement; i++){
			deleteBinaryTreeNode(queue->nodes[i]);
			queue->nodes[i] = (BinaryTreeNodeQueue*)NULL;
		}
	}
	free(queue->nodes);
	queue->numElement = 0;
	queue->size = 0;
	queue->nodes = (BinaryTreeNode**)NULL;
	free(queue);
}

/**
 * Add a node to the queue.
 *
 * @param queue the tree node queue
 * @param node the element of tree to be added to the queue
 */

void enqueueBinaryTreeNodeQueue(BinaryTreeNodeQueue* queue, BinaryTreeNode* node){
	assert(node != (BinaryTreeNode*)NULL);
	assert(queue != (BinaryTreeNodeQueue*)NULL);
	assert(queue->numElement < queue->size);

	// reallocating if necessary.
	if(queue->numElement == queue->size){
		int newSize = 2 * queue->size;
		BinaryTreeNode** newMessages = (BinaryTreeNode**)realloc(queue->nodes, (sizeof(BinaryTreeNode*)) * newSize);
		assert(newMessages != (BinaryTreeNode**)NULL);

		queue->nodes = newMessages;
		assert(newMessages != (BinaryTreeNode*)NULL);
		queue->size = newSize;
	}
		queue->nodes[queue->numElement++] = node;
}

/**
 * Remove and return the first element in the queue.
 *
 * @param queue the tree node queue
 * @return the dequeued node, or NULL if no node on queue
 */

BinaryTreeNode* dequeueBinaryTreeNodeQueue(BinaryTreeNodeQueue* queue){
	assert(queue != (BinaryTreeNodeQueue*)NULL);

	// queue is empty
	if(queue->numElement == 0){
		return (BinaryTreeNode*)NULL;
	}

	BinaryTreeNode* deleted = queue->nodes[0];

	// remove the node from the queue
	for(int i = 0; i < queue->numElement ; i++){
		queue->nodes[i] = queue->nodes[i + 1];
	}
	queue->numElement--;
	return deleted;
}

/**
 * Check if the queue is empty
 *
 * @param queue the tree node queue
 * @return true if it is empty or false otherwise.
 */
bool isEmptyBinaryTreeNodeQueue(BinaryTreeNodeQueue* queue){
	if(queue->numElement == 0){
		return true;
	}
	return false;
}

/**
 * Get the current number of elements in the queue.
 *
 * @param queue the tree node queue
 * return number of element in BinaryTreeNodeQueue queue.
 */

int getNumElementsBinaryTreeNodeQueue(BinaryTreeNodeQueue* queue){
	return queue->numElement;
}


