/*
 * tree_set_iterator.h
 *
 * This file provides the structures and function declarations of a
 * TreeSetIterator that iterates over the setNodes of a TreeSet.
 *
 * @since 2017-02-15

 */

#ifndef TREE_SET_ITERATOR_H_
#define TREE_SET_ITERATOR_H_

#include <stdbool.h>
#include "tree_map_iterator.h"
#include "tree_set.h"

/**
 * An iterator for a TreeSet
 */
typedef struct {
  TreeMapIterator* mapIterator;
} TreeSetIterator;

/**
 * Create and initialize a new TreeSetIterator
 *
 * @param set the set
 * @return an iterator for the specified tree set
 */
TreeSetIterator* createTreeSetIterator(TreeSet* set);

/**
 * Freeing iterator storage.
 *
 * @param itr the TreeSetIterator to delete
 */
void freeTreeSetIterator(TreeSetIterator* itr);

/**
 * Gets next key in the set
 *
 * @param itr the TreeSetIterator
 * @return the next key or NULL if iterator is at end the set
 */
const char* getNextTreeSetKey(TreeSetIterator* itr);

/**
 * Determines whether there is another key in the set
 *
 * @param itr the TreeSetIterator
 * @return true if there is another key, false otherwise
 */
bool hasNextTreeSetKey(TreeSetIterator* itr);

/**
 * Gets previous key in the tree set
 *
 * @param itr the TreeSetIterator
 * @return the previous key or NULL if iterator is at end of list
 */
const char* getPrevTreeSetKey(TreeSetIterator* itr);

/**
 * Determines whether there is a previous key in the set.
 *
 * @param itr the TreeSetIterator
 * @return the previous key or NULL if iterator is at beginning of the set
 */
bool hasPrevTreeSetKey(TreeSetIterator* itr);

/**
 * Resets the tree set iterator to the beginning of the set.
 *
 * @param itr the TreeSetIterator
 * @return true if successful, false if not supported
 */
bool resetTreeSetIterator(TreeSetIterator* itr);

/**
 * Returns the number of keys returned so far.
 *
 * @param itr the TreeSetIterator
 * @return the number of keys returned so far
 */
int getTreeSetIteratorCount(TreeSetIterator* itr);

/**
 * Returns the number of keys available.
 *
 * @param itr the TreeSetIterator
 * @return available number of keys or UNAVAILABLE if cannot perform operation.
 */
int getTreeSetIteratorAvailable(TreeSetIterator* itr);

#endif /* TREE_SET_ITERATOR_H_ */
