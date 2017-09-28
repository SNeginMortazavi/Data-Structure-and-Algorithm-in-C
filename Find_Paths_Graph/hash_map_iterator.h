/*
 * hash_map_iterator.h
 *
 * This file provides the structures and function declarations of a
 * HashMapIterator that iterates over a HashMap.
 *
 * @since 2017-02-22
 * @author philip gust
 */

#ifndef HASH_MAP_ITERATOR_H_
#define HASH_MAP_ITERATOR_H_

#include <stdbool.h>
#include "hash_map.h"

/**
 * An iterator for a HashMap
 */
typedef struct {
 	HashMap* map;						// the hash map
 	int hashTableIndex;					// current has table index
 	HashChainEntry* hashChainEntry;		// current hash chain entry
 	int count;							// count of entries returned
} HashMapIterator;

/**
 * Create and initialize a new HashMapIterator
 *
 * @param map the map
 * @return an iterator for the specified hash map
 */
HashMapIterator* createHashMapIterator(HashMap* map);

/**
 * Freeing iterator storage.
 *
 * @param itr the HashMapIterator to delete
 */
void freeHashMapIterator(HashMapIterator* itr);

/**
 * Gets next link entry in the map
 *
 * @param itr the HashMapIterator
 * @return the next entry or NULL if iterator is at end the map
 */
MapEntry* getNextHashMapEntry(HashMapIterator* itr);

/**
 * Determines whether there is another entry in the map
 *
 * @param itr the HashMapIterator
 * @return true if there is another entry, false otherwise
 */
bool hasNextHashMapEntry(HashMapIterator* itr);

/**
 * Gets previous entry in the hash map

 * @param itr the HashMapIterator
 * @return the previous entry or NULL if iterator is at end of list
 */
MapEntry* getPrevHashMapEntry(HashMapIterator* itr);

/**
 * Determines whether there is a previous entry in the map.
 *
 * @param itr the HashMapIterator
 * @return true if there is a previous entry, false otherwise
 */
bool hasPrevHashMapEntry(HashMapIterator* itr);

/**
 * Resets the hash map iterator to the beginning of the map.
 *
 * @param itr the HashMapIterator
 * @return true if successful, false if not supported
 */
bool resetHashMapIterator(HashMapIterator* itr);

/**
 * Returns the number of entries returned so far.
 *
 * @param itr the HashMapIterator
 * @return the number of entries returned so far
 */
int getHashMapIteratorCount(HashMapIterator* itr);

/**
 * Returns the number of entries available.
 *
 * @param itr the HashMapIterator
 * @return available number of entries or UNAVAILABLE if cannot perform operation.
 */
int getHashMapIteratorAvailable(HashMapIterator* itr);

#endif /* HASH_MAP_ITERATOR_H_ */
