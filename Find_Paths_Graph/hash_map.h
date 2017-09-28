/*
 * hash_map.h
 *
 * This file provides the structures and function declarations of a HashMap,
 * which is a Map that is backed by a HashTable.
 *
 * @since 2017-03-22
 * @author philip gust
 *
 */

#ifndef HASH_MAP_H_
#define HASH_MAP_H_
#include "map_entry.h"

/**
 * Entry in the hash chain for a hash table entry
 */
typedef struct _HashChainEntry {
	MapEntry entry;						// entry key/value pair
	int hashCode;						// hash code for the entry key
	struct _HashChainEntry* nextEntry;  // pointer to next entry in chain
} HashChainEntry;

/**
 * An entry in the hash table array.
 */
typedef struct {
  HashChainEntry* hashChain;			// list of hash chain entries
} HashTableEntry;

/**
 * The hash table
 */
typedef struct {
	HashTableEntry* hashTable;			// the hash table
	int capacity;						// the current size of the hash table
	float loadFactor;					// % full before resizing table
	int size;							// number of entries in table
} HashMap;

/**
 * Create new empty HashMap.
 *
 * @return new HashMap
 */
HashMap* createHashMap(void);

/**
 * Frees a HashMap.
 *
 * @param map the HashMap to free
 */
void freeHashMap(HashMap* map);

/**
 * Removes all of the mappings from this map.
 *
 * @param map the HashMap
 */
void clearHashMap(HashMap* map);

/**
 * Returns true if this map contains a mapping for the specified key.
 *
 * @param map the HashMap
 * @param key the entry key to check
 */
bool containsHashMapKey(HashMap* map, MapKey key);

/**
 * Returns true if this map maps one or more keys to the specified value.
 *
 * @param map the HashMap
 * @param value the entry value to check
 */
bool containsHashMapValue(HashMap* map, MapValue* value);


/**
 * Returns an null-terminated array of pointers to MapEntry mappings
 * contained in this map. Caller is responsible for freeing allocated array.
 *
 * @param map the HashMap
 * @return the set of HashMap entries for the map
 */
MapEntry** getHashMapEntrySet(HashMap* map);

/**
 * Returns the entry to which the specified key is mapped, or null if
 * this map contains no mapping for the key.
 *
 * @param map the HashMap
 * @param key the entry key for the value to get
 * @return the MapEntry for the given key
 */
MapEntry* getHashMapEntry(HashMap* map, MapKey key);

/**
 * Returns the value to which the specified key is mapped, or null if
 * this map contains no mapping for the key.
 *
 * @param map the HashMap
 * @param key the entry key for the value to get
 * @return the value for the given key
 */
MapValue* getHashMapValue(HashMap* map, MapKey key);

/**
 * Returns an null-terminated array of pointers to MapValue entries contained
 * in this map. Caller is responsible for freeing allocated array.
 *
 * @param map the map
 * @return null-terminated array of pointers to KeyMap keys for this map
 */
MapValue** getHashMapValues(HashMap* map);

/**
 * Returns true if this map contains no key-value mappings.
 *
 * @param map the HashMap
 * @return true of the map is entry, false otherwise
 */
bool isHashMapEmpty(HashMap* map);

/**
 * Returns an null-terminated array of pointers to MapKey keys contained
 * in this map. Caller is responsible for freeing allocated array.
 *
 * @param map the HashMap
 * @return the set of key strings in the map
 */
MapKey** getHashMapKeys(HashMap* map);

/**
 * Associates the specified value with the specified key in this map
 *
 * @param map the HashMap
 * @param key the key for the value to put
 * @param value the HashMapValue for the key
 * @return the previous value for the key, or NULL for a new entry
 */
MapValue* putHashMapEntry(HashMap* map, MapKey key, MapValue* value);

/**
 * Copies all of the mappings from the specified map to this map
 *
 * @param map the HashMap
 * @param aMap another map whose entries will be added to the map
 */
void putAllHashMapEntries(HashMap* map, HashMap* aMap);

/**
 * Removes the mapping for a key from this map if it is present
 *
 * @param map the HashMap
 * @param key the key for the value to remove
 * @return the value of the entry that was removed
 */
MapValue* removeHashMapEntryForKey(HashMap* map, MapKey key);

/**
 * Returns the number of key-value mappings in this map.
 *
 * @param map the HashMap
 * @return the number of entries in the map
 */
int getHashMapSize(HashMap* map);

#endif /* HASH_MAP_H_ */
