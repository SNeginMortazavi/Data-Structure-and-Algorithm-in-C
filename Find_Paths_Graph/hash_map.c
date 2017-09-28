/*
 * hash_map.c
 *
 *  Created on: Mar 22, 2017
 *      Author: phil
 */

#include <stdio.h>
#include <stdbool.h>
#include <strings.h>
#include "hash_map.h"
#include "hash_map_iterator.h"

#ifndef DEFAULT_LOADING_FACTOR
#define DEFAULT_LOADING_FACTOR 0.75f;
#endif

#ifndef DEFAULT_CAPACITY
#define DEFAULT_CAPACITY 16
#endif

/**
 * Get the hash table index for the hash key in a table of a given capacity.
 *
 * @param hashCode the hash key
 * @param capacity the capacity of the table;
 * @return the hash key index in the table
 */
static int indexForTableEntryArray(int hashCode, int capacity) {
	return hashCode & (capacity-1);  // mod function for power of 2 capacity
}


/**
 * Create new empty HashMap.
 *
 * @return new HashMap
 */
HashMap* createHashMap(void) {
	// create and initialize the map
	HashMap* map = (HashMap*)malloc(sizeof(HashMap));
	map->size = 0;
	map->loadFactor = DEFAULT_LOADING_FACTOR;
	map->capacity = DEFAULT_CAPACITY;

	// create and initial hash table list for the map
	map->hashTable =
		(HashTableEntry*)malloc(map->capacity * sizeof (HashTableEntry));
	for (int i = 0; i < map->capacity; i++) {
		map->hashTable[i].hashChain = (HashChainEntry*)NULL;
	}

	return map;
}

/**
 * Frees a HashMap.
 *
 * @param map the HashMap to free
 */
void freeHashMap(HashMap* map) {
	clearHashMap(map);
	free(map->hashTable);
	map->hashTable = (HashTableEntry*)NULL;
	free(map);
}

/**
 * Removes all of the mappings from this map.
 *
 * @param map the HashMap
 */
void clearHashMap(HashMap* map) {
	// clear the table entries
	if (map->hashTable != (HashTableEntry*)NULL) {  // call assert?
		for (int i = 0; i < map->capacity; i++) {
			// free the list entry chain
			HashChainEntry* listEntry = map->hashTable[i].hashChain;
			while (listEntry != (HashChainEntry*)NULL) {
				HashChainEntry* nextListEntry = listEntry->nextEntry;
				listEntry->nextEntry = (HashChainEntry*)NULL;
				free(listEntry);
				listEntry = nextListEntry;
			}
			map->hashTable[i].hashChain = (HashChainEntry*)NULL;
		}
	}
	map->size = 0;
}

/**
 * Returns true if this map contains a mapping for the specified key.
 *
 * @param map the HashMap
 * @param key the entry key to check
 */
bool containsHashMapKey(HashMap* map, MapKey key) {
	return getHashMapEntry(map, key) != (MapEntry*)NULL;
}

/**
 * Returns true if this map maps one or more keys to the specified value.
 *
 * @param map the HashMap
 * @param value the entry value to check
 */
bool containsHashMapValue(HashMap* map, MapValue* value) {
	HashMapIterator* itr = createHashMapIterator(map);
	while (hasNextHashMapEntry(itr)) {
		MapEntry* mapEntry = getNextHashMapEntry(itr);
		if (compareMapValue(mapEntry->value, value) == 0) {
			freeHashMapIterator(itr);
			return true;
		}
	}
	freeHashMapIterator(itr);
	return false;
}

/**
 * Returns an null-terminated array of pointers to MapEntry mappings
 * contained in this map. Caller is responsible for freeing allocated array.
 *
 * @param map the HashMap
 * @return the set of HashMap entries for the map
 */
MapEntry** getHashMapEntries(HashMap* map) {
	// allocate MapEntrySet array
	MapEntry** mapEntrySet = (MapEntry**)malloc(map->size*sizeof(MapEntry*) + 1);
	int i = 0;
	HashMapIterator* itr = createHashMapIterator(map);
	while (hasNextHashMapEntry(itr)) {
		MapEntry* mapEntry = getNextHashMapEntry(itr);
		mapEntrySet[i++] = mapEntry;
	}
	mapEntrySet[i] = (MapEntry*)NULL; // NULL terminated array

	freeHashMapIterator(itr);
	return mapEntrySet;
}

/**
 * Returns the entry to which the specified key is mapped, or null if
 * this map contains no mapping for the key.
 *
 * @param map the HashMap
 * @param key the entry key for the value to get
 * @return the MapEntry for the given key
 */
