/*
 * tree_set.h
 *
 * This file provides the implementations of a HashSet, which is
 * a Set that is backed by a HashMap.
 *
 * @since 2017-03-15
 * @author philip gust
 */

#include "hash_set.h"

#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include "hash_map.h"
#include "hash_set_iterator.h"

/**
 * The value assigned to all MapEntry value fields
 */
static MapValue* ENTRY_VALUE = &(MapValue){""};

/**
 * Create new empty HashSet.
 *
 * @return a new HashSet
 */
HashSet* createHashSet(void) {
	HashSet* set = (HashSet*)malloc(sizeof(HashSet));
	set->map = createHashMap();
	return set;
}

/**
 * Frees a HashSet.
 *
 * @param set the HashSet to free
 */
void freeHashSet(HashSet* set) {
	freeHashMap(set->map);
	set->map = (HashMap*)NULL;
	free(set);
}

/**
 * Removes all of the keys from this set.
 *
 * @param set the HashSet
 */
void clearHashSet(HashSet* set) {
	clearHashMap(set->map);
}

/**
 * Adds the specified key to this set if it is not already present.
 *
 * @param set the HashSet
 * @param key the entry key to check
 * @return true if the key was added, false otherwise
 */
bool addHashSetKey(HashSet* set, MapKey key) {
	return putHashMapEntry(set->map, key, ENTRY_VALUE);
}

/**
 * Adds all keys to this set that are present in the other set.
 *
 * @param set the HashSet
 * @param otherSet the other HashSet
 * @return true if the set was modified as a result of this call
 */
bool addAllHashSetKeys(HashSet* set, HashSet* otherSet) {
	if (!containsAllHashSetKeys(set, otherSet)) {
		putAllHashMapEntries(set->map, otherSet->map);
		return true;
	}
	return false;
}

/**
 * Returns true if this set contains the specified key.
 *
 * @param set the HashSet
 * @param key the entry key to check
 * @return true if the set contains the key, false otherwise
 */
bool containsHashSetKey(HashSet* set, MapKey key) {
	return containsHashMapKey(set->map, key);
}

/**
 * Returns true if this set contains all the keys from the other set.
 *
 * @param set the HashSet
 * @param key the entry key to check
 * @return true if the set contains all the keys, false otherwise
 */
bool containsAllHashSetKeys(HashSet* set, HashSet* otherSet) {
	HashSetIterator* otherItr = createHashSetIterator(otherSet);
	bool result = true;
	MapKey* key = getNextHashSetKey(otherItr);
	while (result && key != (MapKey*)NULL) {
		result &= containsHashSetKey(set, *key);
		key = getNextHashSetKey(otherItr);
	}
	freeHashSetIterator(otherItr);
	return result;
}

/**
 * Returns the size of the set.
 *
 * @param set the HashSet
 * @return the size of the HashSet
 */
int getHashSetSize(HashSet* set) {
	return getHashMapSize(set->map);
}

/**
 * Returns true if this set contains no keys.
 *
 * @param set the HashSet
 * @return true of the set is entry, false otherwise
 */
bool isHashSetEmpty(HashSet* set) {
	return isHashMapEmpty(set->map);
}

/**
 * Removes the specified element from this set if it is present.
 *
 * @param set the HashSet
 * @param key the entry key to check
 * @return true if the key was removed, false otherwise
 */
bool removeHashSetKey(HashSet* set, MapKey key) {
	return (removeHashMapEntryForKey(set->map, key) != (MapValue*)NULL);
}

/**
 * Removes all elements from this set that are present in the other set.
 *
 * @param set the HashSet
 * @param key the entry key to check
 * @return true if the set changed as a result of this call
 */
bool removeAllHashSetKeys(HashSet* set, HashSet* otherSet) {
	HashSetIterator* otherItr = createHashSetIterator(otherSet);
	MapKey* keyptr = getNextHashSetKey(otherItr);
	bool result = false;
	while (keyptr != (MapKey*)NULL) {
		result |= removeHashSetKey(set, *keyptr);
		keyptr = getNextHashSetKey(otherItr);
	}
	freeHashSetIterator(otherItr);
	return result;
}

/**
 * Retains only the elements in this set that are present in the other set.
 *
 * @param set the HashSet
 * @param key the entry key to check
 * @return true if the set changed as a result of this call
 */
bool retainAllHashSetKeys(HashSet* set, HashSet* otherSet) {
	// set of keys in set that are not present in the other set
	HashSet* removeSet = createHashSet();

	// collect all keys in set that are not present in the other set
	HashSetIterator* itr = createHashSetIterator(set);
	MapKey* keyptr = getNextHashSetKey(itr);
	while (keyptr != (MapKey*)NULL) {
		if (!containsHashSetKey(otherSet, *keyptr)) {
			addHashSetKey(removeSet, *keyptr);
		}
		keyptr = getNextHashSetKey(itr);
	}
	freeHashSetIterator(itr);

	// remove all keys not present in other set from set
	bool result = removeAllHashSetKeys(set, removeSet);
	freeHashSet(removeSet);
	return result;
}
