/*
 * binary_tree_iterator.h
 *
 * This file provides the structure and function definitions for an
 * iterator of a binary tree.
 *
 * @since 2017-02-15
 * @author philip gust
 */

#ifndef BINARY_TREE_ITERATOR_H_
#define BINARY_TREE_ITERATOR_H_

#include <stdbool.h>
#include "binary_tree.h"

/**
 * An iterator for a binary tree
 */
typedef struct {
  BinaryTreeNode* theTree;
  BinaryTreeNode* curNode;
  BinaryTreeNodeLink prevLink;
  int count;  // the number of nodes returned by iterator
  int size;  // the size of the tree
} BinaryTreeIterator;

/**
 * Value returned by getLinkedListIteratorAvailable if count unavailable
 */
extern const int UNAVAILABLE;

/**
 * Create and initialize a new BinaryTreeIterator
 *
 * @param theTree binary tree
 * @return an iterator for the specified binary tree
 */
BinaryTreeIterator* createBinaryTreeIterator(BinaryTreeNode* theTree);

/**
 * Freeing iterator storage.
 *
 * @param itr the BinaryTreeIterator to delete
 */
void freeBinaryTreeIterator(BinaryTreeIterator* itr);

/**
 * Gets next link node in the binary tree
 *
 * @param itr the BinaryTreeIterator
 * @return the next node or NULL if iterator is at end of tree
 */
BinaryTreeNode* getNextBinaryTreeNode(BinaryTreeIterator* itr);

/**
 * Determines whether there is another node in the binary tree.
 *
 * @param itr the BinaryTreeIterator
 * @return true if there is another node, false otherwise
 */
bool hasNextBinaryTreeNode(BinaryTreeIterator* itr);

/**
 * Gets previous node in the binary tree.
 *
 * @param itr the BinaryTreeIterator
 * @return the previous node or NULL if iterator is at end of list
 */
BinaryTreeNode* getPrevBinaryTreeNode(BinaryTreeIterator* itr);

/**
 * Determines whether there is a previous node in the binary tree.
 *
 * @param itr the BinaryTreeIterator
 * @return true if there is a previous node, false otherwise
 */
bool hasPrevBinaryTreeNode(BinaryTreeIterator* itr);

/**
 * Resets the binary tree iterator to the root of the tree.
 *
 * @param itr the BinaryTreeIterator
 * @return true if successful, false if not supported
 */
bool resetBinaryTreeIterator(BinaryTreeIterator* itr);

/**
 * Returns the number of nodes returned so far.
 *
 * @param itr the BinaryTreeIterator
 */
int getBinaryTreeIteratorCount(BinaryTreeIterator* itr);

/**
 * Returns the number of nodes available.
 *
 * @param itr the BinaryTreeIterator
 * @return available number of node or UNAVAILABLE if cannot perform operation.
 */
int getBinaryTreeIteratorAvailable(BinaryTreeIterator* itr);

#endif /* BINARY_TREE_ITERATOR_H_ */