MapEntry* getHashMapEntry(HashMap* map, MapKey key) {
	int hashCode = getMapEntryKeyHashCode(key);
	int entryIndex = indexForTableEntryArray(hashCode, map->capacity);

	HashChainEntry* chainEntry = map->hashTable[entryIndex].hashChain;
	for ( ; chainEntry != (HashChainEntry*)NULL; chainEntry= chainEntry->nextEntry) {
		if (hashCode == chainEntry->hashCode &&
			compareMapKey(key, chainEntry->entry.key) == 0) { // what if different? assert?
			return &chainEntry->entry;
		}
	}
	return (MapEntry*)NULL;
}

/**
 * Returns the value to which the specified key is mapped, or null if
 * this map contains no mapping for the key.
 *
 * @param map the HashMap
 * @param key the entry key for the value to get
 * @return the value for the given key
 */
MapValue* getHashMapValue(HashMap* map, MapKey key) {
	MapEntry* entry = getHashMapEntry(map, key);
	return (entry == (MapEntry*)NULL) ? (MapValue*)NULL : entry->value;
}

/**
 * Returns an null-terminated array of pointers to MapValue entries contained
 * in this map. Caller is responsible for freeing allocated array.
 *
 * @param map the map
 * @return null-terminated array of pointers to KeyMap keys for this map
 */
MapValue** getHashMapValues(HashMap* map) {
	// allocate MapEntrySet array
	MapValue** valueSet = (MapValue**)malloc(map->size*sizeof(MapValue*) + 1);
	int i = 0;
	HashMapIterator* itr = createHashMapIterator(map);
	while (hasNextHashMapEntry(itr)) {
		MapEntry* mapEntry = getNextHashMapEntry(itr);
		valueSet[i++] = mapEntry->value;
	}
	valueSet[i] = (MapValue*)NULL; // NULL terminated array

	freeHashMapIterator(itr);
	return valueSet;
}

/**
 * Returns true if this map contains no key-value mappings.
 *
 * @param map the HashMap
 * @return true of the map is entry, false otherwise
 */
bool isHashMapEmpty(HashMap* map) {
	return map->size == 0;
}

/**
 * Returns an null-terminated array of pointers to MapKey keys contained
 * in this map. Caller is responsible for freeing allocated array.
 *
 * @param map the HashMap
 * @return the set of key strings in the map
 */
MapKey** getHashMapKeys(HashMap* map) {
	// allocate MapEntrySet array
	MapKey** keySet = (MapKey**)malloc(map->size*sizeof(MapKey*) + 1);
	int i = 0;
	HashMapIterator* itr = createHashMapIterator(map);
	while (hasNextHashMapEntry(itr)) {
		MapEntry* mapEntry = getNextHashMapEntry(itr);
		keySet[i++] = &mapEntry->key;
	}
	keySet[i] = (MapKey*)NULL; // NULL terminated array

	freeHashMapIterator(itr);
	return keySet;
}

/**
 * Transfers all entries from current table to newTable.
 *
 * @param oldTable the old table entry array
 * @param oldCapacity the capacity of the old table entry array
 * @param newTable the new table entry array
 * @param newCapacity the capacity of the new table entry array
 */
static void transferTableEntryArray(HashTableEntry* oldTable, int oldCapacity,
		           HashTableEntry* newTable, int newCapacity) {
	// transfer entries for each table entry
	for (int index = 0; index < oldCapacity; index++) {
		// transfer entries for list entries at current index
		HashChainEntry* listEntry = oldTable[index].hashChain;
		oldTable[index].hashChain = (HashChainEntry*)NULL;  // disconnect chain
		while (listEntry != (HashChainEntry*)NULL) {
			HashChainEntry* nextEntry = listEntry->nextEntry;

			// splice in at head of the new table entry chain
			int newIndex = indexForTableEntryArray(listEntry->hashCode, newCapacity);
			listEntry->nextEntry = newTable[newIndex].hashChain;
			newTable[newIndex].hashChain = listEntry;

			listEntry = nextEntry;
		}
	}
}

/**
 * Replace old table entry array in map with resized table entry array
 * with contents transferred to the new table entry array. This method
 * is used with the table is at its threshold.
 *
 * @param map the map
 * @param newCapacity the new capacity, must be a power of two that is
 *  greater than current capacity.
 */
