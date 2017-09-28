/*
 * tree_map_iterator.c
 *
 * This file provides the implementations of a HashSetIterator that
 * iterates over the keys of a HashSet.
 *
 * @since 2017-03-15
 * @author philip gust
 */

#include <stdlib.h>
#include <stdbool.h>
#include "hash_set_iterator.h"


/**
 * Create and initialize a new HashSetIterator
 *
 * @param set the set
 * @return an iterator for the specified tree set
 */
HashSetIterator* createHashSetIterator(HashSet* set) {
	HashSetIterator* itr = (HashSetIterator*)malloc(sizeof(HashSetIterator));
	itr->mapIterator = createHashMapIterator(set->map);
	return itr;
}

/**
 * Freeing iterator storage.
 *
 * @param itr the HashSetIterator to delete
 */
void freeHashSetIterator(HashSetIterator* itr) {
	freeHashMapIterator(itr->mapIterator);
	itr->mapIterator = (HashMapIterator*)NULL;
	free(itr);
}

/**
 * Gets next key in the set
 *
 * @param itr the HashSetIterator
 * @return the next key or NULL if iterator is at end the set
 */
MapKey* getNextHashSetKey(HashSetIterator* itr) {
	MapEntry* entry = getNextHashMapEntry(itr->mapIterator);
	return (entry == (MapEntry*)NULL) ? (MapKey*)NULL : &(entry->key);
}

/**
 * Determines whether there is another key in the set
 *
 * @param itr the HashSetIterator
 * @return true if there is another key, false otherwise
 */
bool hasNextHashSetKey(HashSetIterator* itr) {
	return hasNextHashMapEntry(itr->mapIterator);
}

/**
 * Gets previous key in the tree set
 *
 * @param itr the HashSetIterator
 * @return the previous key or NULL if iterator is at end of list
 */
MapKey* getPrevHashSetKey(HashSetIterator* itr) {
	MapEntry* entry = getPrevHashMapEntry(itr->mapIterator);
	return (entry == (MapEntry*)NULL) ? (MapKey*)NULL : &(entry->key);
}

/**
 * Determines whether there is a previous key in the set.
 *
 * @param itr the HashSetIterator
 * @return the previous key or NULL if iterator is at beginning of the set
 */
bool hasPrevHashSetKey(HashSetIterator* itr) {
	return hasPrevHashMapEntry(itr->mapIterator);
}

/**
 * Resets the iterator to the beginning of the set.
 *
 * @param itr the HashSetIterator
 * @return true if successful, false if not supported
 */
bool resetHashSetIterator(HashSetIterator* itr) {
	return resetHashMapIterator(itr->mapIterator);
}

/**
 * Returns the number of keys returned so far.
 *
 * @param itr the HashSetIterator
 * @return the number of keys returned so far
 */
int getHashSetIteratorCount(HashSetIterator* itr) {
	return getHashMapIteratorCount(itr->mapIterator);
}

/**
 * Returns the number of keys available.
 *
 * @param itr the HashSetIterator
 * @return available number of keys or UNAVAILABLE if cannot perform operation.
 */
int getHashSetIteratorAvailable(HashSetIterator* itr) {
	return getHashMapIteratorAvailable(itr->mapIterator);
}
