/*
 * Hash_map.h
 *
 * This file provides the structures and function declarations of a HashSet,
 * which is a set that is backed by a HashMap
 *
 * @since 2017-03-15
 * @author philip gust
 */

#ifndef HASH_SET_H_
#define HASH_SET_H_

#include <stdlib.h>
#include <stdbool.h>
#include "hash_map.h"

/**
 * Structure that defines a HashSet. All entries are private
 */
typedef struct {
	HashMap* map;
} HashSet;

/**
 * Create new empty HashSet.
 */
HashSet* createHashSet(void);

/**
 * Frees a HashSet.
 *
 * @param set the HashSet to free
 */
void freeHashSet(HashSet* set);

/**
 * Removes all of the keys from this set.
 *
 * @param set the HashSet
 */
void clearHashSet(HashSet* set);

/**
 * Adds the specified key to this set if it is not already present.
 *
 * @param set the HashSet
 * @param key the entry key to check
 * @return true if the key was added, false otherwise
 */
bool addHashSetKey(HashSet* set, MapKey key);

/**
 * Adds all keys to this set that are present in the other set.
 *
 * @param set the HashSet
 * @param otherSet the other HashSet
 * @return true if the set was modified as a result of this call
 */
bool addAllHashSetKeys(HashSet* set, HashSet* otherSet);

/**
 * Returns true if this set contains the specified key.
 *
 * @param set the HashSet
 * @param key the entry key to check
 * @return true if the set contains the key, false otherwise
 */
bool containsHashSetKey(HashSet* set, MapKey key);

/**
 * Returns true if this set contains all the keys from the other set.
 *
 * @param set the HashSet
 * @param key the entry key to check
 * @return true if the set contains all the keys, false otherwise
 */
bool containsAllHashSetKeys(HashSet* set, HashSet* otherSet);

/**
 * Returns true if this set contains no keys.
 *
 * @param set the HashSet
 * @return true of the set is entry, false otherwise
 */
bool isHashSetEmpty(HashSet* set);

/**
 * Returns the size of the set.
 *
 * @param set the HashSet
 * @return the size of the HashSet
 */
int getHashSetSize(HashSet* set);

/**
 * Removes the specified element from this set if it is present.
 *
 * @param set the HashSet
 * @param key the entry key to check
 * @return true if the key was removed, false otherwise
 */
bool removeHashSetKey(HashSet* set, MapKey key);

/**
 * Removes all elements from this set that are present in the other set.
 *
 * @param set the HashSet
 * @param key the entry key to check
 * @return true if the set changed as a result of this call
 */
bool removeAllHashSetKeys(HashSet* set, HashSet* otherSet);

/**
 * Retains only the elements in this set that are present in the other set.
 *
 * @param set the HashSet
 * @param key the entry key to check
 * @return true if the set changed as a result of this call
 */
bool retainAllHashSetKeys(HashSet* set, HashSet* otherSet);

#endif /* HASH_SET_H_ */