static void resizeTableEntryArray(HashMap* map, int newCapacity) {
	HashTableEntry* oldTable = map->hashTable;
	int oldCapacity = map->capacity;

	HashTableEntry* newTable = (HashTableEntry*)malloc(newCapacity*sizeof(HashTableEntry));
	for (int i = 0; i < newCapacity; i++) {  // initialize new table
		newTable[i].hashChain = (HashChainEntry*)NULL;
	}
	transferTableEntryArray(oldTable, oldCapacity, newTable, newCapacity);
	map->hashTable = newTable;
	map->capacity = newCapacity;
	free(oldTable);
}

/**
 * Adds a new entry with the key, value and hash code to the map,
 * and resizes the map entry table array if necessary.
 *
 * @param map the map
 * @param hashCode the hash key of the key
 * @param key the key to add
 * @param value the value to add
 * @param the entry index in the table entry array
 *
 */
static void addEntryToTableEntryArray(
	HashMap* map, int hashCode, MapKey key, MapValue* value, int entryIndex) {

	// splice in new list entry at head of chain
	HashChainEntry* newChainEntry = (HashChainEntry*)malloc(sizeof(HashChainEntry));

	// set fields of new list entry
	newChainEntry->hashCode = hashCode;
	newChainEntry->entry.key = key;
	newChainEntry->entry.value = value;

	// splice entry to head of list
	newChainEntry->nextEntry = map->hashTable[entryIndex].hashChain;
	map->hashTable[entryIndex].hashChain = newChainEntry;

	// resize table if at threshold (map capacity * loadFactor)
	if (++map->size > map->capacity*map->loadFactor) {
		resizeTableEntryArray(map, 2* map->capacity);
	}
 }



/**
 * Associates the specified value with the specified key in this map
 *
 * @param map the HashMap
 * @param key the key for the value to put
 * @param value the HashMapValue for the key
 * @return the previous value for the key, or NULL for a new entry
 */
MapValue* putHashMapEntry(HashMap* map, MapKey key, MapValue* value) {
	int hashCode = getMapEntryKeyHashCode(key);
	int entryIndex = indexForTableEntryArray(hashCode, map->capacity);

	// look for existing entry in entry chain
	HashChainEntry* listEntry = map->hashTable[entryIndex].hashChain;
	for ( ; listEntry != (HashChainEntry*)NULL; listEntry = listEntry->nextEntry) {
		if (   listEntry->hashCode == hashCode
			&& compareMapKey(key, listEntry->entry.key) == 0) {
			MapValue* oldValue = listEntry->entry.value;
			listEntry->entry.value = value;
			return oldValue;
		}
	}
	// add entry to map and resize if necessary
	addEntryToTableEntryArray(map, hashCode, key, value,entryIndex);

	return (MapValue*)NULL;
}

/**
 * Copies all of the mappings from the specified map to this map
 *
 * @param map the HashMap
 * @param aMap another map whose entries will be added to the map
 * @todo What happens with values for entries whose keys are duplicates.
 */
void putAllHashMapEntries(HashMap* map, HashMap* aMap) {
	HashMapIterator* itr = createHashMapIterator(aMap);
	while (hasNextHashMapEntry(itr)) {
		MapEntry* entry = getNextHashMapEntry(itr);
		putHashMapEntry(map, entry->key, entry->value);
	}
}

/**
 * Removes the mapping for a key from this map if it is present
 *
 * @param map the HashMap
 * @param key the key for the value to remove
 * @return the value of the entry that was removed
 */
MapValue* removeHashMapEntryForKey(HashMap* map, MapKey key) {
	int hashCode = getMapEntryKeyHashCode(key);
	int entryIndex = indexForTableEntryArray(hashCode, map->capacity);

	HashChainEntry* listEntry = map->hashTable[entryIndex].hashChain;
	HashChainEntry* prevListEntry = (HashChainEntry*)NULL;

	while (listEntry != (HashChainEntry*)NULL) {
		if (hashCode == listEntry->hashCode &&
			compareMapKey(key, listEntry->entry.key) == 0) {
			// splice out node from list
			HashChainEntry* nextListEntry = listEntry->nextEntry;
			if (prevListEntry == (HashChainEntry*)NULL) {
				map->hashTable[entryIndex].hashChain = nextListEntry;
			} else {
				prevListEntry->nextEntry = nextListEntry;
			}

			// free the node
			MapValue* value = listEntry->entry.value;
			listEntry->nextEntry = (HashChainEntry*)NULL;
			free(listEntry);

			map->size--;
			return value;
		}
		prevListEntry = listEntry;
		listEntry = listEntry->nextEntry;
	}
	return (MapValue*)NULL;
}

/**
 * Returns the number of key-value mappings in this map.
 *
 * @param map the HashMap
 * @return the number of entries in the map
 */
int getHashMapSize(HashMap* map) {
	return map->size;
}
