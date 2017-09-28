/*
 * tree_map_iterator.c
 *
 * This file provides the implementations of a TreeSetIterator that
 * iterates over the keys of a TreeSet.
 *
 * @since 2017-03-15

 */

#include <stdlib.h>
#include <stdbool.h>

#include "tree_set_iterator.h"

/**
 * Create and initialize a new TreeSetIterator
 *
 * @param set the set
 * @return an iterator for the specified tree set
 */
TreeSetIterator* createTreeSetIterator(TreeSet* set) {
	TreeSetIterator* itr = (TreeSetIterator*)malloc(sizeof(TreeSetIterator));
	itr->mapIterator = (TreeMapIterator*)malloc(sizeof(TreeMapIterator));
	itr->mapIterator->treeItr = createBinaryTreeIterator(set->map->searchTree);
	return itr;
}

/**
 * Freeing iterator storage.
 *
 * @param itr the TreeSetIterator to delete
 */
void freeTreeSetIterator(TreeSetIterator* itr) {
	freeTreeMapIterator(itr->mapIterator);
	itr->mapIterator = (TreeMapIterator*)NULL;
	free(itr);
}

/**
 * Gets next key in the set
 *
 * @param itr the TreeSetIterator
 * @return the next key or NULL if iterator is at end the set
 */
const char* getNextTreeSetKey(TreeSetIterator* itr) {
	BinaryTreeNode* node = getNextBinaryTreeNode(itr->mapIterator->treeItr);
	return (node == (BinaryTreeNode*)NULL) ? (const char*)NULL : node->data->entry.key;
}

/**
 * Determines whether there is another key in the set
 *
 * @param itr the TreeSetIterator
 * @return true if there is another key, false otherwise
 */
bool hasNextTreeSetKey(TreeSetIterator* itr) {
	return hasNextBinaryTreeNode(itr->mapIterator->treeItr);
}

/**
 * Gets previous key in the tree set
 *
 * @param itr the TreeSetIterator
 * @return the previous key or NULL if iterator is at end of list
 */
const char* getPrevTreeSetKey(TreeSetIterator* itr) {
	BinaryTreeNode* node = getPrevBinaryTreeNode(itr->mapIterator->treeItr);
	return (node == (BinaryTreeNode*)NULL) ? (const char*)NULL : node->data->entry.key;
}

/**
 * Determines whether there is a previous key in the set.
 *
 * @param itr the TreeSetIterator
 * @return the previous key or NULL if iterator is at beginning of the set
 */
bool hasPrevTreeSetKey(TreeSetIterator* itr) {
	return hasPrevBinaryTreeNode(itr->mapIterator->treeItr);
}

/**
 * Resets the iterator to the beginning of the set.
 *
 * @param itr the TreeSetIterator
 * @return true if successful, false if not supported
 */
bool resetTreeSetIterator(TreeSetIterator* itr) {
	return resetBinaryTreeIterator(itr->mapIterator->treeItr);
}

/**
 * Returns the number of keys returned so far.
 *
 * @param itr the TreeSetIterator
 * @return the number of keys returned so far
 */
int getTreeSetIteratorCount(TreeSetIterator* itr) {
	return getBinaryTreeIteratorCount(itr->mapIterator->treeItr);
}

/**
 * Returns the number of keys available.
 *
 * @param itr the TreeSetIterator
 * @return available number of keys or UNAVAILABLE if cannot perform operation.
 */
int getTreeSetIteratorAvailable(TreeSetIterator* itr) {
	return getBinaryTreeIteratorAvailable(itr->mapIterator->treeItr);
}
