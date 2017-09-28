/*
 * hash_map_iterator.c
 *
 * This file provides the implementations of a HashMapIterator that
 * iterates over a HashMap.
 *
 * @since 2017-03-22
 * @author philip gust
 */

#include <stdlib.h>
#include <stdbool.h>
#include "hash_map_iterator.h"


/**
 * Create and initialize a new HashMapIterator
 *
 * @param map the map
 * @return an iterator for the specified hash map
 */
HashMapIterator* createHashMapIterator(HashMap* map) {
	HashMapIterator* itr = (HashMapIterator*)malloc(sizeof(HashMapIterator));
 	itr->map = map;
	resetHashMapIterator(itr);
	return itr;
}

/**
 * Freeing iterator storage.
 *
 * @param itr the HashMapIterator to delete
 */
void freeHashMapIterator(HashMapIterator* itr) {
	itr->map = (HashMap*)NULL;
	itr->hashTableIndex = -1;
	itr->hashChainEntry = (HashChainEntry*)NULL;
	itr->count = -1;
	free(itr);
}

/**
 * Gets next entry in the map.
 *
 * @param itr the HashMapIterator
 * @return the next entry or NULL if iterator is at end the map
 */
MapEntry* getNextHashMapEntry(HashMapIterator* itr) {
	if (!hasNextHashMapEntry(itr)) {
		return (MapEntry*)NULL;
	}

	if (itr->hashChainEntry == (HashChainEntry*)NULL) {
		// pointing off end of entry chain, so need to
		// search forward in next table entries
		for (itr->hashTableIndex++;
			 itr->hashTableIndex < itr->map->capacity; itr->hashTableIndex++) {
			// get head of table list entry chain
			HashChainEntry* hashChainHead =
				itr->map->hashTable[itr->hashTableIndex].hashChain;
			// if chain exists, point to head of chain and return head
			if (hashChainHead != (HashChainEntry*)NULL) {
				itr->hashChainEntry = hashChainHead;
				break;
			}
		}
	}

	// return current entry and advance listEntry to next one
	MapEntry* entry = &itr->hashChainEntry->entry;
	itr->hashChainEntry = itr->hashChainEntry->nextEntry;
	itr->count++;
	return entry;
}

/**
 * Determines whether there is another entry in the map
 *
 * @param itr the HashMapIterator
 * @return true if there is another entry, false otherwise
 */
bool hasNextHashMapEntry(HashMapIterator* itr) {
	return itr->count < itr->map->size;
}

/**
 * Gets previous entry in the hash map
 *
 * @param itr the HashMapIterator
 * @return the previous entry or NULL if iterator is at end of list
 */
MapEntry* getPrevHashMapEntry(HashMapIterator* itr) {
	if (!hasPrevHashMapEntry(itr)) {
		return (MapEntry*)NULL;
	}
	HashTableEntry* hashTable = itr->map->hashTable;
	if (itr->hashChainEntry == hashTable[itr->hashTableIndex].hashChain) {
		// pointing to start of entry chain for current entry,
		// so need to search back in previous table entries
		while (itr->hashTableIndex > 0) {
			// see if previous table entry has a list
			HashChainEntry* listEntry =
				hashTable[--itr->hashTableIndex].hashChain;
			if (listEntry != (HashChainEntry*)NULL) {
				while (listEntry->nextEntry != (HashChainEntry*)NULL) {
					listEntry = listEntry->nextEntry;
				}
				itr->hashChainEntry = listEntry;
				itr->count--;
				return &listEntry->entry;
			}
		}
		return (MapEntry*)NULL;  // should not happen

	} else {
		// find previous TableListEntry for this key
		HashChainEntry* listEntry = hashTable[itr->hashTableIndex].hashChain;
		while (listEntry->nextEntry != itr->hashChainEntry) {
			listEntry = listEntry->nextEntry;
		}
		itr->hashChainEntry = listEntry;
		itr->count--;
		return &listEntry->entry;
	}
}

/**
 * Determines whether there is a previous entry in the map.
 *
 * @param itr the HashMapIterator
 * @return true if there is a previous entry, false otherwise
 */
bool hasPrevHashMapEntry(HashMapIterator* itr) {
	return itr->count > 0;
}

/**
 * Resets the hash map iterator to the beginning of the map.
 *
 * @param itr the HashMapIterator
 * @return true if successful, false if not supported
 */
bool resetHashMapIterator(HashMapIterator* itr) {
 	itr->hashTableIndex = 0;
 	itr->hashChainEntry = itr->map->hashTable[itr->hashTableIndex].hashChain;
 	itr->count = 0;
 	return true;
}

/**
 * Returns the number of entries returned so far.
 *
 * @param itr the HashMapIterator
 * @return the number of entries returned so far
 */
int getHashMapIteratorCount(HashMapIterator* itr) {
	return itr->count;
}

/**
 * Returns the number of entries available.
 *
 * @param itr the HashMapIterator
 * @return available number of entries or UNAVAILABLE if cannot perform operation.
 */
int getHashMapIteratorAvailable(HashMapIterator* itr) {
	return itr->map->size - itr->count;
}

