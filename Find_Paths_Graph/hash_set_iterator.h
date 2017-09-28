/*
 * tree_set_iterator.h
 *
 * This file provides the structures and function declarations of a
 * HashSetIterator that iterates over the entries of a HashSet.
 *
 * @since 2017-02-15
 * @author philip gust
 */

#ifndef HASH_SET_ITERATOR_H_
#define HASH_SET_ITERATOR_H_

#include <stdbool.h>

#include "hash_set.h"
#include "hash_map_iterator.h"

/**
 * An iterator for a HashSet
 */
typedef struct {
  HashMapIterator* mapIterator;
} HashSetIterator;

/**
 * Create and initialize a new HashSetIterator
 *
 * @param set the set
 * @return an iterator for the specified tree set
 */
HashSetIterator* createHashSetIterator(HashSet* set);

/**
 * Freeing iterator storage.
 *
 * @param itr the HashSetIterator to delete
 */
void freeHashSetIterator(HashSetIterator* itr);

/**
 * Gets next key in the set
 *
 * @param itr the HashSetIterator
 * @return the next key or NULL if iterator is at end the set
 */
MapKey* getNextHashSetKey(HashSetIterator* itr);

/**
 * Determines whether there is another key in the set
 *
 * @param itr the HashSetIterator
 * @return true if there is another key, false otherwise
 */
bool hasNextHashSetKey(HashSetIterator* itr);

/**
 * Gets previous key in the tree set
 *
 * @param itr the HashSetIterator
 * @return the previous key or NULL if iterator is at end of list
 */
MapKey* getPrevHashSetKey(HashSetIterator* itr);

/**
 * Determines whether there is a previous key in the set.
 *
 * @param itr the HashSetIterator
 * @return the previous key or NULL if iterator is at beginning of the set
 */
bool hasPrevHashSetKey(HashSetIterator* itr);

/**
 * Resets the tree set iterator to the beginning of the set.
 *
 * @param itr the HashSetIterator
 * @return true if successful, false if not supported
 */
bool resetHashSetIterator(HashSetIterator* itr);

/**
 * Returns the number of keys returned so far.
 *
 * @param itr the HashSetIterator
 * @return the number of keys returned so far
 */
int getHashSetIteratorCount(HashSetIterator* itr);

/**
 * Returns the number of keys available.
 *
 * @param itr the HashSetIterator
 * @return available number of keys or UNAVAILABLE if cannot perform operation.
 */
int getHashSetIteratorAvailable(HashSetIterator* itr);

#endif /* HASH_SET_ITERATOR_H_ */
