/*
 * tree_map_iterator.h
 *
 * This file provides the structures and function declarations of a
 * TreeMapIterator that iterates over the MapNodes of a TreeMap.
 *
 * @since 2017-02-15

 */

#ifndef TREE_MAP_ITERATOR_H_
#define TREE_MAP_ITERATOR_H_

#include <stdbool.h>
#include "tree_map.h"
#include "binary_tree_iterator.h"

/**
 * An iterator for a TreeMap
 */
typedef struct {
  BinaryTreeIterator* treeItr;
} TreeMapIterator;

/**
 * Create and initialize a new TreeMapIterator
 *
 * @param map the map
 * @return an iterator for the specified tree map
 */
TreeMapIterator* createTreeMapIterator(TreeMap* map);

/**
 * Freeing iterator storage.
 *
 * @param itr the TreeMapIterator to delete
 */
void freeTreeMapIterator(TreeMapIterator* itr);

/**
 * Gets next link entry in the map
 *
 * @param itr the TreeMapIterator
 * @return the next entry or NULL if iterator is at end the map
 */
MapEntry* getNextTreeMapEntry(TreeMapIterator* itr);

/**
 * Determines whether there is another entry in the map
 *
 * @param itr the TreeMapIterator
 * @return true if there is another entry, false otherwise
 */
bool hasNextTreeMapEntry(TreeMapIterator* itr);

/**
 * Gets previous entru in the tree map
 *
 * @param itr the TreeMapIterator
 * @return the previous entry or NULL if iterator is at end of list
 */
MapEntry* getPrevTreeMapEntry(TreeMapIterator* itr);

/**
 * Determines whether there is a previous entry in the map.
 *
 * @param itr the TreeMapIterator
 * @return true if there is a previous entry, false otherwise
 */
bool hasPrevTreeMapEntry(TreeMapIterator* itr);

/**
 * Resets the tree map iterator to the beginning of the map.
 *
 * @param itr the TreeMapIterator
 * @return true if successful, false if not supported
 */
bool resetTreeMapIterator(TreeMapIterator* itr);

/**
 * Returns the number of entries returned so far.
 *
 * @param itr the TreeMapIterator
 * @return the number of entries returned so far
 */
int getTreeMapIteratorCount(TreeMapIterator* itr);

/**
 * Returns the number of entries available.
 *
 * @param itr the TreeMapIterator
 * @return available number of entries or UNAVAILABLE if cannot perform operation.
 */
int getTreeMapIteratorAvailable(TreeMapIterator* itr);

#endif /* TREE_MAP_ITERATOR_H_ */
