/*
 * binary_tree_iterator.h
 *
 * This file provides the function implementations for a binary tree interator.
 *
 * @since 2017-02-15
 * @author philip gust
 */

#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "binary_tree_iterator.h"

/**
 * Value returned by getBinaryTreeIteratorAvailable if count unavailable
 */
const int UNAVAILABLE = INT_MIN;

/**
 * Create and initialize a new BinaryTreeIterator
 *
 * @param theTree binary tree
 * @return an iterator for the specified binary tree
 */
BinaryTreeIterator* createBinaryTreeIterator(BinaryTreeNode* theTree) {
	BinaryTreeIterator* itr = (BinaryTreeIterator*)malloc(sizeof(BinaryTreeIterator));
	itr->curNode = theTree;
	itr->theTree = theTree;
	itr->prevLink = parentLink;
	itr->count = 0;
 	itr->size =   // UNAVAILABLE causes size to be computed on first use
	  (theTree == (BinaryTreeNode*)NULL) ? 0 : UNAVAILABLE;  // compute on first access

 	return itr;
}

/**
 * Freeing iterator storage.
 *
 * @param itr the LinkedListIterator to delete
 */
void freeBinaryTreeIterator(BinaryTreeIterator* itr) {
	itr->count = UNAVAILABLE;
	itr->size = UNAVAILABLE;
	itr->prevLink = UNAVAILABLE;
	itr->curNode = (BinaryTreeNode*)NULL;
	itr->theTree = (BinaryTreeNode*)NULL;
	free(itr);
}

/**
 * Gets next link node in the binary tree.
 *
 * @param itr the BinaryTreeIterator
 * @return the next node or NULL if no more nodes available
 */
BinaryTreeNode* getNextBinaryTreeNode(BinaryTreeIterator* itr) {
	// restore state from iterator
	BinaryTreeNode* cur = itr->curNode;
	BinaryTreeNodeLink prvLink = itr->prevLink;

	BinaryTreeNode* resultNode = (BinaryTreeNode*)NULL; // node to return
	while (resultNode == (BinaryTreeNode*)NULL && cur != (BinaryTreeNode*)NULL) {
		BinaryTreeNodeLink nxtLink;

		if (prvLink == parentLink) {  // coming from parent
			if (cur->linkTo[leftLink] != (BinaryTreeNode*)NULL) {
				nxtLink = leftLink;
			} else if (cur->linkTo[rightLink] != (BinaryTreeNode*)NULL) {
				nxtLink = rightLink;
				resultNode = cur;   // non-existent left leaf: update itr and return
			} else {
				nxtLink = parentLink;
				resultNode = cur;   // at leaf node: update itr and return
			}
		} else if (prvLink == leftLink) { // coming from left child
			if (cur->linkTo[rightLink] != (BinaryTreeNode*)NULL) {
				nxtLink = rightLink;
			} else {
				nxtLink = parentLink;
			}
			resultNode = cur;   // at parent node from left: update itr and return

		} else {  // prvLink == rightLink coming from right child
			nxtLink = parentLink;
		}
		prvLink = (nxtLink == parentLink) ? linkOfBinaryTreeNodeChild(cur) : parentLink;
		// ensures stopping after root node if the tree is a subtree
		cur = (cur == itr->theTree && nxtLink == parentLink)
				? (BinaryTreeNode*)NULL : cur->linkTo[nxtLink];
	}

	// save state to iterator
	itr->curNode = cur;
	itr->prevLink = prvLink;
	itr->count += (resultNode != (BinaryTreeNode*)NULL);

	return resultNode;
}

/**
 * Determines whether there is another node in the binary tree.
 *
 * @param itr the LinkedListIterator
 * @return true if there is another node, false otherwise
 */
bool hasNextBinaryTreeNode(BinaryTreeIterator* itr) {
	BinaryTreeIterator testItr = *itr;  // local copy of iterator struct
	if (getNextBinaryTreeNode(&testItr) == (BinaryTreeNode*)NULL) {
		*itr = testItr;  // update iterator from local copy
		return false;
	}
	return true;
}

/**
 * Gets previous node in the binary tree.
 *
 * @param itr the LinkedListIterator
 * @return the previous node or NULL if iterator is at end of list
 */
BinaryTreeNode* getPrevBinaryTreeNode(BinaryTreeIterator* itr) {
	return (BinaryTreeNode*)NULL;
}

/**
 * Determines whether there is a previous node in the binary tree.
 *
 * @param itr the BinaryTreeIterator
 * @return true if there is a previous node, false otherwise
 */
bool hasPrevBinaryTreeNode(BinaryTreeIterator* itr) {
	return false;
}

/**
 * Resets the binary tree iterator to the root of the tree.
 *
 * @param itr the BinaryTreeIterator
 * @return true if successful, false if not supported
 */
bool resetBinaryTreeIterator(BinaryTreeIterator* itr) {
	itr->count = 0;
	itr->curNode = itr->theTree;
	itr->prevLink = parentLink;
	return true;
}

/**
 * Returns the number of nodes returned so far.
 *
 * @param itr the BinaryTreeIterator
 */
int getBinaryTreeIteratorCount(BinaryTreeIterator* itr) {
  return itr->count;
}

/**
 * Returns the number of nodes available.
 *
 * @param itr the BinaryTreeIterator
 * @return available number of node or UNAVAILABLE if cannot perform operation.
 */
int getBinaryTreeIteratorAvailable(BinaryTreeIterator* itr) {
	if (itr->size == UNAVAILABLE) {
		itr->size = binaryTreeSize(itr->theTree);
	}
	return itr->size - itr->count;
}
